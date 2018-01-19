#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    unsigned int n;
    unsigned long long c;

    scanf("%u %llu", &n, &c);

    int * a = malloc(n * sizeof(int));
    int * b = malloc(n * sizeof(int));

    for (size_t i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (size_t i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }

    free(a);
    free(b);

    return 0;
}
