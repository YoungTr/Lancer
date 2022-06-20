//
// Created by YoungTr on 2022/6/18.
//

#include <dlfcn.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <stdio.h>
#include <sys/stat.h>
#include "lan_utils.h"
#include "lan_trace.h"
#include "lan_utils.h"
#include "lan_errno.h"
#include "log.h"
#include "xhook.h"

int lan_api_level = 0;
char *lan_trace_dir = NULL;

static uint64_t original_tags = -1;
static uint64_t *atrace_enable_tags = NULL;

static int *atrace_maker_fd = NULL;

static int trace_fd = -1;

static int trace_installed = 0;

static int need_write_systrace(int fd, size_t count) {
    return (trace_installed && fd == *atrace_maker_fd && count > 0) ? 0 : 1;
}

// todo
// 频繁的 UI 操作会影响性能，可以先保存到内存然后异常写入，或者使用 mmap
void write_trace(const void *buf, size_t count) {
    double sec = (double) get_system_nanosecond() / 1000000000;
    const char *trace = buf;
    char content[1024];
    char thread[256];
    int len;
    util_get_thread_name(gettid(), thread, sizeof(thread));
    switch (trace[0]) {
        case 'B':
            len = snprintf(content, sizeof(content),
                           "%s-%d [000] ...1 %.6f: tracing_mark_write: %s\n", thread, gettid(), sec,
                           trace);
            write(trace_fd, content, len);
            break;
        case 'E':
            len = snprintf(content, sizeof(content),
                           "%s-%d [000] ...1 %.6f: tracing_mark_write: E\n", thread, gettid(), sec);
            write(trace_fd, content, len);
            break;
        default:
            return;
    }

}

ssize_t (*original_write)(int fd, const void *const __pass_object_size0 buf, size_t count);

ssize_t my_write(int fd, const void *const buf, size_t count) {
    if (0 == need_write_systrace(fd, count)) {
        write_trace(buf, count);
    }
    return original_write(fd, buf, count);
}

ssize_t (*original_write_chk)(int fd, const void *const __pass_object_size0 buf, size_t count,
                              size_t buf_size);

ssize_t my_write_chk(int fd, const void *const buf, size_t count, size_t buf_size) {
    if (0 == need_write_systrace(fd, count)) {
        write_trace(buf, count);
    }
    return original_write(fd, buf, count);
}

void hook_libc() {
    xhook_register(".*libc\\.so$", "write", (void *) my_write, (void **) (&original_write));
    xhook_register(".*libc\\.so$", "__write_chk", (void *) my_write_chk,
                   (void **) (&original_write_chk));
    xhook_refresh(1);
}

int lan_trace_init(const int app_level, const char *trace_dir) {
    int r = -1;
    lan_api_level = app_level;
    lan_trace_dir = strdup(trace_dir);

    void *handle;

    if (NULL == (handle = dlopen(NULL, RTLD_GLOBAL))) return LANCER_ERRNO_SYS;
    if (NULL == (atrace_enable_tags = dlsym(handle, LANCER_LIB_CUTILS_ENABLETAGS))) goto err;
    if (NULL == (atrace_maker_fd = dlsym(handle, LANCER_LIB_CUTILS_ATRACE_MAKER_FD))) goto err;

    // hook
    hook_libc();

    // mkdir
    LOGD("trace dir: %s", trace_dir);
    if (0 != (r = util_mkdirs(trace_dir))) goto err;

    trace_installed = 1;
    return 0;

  err:
    dlclose(handle);
    handle = NULL;
    return r;
}

static void open_trace_file() {
    char file[256];
    uint64_t time = get_system_nanosecond();
    snprintf(file, sizeof(file), "%s/%020"PRIu64"_%s", lan_trace_dir, time, "trace.txt");
    int fd = open(file, COMMON_OPEN_NEW_FILE_FLAGS, COMMON_OPEN_NEW_FILE_MODE);
    if (fd >= 0) {
        trace_fd = fd;
        char *head = "TRACE:\n# tracer: nop\n#\n";
        write(fd, head, strlen(head));
    }
}


void lan_trace_enable() {
    if (trace_installed) {
        original_tags = *atrace_enable_tags;
        *atrace_enable_tags = UINT64_MAX;
        // open file
        open_trace_file();
    }

}

void lan_trace_disable() {
    if (NULL != atrace_enable_tags) {
        *atrace_enable_tags = original_tags;
        close(trace_fd);
        trace_fd = -1;
    }
}
