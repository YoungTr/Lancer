//
// Created by YoungTr on 2022/6/21.
//

#include "lan_mmap.h"

int lan_open_mmap_file(char *filepath, unsigned char **buffer) {
    if (NULL == filepath || 0 == strnlen(filepath, 128))
        return LAN_MMAP_MEMROY;

    int r = LAN_MMAP_FAIL;
    unsigned char *p_map = NULL;
    int size = LAN_DATA_LENGTH;
    // open file
    int fd = open(filepath, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    if (0 <= fd) {
        FILE *file = fopen(filepath, "rb+");
        if (NULL != file) {
            fseek(file, 0, SEEK_END);
            long fileSize = ftell(file);
            if (fileSize < size) {
                fseek(file, 0, SEEK_SET);
                char zero_data[size];
                memset(zero_data, 0, size);
                size_t _size = fwrite(zero_data, sizeof(char), size, file);
                fflush(file);
                if (_size == size) {
                    LOGD("copy data to mmap file success");
                }
            }
            fclose(file);
        }
        // open success, then mmap
        if (NULL == (p_map = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0))) {
            LOGE("mmap failed.");
            r = LAN_MMAP_MEMROY;
        } else {
            LOGD("mmap success.");
            r = LAN_MMAP_MMAP;
        }
        close(fd);

        // check mmap
        if (LAN_MMAP_MMAP == r && access(filepath, F_OK) != -1) {
            LOGD("check mmap success.");
            r = LAN_MMAP_MMAP;
            *buffer = p_map;
        } else {
            r = LAN_MMAP_MEMROY;
            LOGE("check mmap success.");
            if (NULL != p_map) {
                munmap(p_map, size);
            }
        }
    } else {
        LOGE("open file failed: %s", filepath);
    }

    if (r == LAN_MMAP_MEMROY) {
        *buffer = malloc(LAN_DATA_LENGTH);
    }

    return r;
}