#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>

using namespace std;

#define e           2.71828
#define MAX_N       1000000

struct factor {
    int prime;
    int count;
};

int cnt[MAX_N + 1];
vector< vector<struct factor> > vec(MAX_N + 1);

void init_prime() {
    for (size_t i = 2; i <= MAX_N; i++) {
        if (0 == vec[i].size()) {
            // prime
            size_t j = i;
            while (j <= MAX_N) {
                size_t index = j;

                while (index <= MAX_N) {
                    if (0 == vec[index].size()) {
                        struct factor a;
                        a.prime = i;
                        a.count = 1;

                        vec[index].push_back(a);
                    }
                    else {
                        if (i != vec[index][vec[index].size() - 1].prime) {
                            struct factor a;
                            a.prime = i;
                            a.count = 1;

                            vec[index].push_back(a);
                        }
                        else {
                            vec[index][vec[index].size() - 1].count ++;
                        }
                    }

                    index += j;
                }

                j *= i;
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

    return ret;
}

void init() {
    init_prime();
}

int main() {
    int q;
    scanf("%d", &q);

    init();

    for (size_t i = 0; i < q; i++) {
        int n;
        scanf("%d", &n);

        printf("%d\n", cnt[n]);
    }

    return 0;
}
