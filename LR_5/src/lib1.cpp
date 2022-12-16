#include <bits/stdc++.h>

#include "../include/lib.h"

using namespace std;

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
    return pow(1 + 1 / float(x), x);
}

int GCF(int A, int B)
{
    while (B ^= A ^= B ^= A %= B);
    return abs(A);
}