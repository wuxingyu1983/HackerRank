#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    unsigned int n;
    unsigned long long c;
    int ret = 0;

    scanf("%u %llu", &n, &c);

    int * a = malloc(n * sizeof(int));
    int * b = malloc(n * sizeof(int));

    for (size_t i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (size_t i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }

    unsigned long long remain = 0;
    int seq_start = 0;
    int seq_end = 0;
    int unseq_start = 0 - n;

    // find first loop
    int jump = 0;
    while (jump < n) {
        unsigned long long aft_refuel = (remain + (unsigned long long)a[seq_end] > c) ? c : remain + (unsigned long long)a[seq_end];
        if (aft_refuel > b[seq_end]) {
            // expand seq
            remain = aft_refuel - b[seq_end];
            seq_end = (seq_end + 1) % n;
        }
        else {

        }

        jump ++;
    }

    printf("%d\n", ret);

    free(a);
    free(b);

    return 0;
}
