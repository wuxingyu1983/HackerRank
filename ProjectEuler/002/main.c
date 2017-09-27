#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

#define MAX     (4e16)

unsigned long long output[100000];
unsigned long long fib[100000];
unsigned int cnt;

void init() {
    unsigned long long tmp = 0;
    fib[0] = 1;
    fib[1] = 2;
    cnt = 2;
    tmp = fib[0] + fib[1];

    while (tmp <= MAX) {
        fib[cnt] = tmp;
        tmp = fib[cnt] + fib[cnt - 1];
        cnt ++;
    }
}

int main(){
    int t;
    scanf("%d",&t);

    init();

    for(int a0 = 0; a0 < t; a0++){
        unsigned long long n;
        scanf("%llu",&n);

        unsigned long long sum = 0;
        for (size_t i = 1; i < cnt; i += 3) {
            if (fib[i] > n) {
                break;
            }

            sum += fib[i];
        }
        output[a0] = sum;
    }

    for(int a0 = 0; a0 < t; a0++){
        printf("%llu\n", output[a0]);
    }

    return 0;
}
