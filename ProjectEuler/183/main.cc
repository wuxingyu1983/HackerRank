#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>

using namespace std;

#define E           2.71828
#define MAX_N       1000000

struct factor {
    int prime;
    int count;
};

long long cnt[MAX_N + 1];
vector< vector<struct factor> > vec(MAX_N + 1);

void init_prime() {
    for (size_t i = 2; i <= MAX_N; i++) {
        if (0 == vec[i].size()) {
            // prime
            size_t j = i;
            while (j <= MAX_N) {
                int c = 0;
                int tmp = j;

                while ( 0 == tmp % i) {
                    c ++;
                    tmp /= i;
                }

                struct factor a;
                a.prime = i;
                a.count = c;

                vec[j].push_back(a);

                j += i;
            }
        }
    }
}

bool terminating(int n, int k) {
    bool ret = true;

    int i_n = 0, i_k = 0;
    while (i_n < vec[n].size() && i_k < vec[k].size()) {
        if (2 == vec[k][i_k].prime || 5 == vec[k][i_k].prime) {
            i_k ++;
        }
        else {
            if (vec[n][i_n].prime < vec[k][i_k].prime) {
                i_n ++;
            }
            else if (vec[n][i_n].prime > vec[k][i_k].prime) {
                ret = false;
                break;
            }
            else {
                // ==
                if (vec[n][i_n].count < vec[k][i_k].count) {
                    ret = false;
                    break;
                }
                else {
                    i_n ++;
                    i_k ++;
                }
            }
        }
    }

    if (ret) {
        while (i_k < vec[k].size()) {
            if (2 != vec[k][i_k].prime && 5 != vec[k][i_k].prime) {
                ret = false;
                break;
            }
            i_k ++;
        }
    }

    return ret;
}

void init() {
    init_prime();

    long long count = 0;
    for (size_t i = 5; i <= MAX_N; i++) {
        int k = i / E;

        if (1 > pow((long double)(k + 1) / (long double)k, k) / ((long double)i / (long double)(k + 1))) {
            k += 1;
        }

        if (terminating(i, k)) {
            count -= i;
//            printf("i = %d, k = %d, terminating, count = %d\n", i, k, count);
        }
        else {
            count += i;
//            printf("i = %d, k = %d, non-terminating, count = %d\n", i, k, count);
        }

        cnt[i] = count;
    }
}

int main() {
    int q;
    scanf("%d", &q);

    init();

    for (size_t i = 0; i < q; i++) {
        int n;
        scanf("%d", &n);

        printf("%lld\n", cnt[n]);
    }

    return 0;
}
