#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int * h;
    h = malloc(sizeof(int) * n);

    for (size_t i = 0; i < n; i++) {
        scanf("%d", h + i);
    }

    unsigned long long e = 0;

    for (int i = n - 1; i >= 0; i --) {
        unsigned long long tmp = h[i] + e;
        if (0 != tmp % 2) {
            e = tmp / 2 + 1;
        }
        else {
            e = tmp / 2;
        }
    }

    printf("%llu\n", e);

    free(h);

    return 0;
}
