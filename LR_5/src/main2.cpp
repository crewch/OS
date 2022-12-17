#include <bits/stdc++.h>
#include <dlfcn.h>

#include "../build/version.h"
#include "../include/lib.h"

using namespace std;

const char* lib1 = "./liblib1.so";
const char* lib2 = "./liblib2.so";

int main(int argc, char* argv[])
{
    if (prnt == "EXTENDED") {
        cout << g_version << "\n";
    }
    if (argc == 1) {
        perror("INCORRECT INPUT KEYS (need more arguments)\n");
        exit(0);
    } else {
        if (*argv[1] == '1') {
            void* lib;
            lib = dlopen("liblib1.so", RTLD_LAZY);
            if (!lib) {
                perror("cannot open library\n");
                exit(0);
            }
            if ((argc % 2) != 0) {
                perror("INCORRECT INPUT KEYS (for every computation of dif 2 args needed)\n");
                exit(0);
            } else {
                int glob = 1;

                double (*fun)(double a, double d);
                fun = (double (*)(double, double))dlsym(lib, "dif1");
                printf("Current method - 1\n");

                for (int i = 2; i < argc; i += 2) {
                    int sw;
                    cout << "Enter '0' if you want to switch, '1' otherwise\n";
                    cin >> sw;

                    if (sw == 0) {
                        glob = (glob + 1) % 2;
                        if (glob == 1) {
                            fun = (double (*)(double, double))dlsym(lib, "dif1");
                        }
                        else {
                            fun = (double (*)(double, double))dlsym(lib, "dif2");
                        }
                    }

                    if (glob == 1) {
                        cout << fun(atof(argv[i]), atof(argv[i + 1])) << "\n";
                        cout << "Current method - 1\n";
                    }
                    else {
                        cout << fun(atof(argv[i]), atof(argv[i + 1])) << "\n";
                        cout << "Current method - 2\n";
                    }
                }
                dlclose(lib);
            }
        } else if (*argv[1] == '2') {
            if ((argc % 2) != 0) {
                perror("INCORRECT INPUT KEYS (for every computation of dif 2 args needed)\n");
                exit(0);
            } else {
                void* lib;
                lib = dlopen("liblib2.so", RTLD_LAZY);
                if (!lib) {
                    perror("cannot open library\n");
                    exit(0);
                }
                int glob = 1;

                int (*fun)(int a, int b);
                fun = (int (*)(int, int))dlsym(lib, "nod_ev");

                printf("Current method - euclid\n");

                for (int i = 2; i < argc; i += 2) {
                    int sw;
                    cout << "Enter '0' if you want to switch, '1' otherwise\n";
                    cin >> sw;

                    if (sw == 0) {
                        glob = (glob + 1) % 2;
                        if (glob == 1) {
                            fun = (int (*)(int, int))dlsym(lib, "nod_ev");
                        } else {
                            fun = (int (*)(int, int))dlsym(lib, "nod_simp");
                        }
                    }

                    if (glob == 1) {
                        cout << fun(atoi(argv[i]), atoi(argv[i + 1])) << "\n";
                        cout << "Current method - euclid\n";
                    } else {
                        cout << fun(atoi(argv[i]), atoi(argv[i + 1])) << "\n";
                        cout << "Current method - simple\n";
                    }
                }
            }
        }
        return 0;
    }
}