#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

unsigned long long merge_sort(int * a, int s, int e) {
    unsigned long long ret = 0;

    if (s < e) {
        int middle = (s + e) / 2;

        ret += merge_sort(a, s, middle);
        ret += merge_sort(a, middle + 1, e);

        int * t = malloc(sizeof(int) * (e - s + 1));
        memset(t, 0 , sizeof(int) * (e - s + 1));

        int i = s, j = middle + 1;
        for (size_t k = s; k <= e; k++) {
            if (i <= middle && j <= e) {
                if (a[i] <= a[j]) {
                    t[k - s] = a[i];
                    if (k > i) {
                        ret += k - i;
                    }
                    i ++;
                }
                else {
                    t[k - s] = a[j];
                    if (k > j) {
                        ret += k - j;
                    }
                    j ++;
                }
            }
            else {
                if (i <= middle) {
                    t[k - s] = a[i];
                    if (k > i) {
                        ret += k - i;
                    }
                    i ++;
                }
                else {
                    t[k - s] = a[j];
                    if (k > j) {
                        ret += k - j;
                    }
                    j ++;
                }
            }
        }

        memcpy(&a[s], t, sizeof(int) * (e - s + 1));

        free(t);
    }

    return ret;
}

unsigned long long getMoves(int * a, int len) {
    unsigned long long ret = 0;

    ret = merge_sort(a, 0, len - 1);

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
