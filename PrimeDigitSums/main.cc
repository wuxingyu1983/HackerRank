#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX_N       400000
#define MOD         1000000007

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43};
int flag[45];
int sum[10000];

unsigned int cnt[MAX_N + 1];

int main() {
    int q;
    scanf("%d", &q);

    vector<unsigned int> inputs;
    inputs.reserve(q);

    unsigned int max_n = 0;
    for (size_t i = 0; i < q; i++) {
        unsigned int n;
        scanf("%u", &n);
        if (n > max_n) {
            max_n = n;
        }
        inputs.push_back(n);
    }

    for (size_t i = 0; i < 14; i++) {
        flag[primes[i]] = 1;
    }

    for (size_t i = 3; i <= max_n; i++) {
        if (3 == i) {
            for (size_t j = 1; j <= 9; j++) {
                sum[j] = j;
            }
            for (size_t j = 10; j <= 99; j++) {
                int s = (j / 10) + (j % 10);
                sum[j] = s;
            }
            int c = 0;
            for (size_t j = 100; j <= 999; j++) {
                int s = (j / 100) + sum[(j % 100)];
                sum[j] = s;
                if (flag[s]) {
                    c ++;
                }
            }
            cnt[i] = c;
        }
        else if (4 == i) {
            for (size_t j = 1000; j <= 9999; j++) {
                int s = (j / 1000) + sum[(j % 1000)];
                sum[j] = s;

            }
        }
        else if (5 == i) {

        }
        else {

        }
    }

    for (size_t i = 0; i < q; i++) {
        printf("%u\n", cnt[i]);
    }

    return 0;
}
