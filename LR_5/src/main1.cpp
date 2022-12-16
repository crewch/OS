#include <bits/stdc++.h>

#include "../include/lib.h"

using namespace std;

int main()
{
    int com = 0;
    while (scanf("%d", &com) != EOF) {
        switch (com) {
        case 1:
            int a1;
            cin >> a1;
            cout << E(a1) << endl;
            break;
        case 2:
            int a2, b2;
            cin >> a2 >> b2;
            cout << GCF(a2, b2) << endl;
            break;
        default:
            cout << "Неправильная команда" << endl;
            break;
        }
    }
}