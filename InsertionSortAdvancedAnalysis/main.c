#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

unsigned long long getMoves(int * a, int len) {
    unsigned long long ret = 0;
    int * s = malloc(sizeof(int) * len);
    memset(s, 0, sizeof(int) * len);

    int start = -1, end = -1;

    for (size_t i = 0; i < len; i++) {
        if (0 > start) {
            start = 0;
            s[start] = a[i];
            end = 0;
        }
        else {
            int add = 0;
/*
            if (a[i] <= s[start]) {
                s[-- start] = a[i];
                int tmp = start;
                while (tmp <= end && s[tmp] == a[i]) {
                    tmp ++;
                }
                add = end - tmp + 1;
            }
            else if (a[i] >= s[end]) {
                s[++ end] = a[i];
            }
            else */
            {
                // 二分法找到位置
                int l, r, m;
                l = start;
                r = end;
                while (l <= r) {
                    m = (l + r) / 2;
                    if (a[i] == s[m]) {
                        break;
                    }
                    else if (a[i] < s[m]) {
                        r = m - 1;
                    }
                    else {
                        l = m + 1;
                    }
                }

                if (s[m] == a[i]) {
                    while (s[m] == a[i]) {
                        m ++;
                    }
                }
                else if (s[m] > a[i]) {
                }
                else {
                    m ++;
                }

                for (size_t j = end + 1; j > m; j --) {
                    s[j] = s[j - 1];
                }
                s[m] = a[i];
                add = end - m + 1;
                end ++;
/*
                if (end - m + 1 <= m - start) {
                    memcpy(&s[m + 1], &s[m], sizeof(int) * (end - m + 1));
                    add = end - m + 1;
                    end ++;
                }
                else {
                    memcpy(&s[start - 1], &s[start], sizeof(int) * (m - start));
                    add = end - m + 1;
                    start --;
                }
*/
/*
            for (size_t i = start; i <= end; i ++){
                printf("%d ", s[i]);
            }
            printf(", add is %d, m is %d\n", add, m);
*/
            }

            ret += add;
        }
    }

    free(s);

    return ret;
}

int main() {
    int T;
    scanf("%d", &T);

    unsigned long long * output;
    output = malloc(sizeof(long long) * T);

    for (size_t i = 0; i < T; i++) {
        int N;
        int * a;

        scanf("%d", &N);
        a = malloc(sizeof(int) * N);

        for (size_t j = 0; j < N; j++) {
            scanf("%d", &a[j]);
        }

        output[i] = getMoves(a, N);

        free(a);
    }

    for (size_t i = 0; i < T; i++) {
        printf("%llu\n", output[i]);
    }

    free(output);

    return 0;
}
