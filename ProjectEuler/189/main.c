//
//  main.c
//  189
//
//  Created by 吴星煜 on 2017/12/11.
//  Copyright © 2017年 吴星煜. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG       0
#define MOD         1000000007

unsigned char bits[] = {1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4};

int getIndex(int level[], int c) {
    int ret = 0;

    int i = 0;
    while (0 <= level[i]) {
        ret = ret << bits[c];
        ret += level[i];

        i ++;
    }

    return ret;
}

long long getMultiplier(int pre_level[], int now_level[], int c) {
    long long ret = 1;

    int i = 0;
    while (0 <= pre_level[i]) {
        int same = 0;
        if (pre_level[i] == now_level[i]) {
            same ++;
        }
        if (pre_level[i] == now_level[i + 1]) {
            same ++;
        }

        if (0 == (c - 3 + same)) {
            return 0;
        }
        else {
            ret *= (long long)(c - 3 + same);
        }

        i ++;
    }

    return ret;
}

int main() {
    long long ret = 0;

    int n, c;
    scanf("%d %d", &n, &c);

    if (1 == n) {
        printf("%d\n", c);
        return 0;
    }

    if (1 == c) {
        printf("0\n");
        return 0;
    }

    int arry_size = pow(2, bits[c] * ((n - 1) ? (n - 1) : 1));

    long long * tmp1 = (long long *)malloc(arry_size * sizeof(long long));
    long long * tmp2 = (long long *)malloc(arry_size * sizeof(long long));
    memset(tmp1, 0, arry_size * sizeof(long long));
    memset(tmp2, 0, arry_size * sizeof(long long));

    for (size_t i = 0; i < c; i++) {
        tmp1[i] = 1;
    }

    long long * now = tmp2;
    long long * pre = tmp1;

    int now_level[15];
    int pre_level[15];
    for (size_t j = 2; j <= n - 1; j++) {
        if (0 < j - 2) {
            // clean array tmp
            arry_size = pow(2, (j - 2) * bits[c]);
            memset(now, 0, arry_size * sizeof(long long));
        }

        for (size_t i = 0; i < j; i++) {
            now_level[i] = 0;
        }
        now_level[j] = -1;

        while (true) {
            for (size_t i = 0; i < j - 1; i++) {
                pre_level[i] = 0;
            }
            pre_level[j - 1] = -1;

            int now_index = getIndex(now_level, c);

            while (true) {
                // proc
                int pre_index = getIndex(pre_level, c);

                // debug
                #if DEBUG
                printf("compare :\n");
                printf("pre level is : ");
                for (size_t i = 0; true; i++) {
                    if (0 > pre_level[i]) {
                        printf("\n");
                        break;
                    }
                    else {
                        printf("%d ", pre_level[i]);
                    }
                }
                printf("now level is : ");
                for (size_t i = 0; true; i++) {
                    if (0 > now_level[i]) {
                        printf("\n");
                        break;
                    }
                    else {
                        printf("%d ", now_level[i]);
                    }
                }
                #endif
                if (pre[pre_index]) {
                    long long multiplier = getMultiplier(pre_level, now_level, c);

                    if (0 < multiplier) {
                        long long product = pre[pre_index];
                        product *= multiplier;
                        product %= MOD;

                        now[now_index] += product;
                        now[now_index] %= MOD;
                    }
                }

                // 遍历 pre_level
                {
                    int pos = j - 2;
                    while (c - 1 == pre_level[pos] && pos >= 0) {
                        pos --;
                    }

                    if (0 > pos) {
                        break;
                    }
                    else {
                        pre_level[pos] ++;
                        for (size_t i = pos + 1; i < j - 1; i++) {
                            pre_level[i] = 0;
                        }
                    }
                }
            }

            // 遍历 now_level
            {
                int pos = j - 1;
                while (c - 1 == now_level[pos] && pos >= 0) {
                    pos --;
                }

                if (0 > pos) {
                    break;
                }
                else {
                    now_level[pos] ++;
                    for (size_t i = pos + 1; i < j; i++) {
                        now_level[i] = 0;
                    }
                }
            }
        }

        if (now == tmp2) {
            pre = tmp2;
            now = tmp1;
        }
        else {
            pre = tmp1;
            now = tmp2;
        }
    }

    // j == n
    {
        size_t j = n;

        for (size_t i = 0; i < j; i++) {
            now_level[i] = 0;
        }
        now_level[j] = -1;

        while (true) {
            for (size_t i = 0; i < j - 1; i++) {
                pre_level[i] = 0;
            }
            pre_level[j - 1] = -1;

            while (true) {
                // proc
                int pre_index = getIndex(pre_level, c);

                // debug
                #if DEBUG
                printf("compare :\n");
                printf("pre level is : ");
                for (size_t i = 0; true; i++) {
                    if (0 > pre_level[i]) {
                        printf("\n");
                        break;
                    }
                    else {
                        printf("%d ", pre_level[i]);
                    }
                }
                printf("now level is : ");
                for (size_t i = 0; true; i++) {
                    if (0 > now_level[i]) {
                        printf("\n");
                        break;
                    }
                    else {
                        printf("%d ", now_level[i]);
                    }
                }
                #endif

                if (pre[pre_index]) {
                    long long multiplier = getMultiplier(pre_level, now_level, c);

                    if (0 < multiplier) {
                        long long product = pre[pre_index];
                        product *= multiplier;
                        product %= MOD;

                        ret += product;
                        ret %= MOD;
                    }
                }

                // 遍历 pre_level
                {
                    int pos = j - 2;
                    while (c - 1 == pre_level[pos] && pos >= 0) {
                        pos --;
                    }

                    if (0 > pos) {
                        break;
                    }
                    else {
                        pre_level[pos] ++;
                        for (size_t i = pos + 1; i < j - 1; i++) {
                            pre_level[i] = 0;
                        }
                    }
                }
            }

            // 遍历 now_level
            {
                int pos = j - 1;
                while (c - 1 == now_level[pos] && pos >= 0) {
                    pos --;
                }

                if (0 > pos) {
                    break;
                }
                else {
                    now_level[pos] ++;
                    for (size_t i = pos + 1; i < j; i++) {
                        now_level[i] = 0;
                    }
                }
            }
        }
    }

    printf("%lld\n", ret);

    return 0;
}
