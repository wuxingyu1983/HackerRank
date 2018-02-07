//
//  main.cpp
//  test
//
//  Created by Leo Ng on 2018/2/6.
//  Copyright © 2018年 Leo Ng. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define DEBUG   0
#define MOD     1000000007

int x[100];
long long s_cnt[101];
long long d_cnt[101];

int cnt[2001][101];

int main() {
#if DEBUG
    FILE * fp = fopen("input.txt", "r");
#endif

    int m, r, s;
#if DEBUG
    fscanf(fp, "%d %d %d", &m, &r, &s);
#else
    scanf("%d %d %d", &m, &r, &s);
#endif

    for (size_t i = 0; i < m; i++) {
#if DEBUG
        fscanf(fp, "%d", &x[i]);
#else
        scanf("%d", &x[i]);
#endif
    }

    int sum = (r + s) / 2;
    int diff = (r - s) / 2;

    for (size_t i = 0; i < m; i++) {
        for (int s = 2000; s >= 0; s--) {
            for (int c = 100; c >= 0; c--) {
                long long new_cnt = 0;
                if (0 == s && 0 == c) {
                    new_cnt = cnt[x[i]][c + 1] + 1;
                    new_cnt %= MOD;
                    cnt[x[i]][c + 1] = new_cnt;

                    if (sum == x[i]) {
                        s_cnt[c + 1] += 1;
                        s_cnt[c + 1] %= MOD;
                    }
                    if (diff == x[i]) {
                        d_cnt[c + 1] += 1;
                        d_cnt[c + 1] %= MOD;
                    }
                }
                else {
                    if (0 < cnt[s][c]) {
                        if (s + x[i] <= 2000) {
                            new_cnt = cnt[s + x[i]][c + 1] + cnt[s][c];
                            new_cnt %= MOD;
                            cnt[s + x[i]][c + 1] = new_cnt;

                            if (sum == (x[i] + s)) {
                                s_cnt[c + 1] += cnt[s][c];
                                s_cnt[c + 1] %= MOD;
                            }
                            if (diff == (x[i] + s)) {
                                d_cnt[c + 1] += cnt[s][c];
                                d_cnt[c + 1] %= MOD;
                            }
                        }
                    }
                }
            }
        }
    }

    long long ret = 0;
    for (size_t i = 1; i <= 100; i++) {
        if (s_cnt[i] && d_cnt[i]) {
            ret += (s_cnt[i] * d_cnt[i]) % MOD;
            ret %= MOD;
        }
    }

    printf("%lld\n", ret);

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
