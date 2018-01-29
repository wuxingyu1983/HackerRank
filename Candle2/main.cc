//
//  main.cpp
//  test
//
//  Created by 吴星煜 on 2018/1/29.
//  Copyright © 2018年 吴星煜. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define DEBUG       0
#define MOD         1000000007
#define MAX         50001

int sum[128][MAX];
int bit[128][MAX];

// Return sum from 0...i from array
int getSum(int * fw, int i)
{
    long long sum = 0;
    // Fenwick's index start from 1
    i++;

    while(i > 0)
    {
        sum += fw[i];
        sum = sum % MOD;
        // i & (-i)  returns the decimal value of last set digit
        // eg: if i = 12 (1100) then  i & (-i) will 4 (100)
        i -= i & (-i);
    }
    return (int)sum;
}

// newVal will be updated to Fenwick and all its ancestor
void updateFW(int * fw, int n, int i, long long newVal)
{
    // Fenwick's index start from 1
    i++;
    while (i <= n)
    {
        long long tmp = (long long)(fw[i]) + newVal;
        fw[i] = (tmp + MOD) % MOD;
        i += i & (-i);
    }
}

int main() {
#if DEBUG
    FILE * fp = fopen("input.txt", "r");
#endif

    int n, k;

#if DEBUG
    fscanf(fp, "%d %d", &n, &k);
#else
    scanf("%d %d", &n, &k);
#endif

    long long ret = 0;

    int * height = (int *)malloc(n * sizeof(int));
    int * color = (int *)malloc(n * sizeof(int));

    for (size_t i = 0; i < n; i++) {
#if DEBUG
        fscanf(fp, "%d %d", &height[i], &color[i]);
#else
        scanf("%d %d", &height[i], &color[i]);
#endif
    }

    for (size_t i = 0; i < n; i++) {
        int h = height[i];
        int c = color[i];

        for (int j = 0; j < 1 << k; j++) {
            long long addition = getSum(bit[j], h - 1);

            if (0 == j && 0 == addition) {
                addition = 1;
            }

            int new_j = j | (1 << (c - 1));

            int pre_value = sum[new_j][h];

            long long new_value = sum[new_j][h] + addition;
            new_value = new_value % MOD;

            sum[new_j][h] = (int)new_value;

            if (0 != (new_value - pre_value)) {
                updateFW(bit[new_j], MAX, h, (new_value - pre_value));
            }
        }
    }

    int j = (1 << k) - 1;
    for (size_t i = 0; i < MAX; i++) {
        ret += (long long)sum[j][i];
        ret = ret % MOD;
    }

    printf("%lld\n", ret);

#if DEBUG
    fclose(fp);
#endif
    return 0;
}
