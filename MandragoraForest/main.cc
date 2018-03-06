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
        vector<long long> sp;
        long long max = 0;
#if DEBUG
        fscanf(fp, "%d", &n);
#else
        scanf("%d", &n);
#endif

        health.resize(n, 0);
        sp.resize(n + 2, 0);
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
            for (size_t k = max_s; k >= 1; k--) {
                sp[k] += (long long)k * health[j];
                if (1 < k) {
                    if (sp[k - 1] > sp[k]) {
                        sp[k] = sp[k - 1];
                    }
                }
                if (sp[k] > max) {
                    max = sp[k];
                }
            }
            max_s ++;
        }
#if DEBUG
        fprintf(fp_out, "%lld\n", max);
#else
        printf("%lld\n", max);
#endif
    }

#if DEBUG
    fclose(fp);
    fclose(fp_out);
#endif
    return 0;
}
