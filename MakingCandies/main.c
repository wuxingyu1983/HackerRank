#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

unsigned long long makingCandy( unsigned long long m,
    unsigned long long w,
    unsigned long long p,
    unsigned long long sum,
    unsigned long long n)
    {
        unsigned long long ret = 0;

        if (n > sum) {
            // 按照当前速率
            if (0 == (n - sum) % (m * w)) {
                ret = (n - sum) / (m * w);
            }
            else {
                ret = (n - sum) / (m * w) + 1;
            }

            unsigned long long added = 1;
            while (added <= (n - sum) / p + 1) {
                unsigned long long days = 0;
                if (0 == (p * added) % (m * w)) {
                    days = (p * added) / (m * w);
                }
                else {
                    days = (p * added) / (m * w) + 1;
                }

                if (days >= ret) {
                    break;
                }

                if (0 == added % 2){
                    days += makingCandy(m + added / 2, w + added / 2, p, sum + days * (m * w) - added * p, n);
                }
                else {
                    if (m > w) {
                        days += makingCandy(m + added / 2, w + added / 2 + 1, p, sum + days * (m * w) - added * p, n);
                    }
                    else {
                        days += makingCandy(m + added / 2 + 1, w + added / 2, p, sum + days * (m * w) - added * p, n);
                    }
                }

                if (days < ret) {
                    ret = days;
                }

                added ++;
            }
        }

        return ret;
    }

int main() {
    unsigned long long m, w, p, n;
    scanf("%llu %llu %llu %llu", &m, &w, &p, &n);

    unsigned long long min = makingCandy(m, w, p, 0, n);

    printf("%llu\n", min);

    return 0;
}
