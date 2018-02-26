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
    int n, m;
#if DEBUG
    FILE * fp = fopen("input.txt", "r");
    fscanf(fp, "%d %d", &n, &m);
#else
    scanf("%d %d", &n, &m);
#endif

    int max;
    vector<int> input, left_bounce, right_bounce, bounce;
    input.resize(m);
    left_bounce.resize(m);
    right_bounce.resize(m);
    bounce.resize(m, 0);

    for (size_t i = 0; i < n; i++) {
        int a;
        for (size_t j = 0; j < m; j++) {
#if DEBUG
            fscanf(fp, "%d", &a);
#else
            scanf("%d", &a);
#endif
            input[j] = a;
        }

        int tmp = 0;
        for (size_t j = 0; j < m; j++) {
            if (0 == j) {
                tmp = input[j];
            }
            else {
                if (tmp + input[j] > input[j]) {
                    tmp += input[j];
                }
                else {
                    tmp = input[j];
                }
            }
            left_bounce[j] = tmp;
        }

        for (int j = m - 1; j >= 0; j--) {
            if (m - 1 == j) {
                tmp = input[j];
            }
            else {
                if (tmp + input[j] > input[j]) {
                    tmp += input[j];
                }
                else {
                    tmp = input[j];
                }
            }
            right_bounce[j] = tmp;

            bounce[j] += left_bounce[j] + right_bounce[j] - input[j];

            if (n - 1 == i) {
                if (m - 1 == j) {
                    max = bounce[j];
                }
                else {
                    if (bounce[j] > max) {
                        max = bounce[j];
                    }
                }
            }
        }
    }

    printf("%d\n", max);

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
