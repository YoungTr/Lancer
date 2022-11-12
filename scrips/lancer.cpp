//
// Created by YoungTr on 2022/11/12.
//

#include <stack>
#include <strstream>
#include "lancer.h"


double StringToDouble(const char *s) {
    double val;
    std::strstream ss;
    ss << s;
    ss >> val;
    return val;
}


static bool IsMethodIn(const char x) {
    return x == METHOD_IN;
}

static bool IsHandlerMethod(const char *method) {
    string s = string(method);
    return s.find("Handler (") == 0;
}

static bool IsStartWith(const char *s1, const char *s2) {
    string t = string(s1);
    return t.find(s2) == 0;
}

void Lancer::ReadFile(const string &file) {

    in_fp_ = fopen(file.c_str(), "r");
    out_fp_ = fopen("lancer.txt", "w+");
    handler_fp_ = fopen("handler_method_record.txt", "w+");
    if (nullptr == in_fp_ || nullptr == out_fp_ || nullptr == handler_fp_) {
        return;
    }

    fputs("TRACE:\n# tracer: nop\n", out_fp_);

    stack<string> words;

    char line[256];

    char time[64];
    char type[8];
    char method[256];
    char handler_method[256];
    char temp[512];

    char handler_method_record[256];
    double handler_start = 0;
    double handler_end = 0;
    char handler_temp[512];


    while (fgets(line, sizeof(line), in_fp_)) {
//        if (nullptr != strstr(line, "TRACE_START") || nullptr != strstr(line, "TRACE_END")) {
//            continue;
//        }
        if (3 != sscanf(line, "%[^:]%*s %[^|]|%127[^\\\n]", time, type, method)) {
            continue;
        }
        bool is_handler = IsHandlerMethod(method);
        bool is_method_in = IsMethodIn(type[0]);

        if (is_handler) {
            // 记录 handler_method 的时间
            if (is_method_in) {
                if (handler_start > 0) {
                    printf("handler_method_record start not be >0 %s\n", method);
                }
                handler_start = StringToDouble(time);
                strcpy(handler_method_record, method);
            } else {
                if (IsStartWith(handler_method_record, method)) {
                    handler_end = StringToDouble(time);
                    double duration = handler_end - handler_start;
                    snprintf(handler_temp, sizeof(handler_temp), "%f cast [start: %7f ~ end: %7f] in %s\n",
                             duration, handler_start, handler_end, handler_method_record);
                    handler_start = 0;
                    fputs(handler_temp, handler_fp_);
                } else {
                    printf("not match end handler_method_record %s\n", method);
                }
            }

            // 截取handler方法
            if (1 == sscanf(method, "%*s (%[^)]", handler_method)) {
//                printf("%s: %s\n", type, handler_method);
                strcpy(method, handler_method);
            }
        }

        if (is_method_in) {
            words.push(string(method));
            snprintf(temp, sizeof(temp), "%s-%s [000] ...1 %s tracing_mark_write: %s|%s|%s\n",
                     DEFAULT_PACKAGE,
                     DEFAULT_PID,
                     time,
                     type,
                     DEFAULT_PID,
                     method);

        } else {
            if (words.empty()) {
                printf("not find in method: %s\n", method);
            } else {
                string in_method = words.top();
                if (0 == strcmp(in_method.c_str(), method)) {
                    words.pop();
                } else {
                    printf("not match in method: %s\n", method);
                }

            }

            snprintf(temp, sizeof(temp), "%s-%s [000] ...1 %s tracing_mark_write: %s\n",
                     DEFAULT_PACKAGE,
                     DEFAULT_PID,
                     time,
                     type);
        }

        fputs(temp, out_fp_);
    }

    printf("not matched method size: %lu\n", words.size());
    while (!words.empty()) {
        string p = words.top();
        printf("not matched method: %s\n", p.c_str());
        words.pop();
    }


}

void Lancer::OnDestroy() {
    if (nullptr != in_fp_) {
        fclose(in_fp_);
    }

    if (nullptr != out_fp_) {
        fclose(out_fp_);
    }

    if (nullptr != handler_fp_) {
        fclose(handler_fp_);
    }

}
