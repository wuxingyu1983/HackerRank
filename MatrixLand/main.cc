#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define DEBUG       0

int main() {
    int n, m;
#if DEBUG
    FILE * fp = fopen("input.txt", "r");
    fscanf(fp, "%d %d", &n, &m);
#else
    scanf("%d %d", &n, &m);
#endif

    int max = 0;
    vector<int> input, left_bounce, right_bounce, left_score, right_score, score;
    input.resize(m);
    left_bounce.resize(m);
    right_bounce.resize(m);
    left_score.resize(m, 0);
    right_score.resize(m, 0);
    score.resize(m, 0);

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

        for (size_t j = 0; j < m; j++) {
            if (0 == j) {
                left_bounce[j] = input[j];
                left_score[j] = score[j] + input[j];
            }
            else {
                if (left_bounce[j - 1] > 0) {
                    left_bounce[j] = input[j] + left_bounce[j - 1];
                }
                else {
                    left_bounce[j] = input[j];
                }

                if (left_score[j - 1] + input[j] > score[j] + left_bounce[j]) {
                    left_score[j] = left_score[j - 1] + input[j];
                }
                else {
                    left_score[j] = score[j] + left_bounce[j];
                }
            }
        }

        for (int j = m - 1; j >= 0; j--) {
            if (m - 1 == j) {
                right_bounce[j] = input[j];
                right_score[j] = score[j] + input[j];
            }
            else {
                if (right_bounce[j + 1] > 0) {
                    right_bounce[j] = input[j] + right_bounce[j + 1];
                }
                else {
                    right_bounce[j] = input[j];
                }

                if (right_score[j + 1] + input[j] > score[j] + right_bounce[j]) {
                    right_score[j] = right_score[j + 1] + input[j];
                }
                else {
                    right_score[j] = score[j] + right_bounce[j];
                }
            }
        }

        for (size_t j = 0; j < m; j++) {
            score[j] = left_score[j] + right_bounce[j] - input[j];

            if (score[j] < right_score[j] + left_bounce[j] - input[j]) {
                score[j] = right_score[j] + left_bounce[j] - input[j];
            }

            if (n - 1 == i) {
                if (0 == j) {
                    max = score[j];
                }
                else {
                    if (max < score[j]) {
                        max = score[j];
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
