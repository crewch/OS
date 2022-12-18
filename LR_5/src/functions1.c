#include <stdlib.h>

int fact(int x)
{
    int res = 1;
    for (int i = 2; i <= x; i++) {
        res *= i;
    }

    return res;
}

float power(float base, int exp) {
    float result = 1;
    for (int i = 0; i < exp; i++)
        result *= base;
    return result;
}

float E(int x)
{
    return power(1 + 1 / (float)x, x);
}

int GCF(int A, int B)
{
    while (B ^= A ^= B ^= A %= B);
    return abs(A);
}