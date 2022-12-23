#include "functions.h"
#include "stdio.h"

#ifdef SYSTEM
    #define PRINT_OS printf("Operation system: %s\n", SYSTEM)
#else
    #define PRINT_OS
#endif

int main()
{
    while (1) {
        int target;
        scanf("%d", &target);

        if (target == 1) {
            int a, b;
            scanf("%d %d", &a, &b);
            PRINT_OS;
            printf("GCF: %d\n", GCF(a, b));
        } else if (target == 2) {
            int x;
            scanf("%d", &x);
            PRINT_OS;
            printf("E: %f\n", E(x));
        } else if (target == -1)
            break;
    }
    
    return 0;
}