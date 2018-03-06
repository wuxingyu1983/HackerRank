#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define DEBUG       1

int main() {
#if DEBUG
    FILE * fp = fopen("input.txt", "r");
    FILE * fp_out = fopen("output.txt", "w");
#endif

    int t;
#if DEBUG
    fscanf(fp, "%d", &t);
#else
    scanf("%d", &t);
#endif

    for (size_t i = 0; i < t; i++) {
        int n, max_s = 1;
        vector<long long> health;
        vector<long long> sums;
#if DEBUG
        fscanf(fp, "%d", &n);
#else
        scanf("%d", &n);
#endif

        health.resize(n, 0);
        sums.resize(n, 0);
        for (size_t j = 0; j < n; j++) {
#if DEBUG
            fscanf(fp, "%lld", &health[j]);
#else
            scanf("%lld", &health[j]);
#endif
        }

        // sort
        sort(health.begin(), health.end());
        for (size_t j = 0; j < n; j++) {
            if (0 == j) {
                sums[j] = health[j];
            }
            else {
                sums[j] = health[j] + sums[j - 1];
            }
        }

        long long s = 1;
        long long p = 0;
        for (size_t j = 0; j < n; j++) {
            if (s * health[j] > (sums[n - 1] - sums[j])) {
                p += s * health[j];
            }
            else {
                s ++;
            }
        }
#if DEBUG
        fprintf(fp_out, "%lld\n", p);
#else
        printf("%lld\n", p);
#endif
    }

#if DEBUG
    fclose(fp);
    fclose(fp_out);
#endif
    return 0;
}
