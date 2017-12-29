#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main() {
    int t;
    scanf("%i", &t);
    for(int a0 = 0; a0 < t; a0++){
        int n;
        scanf("%i", &n);
        int *arr = malloc(sizeof(int) * n);
        for (int arr_i = 0; arr_i < n; arr_i++) {
           scanf("%i",&arr[arr_i]);
        }

        unsigned long long profit = 0;
        unsigned int max = arr[n - 1];

        for (int i = n - 2; i >= 0; i --) {
            if (arr[i] > max) {
                max = arr[i];
            }
            else {
                profit += max - arr[i];
            }
        }

        printf("%lld\n", profit);

        free(arr);
    }

    return 0;
}
