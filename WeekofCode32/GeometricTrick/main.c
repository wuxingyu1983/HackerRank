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
    int factor[8];
    int expo[8];
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
                    j ++;
                }
                nums[times_i].factor[j] = i;
                int now = times_i;
                while (0 == now % i) {
                    nums[times_i].expo[j] ++;
                    now /= i;
                }
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

void dfsFactor(long long j, long long i, long long r) {
	if (i == nums[j].factorN) {
		if (r >= j) {
            return;
        }
		long long k = j * j / r;
        if (k <= n) {
            if ('a' == s[r] && 'c' == s[k]) {
                result++;
            }
            else if ('c' == s[r] && 'a' == s[k]) {
                result++;
            }
        }
		return;
	}
	for (int t = 0; t <= nums[j].expo[i]; t++) {
		dfsFactor(j, i+1, r);
		r = r * nums[j].factor[i];
		if (r >= j) {
            break;
        }
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
/*
    for (int i = 1; i <= n; i++) {
        printf("%d is prime(%d), has :\n", i, isPrime[i]);
        for (size_t j = 0; j < nums[i].factorN; j++) {
            printf("  fact = %d, expo = %d\n", nums[i].factor[j], nums[i].expo[j]);
        }
    }
*/
    finish=clock();
    TheTimes=(double)(finish-start)/CLOCKS_PER_SEC;
//    printf("after get primes : %f\n", TheTimes);

    result = 0;
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
