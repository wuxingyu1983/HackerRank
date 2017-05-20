#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

#define PRIME_COUNT     41538
#define MAX             500000

struct number {
    int factor[7];
    int expo[7];
    int factorN;
};

struct number nums[MAX + 1];
char isPrime[MAX + 1];

int getPrimes(int n) {
    int count = 0;
    for (int i = 2; i <= n; i++) {
        if (0 == nums[i].factor[0]) {
            // prime
            isPrime[i] = 1;
            count ++;
            nums[i].factor[0] = i;
            nums[i].expo[0] = 2;
            nums[i].factorN = 1;

            int times_i = 2 * i;
            while (times_i <= n) {
                int j = 0;
                while (0 != nums[times_i].factor[j]) {
                    if (i == nums[times_i].factor[j]) {
                        break;
                    }
                    j ++;
                }
                nums[times_i].factor[j] = i;
                nums[times_i].expo[j] ++;
                nums[times_i].factorN = j + 1;
                times_i += i;
            }
        }
        else {
            // not prime
            int j = 0;
            while (0 != nums[i].factor[j]) {
                nums[i].expo[j] *= 2;
                j ++;
            }
        }
    }

    return count;
}

int n;
char * s;
unsigned long long result = 0;

void dfsFactor(unsigned long long j, unsigned long long i, unsigned long long r) {
    if (i == nums[j].factorN) {
        if (r > n || s[r] != 'a') return;
        unsigned long long k = j * j / r;
        if (k <= n && s[k] == 'c') result++;
        return;
    }
    for (int t = 0; t <= nums[j].expo[i]; t++) {
        dfsFactor(j, i+1, r);
        r = r * nums[j].factor[i];
        if (r > n) break;
    }
}

int main() {
    clock_t start,finish;
    double TheTimes;
    start=clock();

    scanf("%d", &n);
    s = (char *)malloc((n + 2) * sizeof(char));
    scanf("%s", s + 1);

    int cnt = getPrimes(n);
//    printf("we have %d primes\n", cnt);

    finish=clock();
    TheTimes=(double)(finish-start)/CLOCKS_PER_SEC;
//    printf("after get primes : %f\n", TheTimes);

    for (size_t j = 2; j <= n; j++) {
        if ('b' == s[j] && 0 == isPrime[j]) {
            // not primes
            dfsFactor(j, 0, 1);
        }
    }

    printf("%llu\n", result);

    free(s);

    finish=clock();
    TheTimes=(double)(finish-start)/CLOCKS_PER_SEC;
//    printf("finish : %f\n", TheTimes);

    return 0;
}
