#include <stdio.h>
#include <dlfcn.h>

#ifdef SYSTEM
    #define PRINT_OS printf("Operation system: %s\n", SYSTEM)
#else
    #define PRINT_OS
#endif

#define CHECK_ERROR(expr, message) \
    do \
    { \
        void* res = (expr); \
        if (res == NULL) \
        { \
            perror(message); \
            return -1; \
        } \
    } while (0)

const int N = 2;
const char* names[] = {"./liblib1.so", "./liblib2.so"};

int main()
{
    int n = 0;
    void* handle;
    float(*E)(int);
    int(*GCF)(int, int);
    CHECK_ERROR(handle = dlopen(names[n], RTLD_LAZY), "dlopen error");
    CHECK_ERROR(E = dlsym(handle, "E"), "dlsym error (E)");
    CHECK_ERROR(GCF = dlsym(handle, "GCF"), "dlsym error (GCF)");

    while(1)
    {
        int t;
        scanf("%d", &t);
        if (t == 0)
        {
            n = (n + 1) % N;
            if (dlclose(handle) != 0)
            {
                perror("dlclose error");
                return -1;
            };
            CHECK_ERROR(handle = dlopen(names[n], RTLD_LAZY), "dlopen error");
            CHECK_ERROR(E = dlsym(handle, "E"), "dlsym error (E)");
            CHECK_ERROR(GCF = dlsym(handle, "GCF"), "dlsym error (GCF)");
        }
        if (t == 1)
        {
            int a, b;
            scanf("%d %d", &a, &b);
            PRINT_OS;
            printf("GCF: %d\n", (*GCF)(a, b));
        }
        if (t == 2)
        {
            int x;
            scanf("%d", &x);
            PRINT_OS;
            printf("E: %f\n", (*E)(x));
        }
        if (t == -1)
            break;
    }
}