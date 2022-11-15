#include "lancer.h"
#include <string>

using namespace std;

void test() {
    string line = "1334588.091854: B|RecyclerViewHelp:getItemViewType";

    char time[20];
    char type[127];
    char method[127];

//    sscanf(line.c_str(), "%*s (%[^)]", method);
//    printf("time:%s, type:%s, method:%s\n", time, type, method);


    int c = sscanf(line.c_str(), "%[^:]%*s %[^|]|%[^\\\n]", time, type, method);

    printf("c: %d\n", c);

    printf("time->%s, type->%s, method->%s\n", time, type, method);


}

int main(int argc, char *argv[]) {
//    test();


    if (argc != 2) {
        printf("enter file path!\n");
        exit(1);
    }
    string file = string(argv[1]);
    Lancer lancer;
    lancer.ReadFile(file);
    lancer.OnDestroy();
    return 0;
}



