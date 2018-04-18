#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MOD         1000000007
#define DEBUG		0

int main() {
    int n;
    scanf("%d", &n);

    vector<unsigned long long> a;
    a.resize(n);

    unsigned long long sum = 0;
    unsigned long long cnt = 0;    // the count of cities
    unsigned long long bs = 0;
    unsigned long long lpath = 0;

    for (size_t i = 0; i < n; i++) {
        scanf("%llu", &a[i]);

        if (0 == i) {
            sum = 29 * a[i];
            cnt = 6;
            bs = 11 * a[i];
            lpath = 3 * a[i];
        }
        else {
            // 周边4个角落的
            unsigned long long new_sum = (sum * 4) % MOD;

            // 中间部分
            new_sum += 29 * a[i];
            new_sum %= MOD;

            // 角落到角落
            new_sum += ((cnt - 1) * 2 * bs * 3 % MOD + ((cnt - 1) * (cnt - 1) % MOD) * (2 * a[i] + 2 * 3 * a[i])) * 2 % MOD;
            new_sum %= MOD;

            // 角落到中间
            new_sum += (bs * 5 + (cnt - 1) * 11 * a[i]) * 4 % MOD;

            // 计算新的bs
            unsigned long long new_bs = bs;
            new_bs += bs * 3 + 8 * a[i] * cnt % MOD + cnt * lpath * 3 % MOD + 2 * a[i] + lpath + a[i] + lpath;

            sum = new_sum % MOD;
            cnt = (4 * cnt + 2) % MOD;
            bs = new_bs % MOD;
            lpath = (lpath * 2 + 3 * a[i]) % MOD;
        }
    }

    printf("%llu\n", sum);

    return 0;
}
