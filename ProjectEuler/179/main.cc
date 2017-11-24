#include <string>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <bitset>

#define MAX_K          10000000
#define MAX_T          1000000

using namespace std;

struct factor {
    int prime;
    int count;
};

int product[MAX_K + 1];
int cnt[MAX_K + 1];

void init() {
    int pre = -1;
    int now_cnt = 0;

    for (size_t i = 2; i <= MAX_K; i++) {
        if (0 == product[i]) {
            // prime
            size_t j = i;
            while (j <= MAX_K) {
                int tmp = j;
                int c = 0;
                while (0 == tmp % i) {
                    c ++;
                    tmp /= i;
                }

                if (0 == product[j]) {
                    product[j] = c + 1;
                }
                else {
                    product[j] *= (c + 1);
                }

                j += i;
            }
        }

        if (product[i] == pre) {
            now_cnt ++;
        }

        pre = product[i];

        cnt[i] = now_cnt;
    }
}

int main() {
    int t;

    scanf("%d", &t);

    init();

    for (size_t i = 0; i < t; i++) {
        int k;
        scanf("%d", &k);

        printf("%d\n", cnt[k]);
    }

    return 0;
}
