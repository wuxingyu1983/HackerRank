//
//  main.cpp
//  test
//
//  Created by 吴星煜 on 2018/4/5.
//  Copyright © 2018年 吴星煜. All rights reserved.
//

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

int lsum[MAX];

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
            if (z > 0 && y <= z && z <= a[3]) {
                lcnt[1][s] ++;
            }
        }

        lsum[1] += lcnt[1][s];

        for (int y = 1; y <= a[2] - 1; y++) {
            z = s ^ y;
            if (z > 0 && y <= z && z <= a[3]) {
                lcnt[y + 1][s] = lcnt[y][s] - 1;
            }
            else {
                lcnt[y + 1][s] = lcnt[y][s];
            }

            lsum[y + 1] += lcnt[y + 1][s];
        }
    }

    unsigned long long ret = 0;

    for (int w = 1; w <= a[0]; w ++) {
        for (int x = w; x <= a[1]; x ++) {
            int s = w ^ x;
            ret += lsum[x] - lcnt[x][s];
        }
    }

    printf("%llu\n", ret);

    return 0;
}
