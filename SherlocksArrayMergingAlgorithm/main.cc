//
//  main.cpp
//  test
//
//  Created by 吴星煜 on 2018/4/7.
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

#define MOD     1000000007
#define MAX_N   15

unsigned long long cnt[MAX_N + 1][MAX_N + 1];

int main() {
    int n;
    scanf("%d", &n);

    vector<int> vec_m;
    vec_m.reserve(n);

    int m;
    for (size_t i = 0; i < n; i++) {
        scanf("%d", &m);
        vec_m.push_back(m);
    }

    for (int c = 1; c <= n; c ++) {
        for (int i = n - c; i >= 0; i --) {
            if (1 == c) {
                cnt[i][c] = 1;
            }
            else {
                if (0 < cnt[i + 1][c - 1] && vec_m[i] < vec_m[i + 1]) {
                    if (i + c >= n) {
                        cnt[i][c] = 1;
                    }
                    else {
                        unsigned long long tmp = c;
                        for (int j = 1, c1 = c; j <= c; j ++, c1 --) {
                            cnt[i][c] += cnt[i + c][j] * tmp;
                            cnt[i][c] %= MOD;
                            tmp *= c1 - 1;
                            tmp %= MOD;
                        }
                    }
                }
            }
        }
    }

    unsigned long long ret = 0;

    for (int i = 1; i <= n; i ++) {
        ret += cnt[0][i];
        ret %= MOD;
    }

    printf("%llu\n", ret);

    return 0;
}
