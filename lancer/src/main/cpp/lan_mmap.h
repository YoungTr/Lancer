//
// Created by YoungTr on 2022/6/21.
//

#ifndef LANCER_LAN_MMAP_H
#define LANCER_LAN_MMAP_H

#include <stdio.h>
#include <fcntl.h>
#include<sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>

#define LAN_MMAP_MMAP   1
#define LAN_MMAP_MEMROY 0
#define LAN_MMAP_FAIL -1

#define LAN_DATA_LENGTH 10 * 1024 // 10M

#define COMMON_OPEN_NEW_FILE_FLAGS (O_CREAT | O_WRONLY | O_CLOEXEC | O_TRUNC | O_APPEND)
#define COMMON_OPEN_NEW_FILE_MODE  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) //644


#ifdef __cplusplus
extern "C" {
#endif

int lan_open_mmap_file(char *filepath, unsigned char **buffer);

#ifdef __cplusplus
}
#endif

#endif //LANCER_LAN_MMAP_H
