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

        long long ret_subarrays = arr[0];           // contiguous
        long long ret_subsequences = arr[0];
        int *sum_subarrays = malloc(n * sizeof(int));

        sum_subarrays[0] = arr[0];

        for (size_t i = 1; i < n; i++) {
            // subsequences
            if (ret_subsequences < 0) {
                if (ret_subsequences < arr[i]) {
                    ret_subsequences = arr[i];
                }
            }
            else {
                if (0 < arr[i]) {
                    ret_subsequences += arr[i];
                }
            }

            // subarrays
            if (sum_subarrays[i - 1] + arr[i] > arr[i]) {
                sum_subarrays[i] = sum_subarrays[i - 1] + arr[i];
            }
            else {
                sum_subarrays[i] = arr[i];
            }

            if (sum_subarrays[i] > ret_subarrays) {
                ret_subarrays = sum_subarrays[i];
            }
        }

        printf("%lld %lld\n", ret_subarrays, ret_subsequences);

        free(arr);
        free(sum_subarrays);
    }
    return 0;
}
