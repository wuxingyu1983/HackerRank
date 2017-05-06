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
            if (m > (n - sum) / w) {
                ret = 1;
            }
            else {
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

                    unsigned long long new_m = m, new_w = w;
                    if (m == w) {
                        if (0 == added % 2){
                            new_m += added / 2;
                            new_w += added / 2;
                        }
                        else {
                            new_m += added / 2 + 1;
                            new_w += added / 2;
                        }
                    }
                    else {
                        if (m > w) {
                            if (added <= m - w) {
                                new_w += added;
                            }
                            else {
                                unsigned long long new_added = added - m + w;
                                new_w = new_m;
                                if (0 == new_added % 2) {
                                    new_m += new_added / 2;
                                    new_w += new_added / 2;
                                }
                                else {
                                    new_m += new_added / 2 + 1;
                                    new_w += new_added / 2;
                                }
                            }
                        }
                        else {
                            if (added <= w - m) {
                                new_m += added;
                            }
                            else {
                                unsigned long long new_added = added - w + m;
                                new_m = new_w;
                                if (0 == new_added % 2) {
                                    new_m += new_added / 2;
                                    new_w += new_added / 2;
                                }
                                else {
                                    new_m += new_added / 2 + 1;
                                    new_w += new_added / 2;
                                }
                            }
                        }
                    }

                    days += makingCandy(new_m, new_w, p, sum + days * (m * w) - added * p, n);

                    if (days < ret) {
                        ret = days;
                    }

                    added ++;
                }
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
