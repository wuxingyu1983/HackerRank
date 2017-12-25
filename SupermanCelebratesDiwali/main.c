#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int buildings[1901][1901];
int cnt[1901][1901];
int max[1901];

int main() {
    int N, H, I;

    scanf("%d %d %d", &N, &H, &I);

    for (size_t i = 0; i < N; i++) {
        int people = 0;
        scanf("%d", &people);

        if (people) {
            for (size_t j = 0; j < people; j++) {
                int floor = 0;;
                scanf("%d", &floor);

                buildings[i][floor] ++;
            }
        }
    }

    for (size_t h = 1; h <= H; h++) {
        if (0 < h - I) {
            for (size_t b = 0; b < N; b++) {
                if (buildings[b][h] + cnt[b][h - 1] > buildings[b][h] + max[h - I]) {
                    cnt[b][h] = buildings[b][h] + cnt[b][h - 1];
                }
                else {
                    cnt[b][h] = buildings[b][h] + max[h - I];
                }
                if (cnt[b][h] > max[h]) {
                    max[h] = cnt[b][h];
                }
            }
        }
        else {
            for (size_t b = 0; b < N; b++) {
                cnt[b][h] = buildings[b][h] + cnt[b][h - 1];
                if (cnt[b][h] > max[h]) {
                    max[h] = cnt[b][h];
                }
            }
        }
    }

    printf("%d\n", max[H]);

    return 0;
}
