//
// Created by YoungTr on 2022/4/14.
//

#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include "sn_util.h"

char *util_trim(char *start) {
    char *end;

    if (NULL == start) return NULL;

    end = start + strlen(start);
    if (start == end) return start;

    while (start < end && isspace((int) (*start))) start++;
    if (start == end) return start;

    while (start < end && isspace((int) (*(end - 1)))) end--;
    *end = '\0';
    return start;


}