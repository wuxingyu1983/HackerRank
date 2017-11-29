#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MOD         1000000007

long long * * cnt1;
long long * * cnt2;

int main() {
    int l, n, m;
    long long c;

    scanf("%d %d %d %lld", &l, &n, &m, &c);

    // malloc
    cnt1 = (long long * *)malloc((n + 1) * sizeof(long long *));
    for (size_t i = 0; i <= n; i++) {
        cnt1[i] = (long long *)malloc(m * sizeof(long long));
        memset(cnt1[i], 0xff, m * sizeof(long long));
    }

    cnt2 = (long long * *)malloc((n + 1) * sizeof(long long *));
    for (size_t i = 0; i <= n; i++) {
        cnt2[i] = (long long *)malloc(m * sizeof(long long));
        memset(cnt2[i], 0xff, m * sizeof(long long));
    }

    long long sum = 0;

    cnt1[0][0] = (c - 2) % MOD;
    cnt1[0][1] = 1;
    cnt1[1][0] = 1;

    sum += ((long long)(c % MOD)) * (long long)n % MOD;

    long long * * now = cnt2;
    long long * * pre = cnt1;

    for (size_t day = 2; day <= l; day++) {
        int max_n = (n < day) ? n : day;
        for (size_t in = 0; in <= max_n; in++) {
            long long tmp = 0;
            int max_m = ((m - 1) < (day - in)) ? (m - 1) : (day - in);
            for (size_t im = 0; im <= max_m; im++) {
                if (0 == im) {
                    for (size_t i = 0; i < m; i++) {
                        if (0 > pre[in][i]) {
                            break;
                        }
                        tmp += pre[in][i] * (long long)((c - 2) % MOD);
                        tmp %= MOD;
                    }

                    if (in > 0) {
                        for (size_t i = 0; i < m; i++) {
                            if (0 > pre[in - 1][i]) {
                                break;
                            }
                            tmp += pre[in - 1][i];
                            tmp %= MOD;
                        }
                    }

                    now[in][im] = tmp;
                }
                else {
                    now[in][im] = pre[in][im - 1];
                }
//                printf("day = %zu, now[%zu][%zu] = %lld\n", day, in, im, now[in][im]);

                if (0 == in) {
                    sum += (long long)n * (long long)now[in][im];
                    sum %= MOD;
                }
                else {
                    sum += (long long)(n - in + 1) * (long long)now[in][im];
                    sum %= MOD;
                }
            }
        }

        if (now == cnt2) {
            now = cnt1;
            pre = cnt2;
        }
        else {
            now = cnt2;
            pre = cnt1;
        }
    }

    printf("%lld\n", sum);

    return 0;
}
