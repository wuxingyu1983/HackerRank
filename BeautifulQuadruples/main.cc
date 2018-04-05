#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX      4096       // 0 - 0xFFF

int lcnt[MAX][MAX];
int rcnt[MAX][MAX];

int lsum[MAX];
int rsum[MAX];

int main() {
    vector<int> a;
    a.resize(4);
    scanf("%d %d %d %d", &a[0], &a[1], &a[2], &a[3]);

    // sort, asc order
    sort(a.begin(), a.end());

    for (int s = 0; s < MAX; s++) {
        int z;
        for (int y = 1; y <= a[2]; y++) {
            z = s ^ y;
            if (y <= z && z <= a[3]) {
                lcnt[1][s] ++;
            }
        }

        lsum[1] += lcnt[1][s];

        for (int y = 2; y <= a[2]; y++) {
            z = s ^ y;
            if (y <= z && z <= a[3]) {
                lcnt[y][s] = lcnt[y - 1][s] - 1;
            }
            else {
                lcnt[y][s] = lcnt[y - 1][s];
            }

            lsum[y] += lcnt[y][s];
        }
    }

    for (int s = 0; s < MAX; s++) {
        int w;
        for (int x = 1; x <= a[1]; x++) {
            w = s ^ x;
            if (w <= x && w <= a[0]) {
                rcnt[a[1]][s] ++;
            }
        }

        rsum[a[1]] += rcnt[a[1]][s];

        for (int x = a[1] - 1; x > 0; x--) {
            w = s ^ x;
            if (w <= x && w <= a[0]) {
                rcnt[x][s] = rcnt[x + 1][s] - 1;
            }
            else {
                rcnt[x][s] = rcnt[x + 1][s];
            }

            rsum[x] += rcnt[x][s];
        }
    }

    unsigned long long ret = 0;

    for (size_t i = 1; i <= a[1]; i++) {
        for (size_t j = 0; j < MAX; j++) {
            if (rcnt[i][j]) {
                ret += (unsigned long long)rcnt[i][j] * (unsigned long long)(lsum[j] - lcnt[i][j]);
            }
        }
    }

    printf("%llu\n", ret);

    return 0;
}
