//
//  main.cpp
//  test
//
//  Created by 吴星煜 on 2018/1/22.
//  Copyright © 2018年 吴星煜. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

#define DEBUG       1

using namespace std;

int main() {
    int t;

#if DEBUG
    FILE * fp = fopen("input.txt", "r");

    fscanf(fp, "%d", &t);
#else
    scanf("%d", &t);
#endif

    for (size_t i_t = 0; i_t < t; i_t++) {
        int n, g;

#if DEBUG
        fscanf(fp, "%d %d", &n, &g);
#else
        scanf("%d %d", &n, &g);
#endif

        int sum = 0;
        int * a = (int *)malloc(n * sizeof(int));

        for (size_t i_n = 0; i_n < n; i_n++) {
#if DEBUG
            fscanf(fp, "%d", &a[i_n]);
#else
            scanf("%d", &a[i_n]);
#endif

            sum += a[i_n];
        }

        char * flag = (char *)malloc(sum + 1);
        memset(flag, 0, sum + 1);

        int max = 0, tmp_max = 0;
        flag[0] = 1;

        for (size_t i_n = 0; i_n < n; i_n++) {
            for (int j = max; j >= 0; j--) {
                if (1 == flag[j]) {
                    flag[j + a[i_n]] = 1;

                    if (j + a[i_n] > tmp_max) {
                        tmp_max = j + a[i_n];
                    }
                }
            }

            max = tmp_max;
        }

        size_t j;
        for (j = 0; j <= max; j++) {
            if (1 == flag[j] && 1 == flag[sum - j]) {
                if (j <= g && (sum - j) <= g) {
                    break;
                }
            }
        }

        if (j > max) {
            printf("NO\n");
        }
        else {
            printf("YES\n");
        }

        free(flag);
        free(a);
    }

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
