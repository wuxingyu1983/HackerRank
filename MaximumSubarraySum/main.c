#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int M;

void merge_func(long long * a, int s, int e, long long * max) {
    if (s < e) {
        int middle = (s + e) / 2;

        merge_func(a, s, middle, max);
        merge_func(a, middle + 1, e, max);

        if (a[e] > a[s] && (a[e] - a[s]) > *max) {
            *max = a[e] - a[s];
        }

        long long * t = malloc(sizeof(long long) * (e - s + 1));
        memset(t, 0 , sizeof(long long) * (e - s + 1));

        int i = s, j = middle + 1;
        for (size_t k = s; k <= e; k++) {
            if (i <= middle && j <= e) {
                if (a[i] <= a[j]) {
                    t[k - s] = a[i];
                    i ++;
                }
                else {
                    // a[i] > a[j]
                    if (*max < (M - (a[i] - a[j]))) {
                        *max = M - (a[i] - a[j]);
                    }
                    t[k - s] = a[j];
                    j ++;
                }
            }
            else {
                if (i <= middle) {
                    t[k - s] = a[i];
                    i ++;
                }
                else {
                    t[k - s] = a[j];
                    j ++;
                }
            }
        }

        memcpy(&a[s], t, sizeof(long long) * (e - s + 1));

        free(t);
    }
}

int main() {
    int T;
    scanf("%d", &T);

    long long * output = malloc(sizeof(long long) * T);
    long long input[100000];

    for (size_t ti = 0; ti < T; ti++) {
        int N;
        scanf("%d %d", &N, &M);

        long long sum = 0;
        long long max = 0;
        for (size_t ni = 0; ni < N; ni++) {
            long long n;
            scanf("%lld", &n);
            n = n % M;

            if (n > max) {
                max = n;
            }

            sum += n;
            sum = sum % M;

            if (sum > max) {
                max = sum;
            }

            input[ni] = sum;
        }

        if (max != (M - 1)) {
            merge_func(input, 0, N - 1, &max);
        }
        output[ti] = max;
    }

    for (size_t ti = 0; ti < T; ti++) {
        printf("%lld\n", output[ti]);
    }

    free(output);

    return 0;
}
