#include <stdlib.h>

int fact(int x)
{
    int res = 1;
    for (int i = 2; i <= x; i++) {
        res *= i;
    }

    return res;
}

float E(int x)
{
    float sum = 0;

    for (int i = 0; i <= x; i++) {
        sum += (1 / (float)fact(i));
    }
    
    return sum;
}

int GCF(int A, int B)
{
    A = abs(A);
    B = abs(B);
    int min_num = (A < B) ? A : B;

    for (int i = min_num; i > 0; i--) {
        if (A % i == 0 && B % i == 0) {
            return i;
        }
    }

    return 1;
}