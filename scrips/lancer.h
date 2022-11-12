//
// Created by YoungTr on 2022/11/12.
//

#ifndef LANCER_LANCER_H
#define LANCER_LANCER_H

#include <cstdio>
#include <string>

#define MAX_METHOD_COUNT 100000
#define MAX_METHOD_LENGTH 256

#define DEFAULT_PACKAGE "package"
#define DEFAULT_PID "1234"
#define METHOD_IN 'B'
#define METHOD_OUT 'E'

using namespace std;

class Lancer {
public:
    void ReadFile(const string &file);

    void OnDestroy();

private:
    FILE *in_fp_;
    FILE *out_fp_;
    FILE *handler_fp_;


};

#endif //LANCER_LANCER_H
