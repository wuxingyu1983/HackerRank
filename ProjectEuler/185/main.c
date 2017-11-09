#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN     12
#define MAX_N       30

char s[MAX_N][MAX_LEN + 1];
char output[MAX_LEN + 1];
int c[MAX_N][MAX_LEN + 1];

#define SEED	   131
#define MOD		   10000007

long long _pow[MAX_N];

char flag[MAX_LEN][MOD];    // 0 - undefine, 1 - false, 2 - true (nerver happen)

void init_pow(long long p[], long long seed, long long mod) {
    p[0] = 1;
    for (size_t i = 1; i < MAX_N; i++) {
        p[i] = (p[i - 1] * seed) % mod;
    }

    return;
}

int get_hash(int n, int index) {
    long long ret = 0;

    for (size_t j = 0; j < n; j++) {
        ret += _pow[j] * (long long)c[j][index] % MOD;
        ret = ret % MOD;
    }

    return (int)ret;
}

bool func(int n, int index) {
    bool ret = true;

    for (size_t i = 0; i <= 9; i++) {
        ret = true;
        for (size_t j = 0; j < n; j++) {
            if ((MAX_LEN - 1) == index) {
                if (i == (s[j][index] - '0')) {
                    c[j][index + 1] = c[j][index] - 1;
                }
                else {
                    c[j][index + 1] = c[j][index];
                }

                if (0 != c[j][index + 1]) {
                    ret = false;
                    break;
                }
            }
            else {
                if (i == (s[j][index] - '0')) {
                    c[j][index + 1] = c[j][index] - 1;
                    if (0 > c[j][index + 1]) {
                        ret = false;
                        break;
                    }
                }
                else {
                    c[j][index + 1] = c[j][index];
                }
            }
        }

        if (ret) {
            output[index] = i + '0';
            if ((MAX_LEN - 1) > index) {
                int hash = get_hash(n, index + 1);
                if (0 == flag[index + 1][hash]) {
                    ret = func(n, index + 1);
                    if (ret) {
                        break;
                    }
                    else {
                        // mark flag
                        flag[index + 1][hash] = 1;
                    }
                }
                else {
                    // 1 - false
                    ret = false;
                }
            }
            else {
                // MAX_LEN - 1 == index
                break;
            }
        }
    }

    if (false == ret) {
        // mark flag
        int hash = get_hash(n, index);
        flag[index][hash] = 1;
    }

    return ret;
}

int main() {
    int n;
    scanf("%d", &n);

    for (size_t i = 0; i < n; i++) {
        scanf("%s %d", s[i], &c[i][0]);
    }

    init_pow(_pow, SEED, MOD);

    func(n, 0);

    printf("%s\n", output);

    return 0;
}
