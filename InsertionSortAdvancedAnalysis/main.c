#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

unsigned long long getMoves(int * a, int len) {
    unsigned long long ret = 0;
    int * s = malloc(sizeof(int) * len * 2);
    memset(s, 0, sizeof(int) * len * 2);

    int start = -1, end = -1;

    for (size_t i = 0; i < len; i++) {
        if (0 > start) {
            start = len;
            s[start] = a[i];
            end = len;
        }
        else {
            int add = 0;
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

            if (end - m + 1 <= m - start) {
                for (size_t j = end + 1; j > m; j --) {
                    s[j] = s[j - 1];
                }
                s[m] = a[i];
                add = end - m + 1;
                end ++;
            }
            else {
                for (size_t j = start; j < m; j ++) {
                    s[j - 1] = s[j];
                }
                s[m - 1] = a[i];
                add = end - m + 1;
                start --;
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
