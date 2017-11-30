#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MOD         1000000007

long long * * cnt1;
long long * * cnt2;

int main() {
    long long l, n, m;
    long long c;

    scanf("%lld %lld %lld %lld", &l, &n, &m, &c);

    long long * * s = (long long * *)malloc((n + 1) * sizeof(long long *));
    for (size_t i = 0; i <= n; i++) {
        s[i] = (long long *)malloc(m * sizeof(long long));
        memset(s[i], 0, m * sizeof(long long));
    }

    long long * sum_day = (long long *)malloc((n + 1) * sizeof(long long));
    memset(sum_day, 0, (n + 1) * sizeof(long long));

    int * p = (int *)malloc(m * sizeof(int));
    memset(p, 0, m * sizeof(int));

    long long sum = 0;

    // day 1
    s[0][0] = (c - 2) % MOD;
    s[0][1] = 1;
    sum_day[0] = (c - 1) % MOD;

    s[1][0] = 1;
    sum_day[1] = 1;

    sum = ((c % MOD) * n) % MOD;

    for (size_t day = 2; day <= l; day++) {
        long long max_n = n;
        if (day <= n) {
            s[day][0] = 1;
            sum_day[day] = 1;

            sum += (n - day + 1);
            sum %= MOD;

            max_n = day - 1;
        }

        for (long long i = max_n; i >= 0; i--) {
            p[i] = (p[i] - 1 + m) % (m);
            long long pre = s[i][p[i]];

            s[i][p[i]] = (sum_day[i] * ((c - 2) % MOD)) % MOD;
            if (i > 0) {
                s[i][p[i]] += sum_day[i - 1];
            }
            s[i][p[i]] %= MOD;
            sum_day[i] += s[i][p[i]];
            sum_day[i] -= pre;
            if (0 > sum_day[i]) {
                sum_day[i] += MOD;
            }
            sum_day[i] %= MOD;

//            printf("sum_day[%d] = %lld\n", i, sum_day[i]);

            if (0 == i) {
                sum += sum_day[i] * n;
            }
            else {
                sum += sum_day[i] * (n - i + 1);
            }

            sum %= MOD;
        }
    }

    printf("%lld\n", sum);

    return 0;
}
