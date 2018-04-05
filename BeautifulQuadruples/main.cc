#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX      4096       // 0xFFF

int lcnt[MAX][MAX];
int rcnt[MAX][MAX];

int main() {
    vector<int> a;
    a.resize(4);
    scanf("%d %d %d %d", &a[0], &a[1], &a[2], &a[3]);

    // sort, asc order
    sort(a.begin(), a.end());

    for (int s = 0; s < MAX; s++) {
        int z;
        for (int y = 1; y <= a[3]; y++) {
            z = s ^ y;
            if (y <= z) {
                lcnt[1][s] ++;
            }
        }

        for (int y = 2; y <= a[3]; y++) {
            z = s ^ y;
            if (y <= z) {
                lcnt[y][s] = lcnt[y - 1][s] - 1;
            }
            else {
                lcnt[y][s] = lcnt[y - 1][s];
            }
        }
    }

    for (int s = 0; s < MAX; s++) {
        int w;
        for (int x = 1; x <= a[2]; x++) {
            w = s ^ x;
            if (w <= x) {
                rcnt[a[2]][s] ++;
            }
        }

        for (int x = a[2] - 1; x > 0; x--) {
            w = s ^ x;
            if (w <= x) {
                rcnt[x][s] = rcnt[x + 1][s] - 1;
            }
            else {
                rcnt[x][s] = rcnt[x + 1][s];
            }
        }
    }

    unsigned long long ret = 0;

    

    printf("%llu\n", ret);

    return 0;
}
