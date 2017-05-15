#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main() {
    unsigned int s[1024];
    int cnt = 1;
    s[0] = 0;

    while (cnt <= 512) {
        for (size_t i = 0; i < cnt; i++) {
            s[cnt + i] = 1 - s[i];
        }

        cnt *= 2;
    }

    int q;
    scanf("%d", &q);

    unsigned int * output = malloc(sizeof(unsigned int) * q);

    for(int a0 = 0; a0 < q; a0++){
        int x;
        scanf("%d", &x);
        output[a0] = s[x];
    }

    for(int a0 = 0; a0 < q; a0++){
        printf("%u\n", output[a0]);
    }

    free(output);

    return 0;
}
