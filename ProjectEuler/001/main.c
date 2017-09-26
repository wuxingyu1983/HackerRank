#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

unsigned long long output[100000];

int main(){
    int t;
    scanf("%d",&t);

    for(int a0 = 0; a0 < t; a0++){
        int n;
        scanf("%d",&n);

        n --;

        unsigned long long cnt = 0;
        unsigned long long sum = 0;
        // sum of multiple of 3
        cnt = n / 3;
        if (1 <= cnt) {
            sum = (cnt + 1) * 3 * cnt / 2;
        }

        // sum of multiple of 5
        cnt = n / 5;
        if (1 <= cnt) {
            sum += (cnt + 1) * 5 * cnt / 2;
        }

        // sum of multiple of 15
        cnt = n / 15;
        if (1 <= cnt) {
            sum -= (cnt + 1) * 15 * cnt / 2;
        }

        output[a0] = sum;
    }

    for(int a0 = 0; a0 < t; a0++){
        printf("%llu\n", output[a0]);
    }

    return 0;
}
