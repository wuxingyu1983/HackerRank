#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX         2001

char nums[MAX];
char flags[MAX];
int arr[MAX];

int main()
{
    int t;

    scanf("%d\n", &t);

    for (size_t i = 0; i < t; i++) {
        int n, k;

        scanf("%d %d\n", &n, &k);

        memset(nums, 0, MAX);

        for (size_t j = 0; j < n; j++) {
            scanf("%d", &arr[j]);

            if (0 == nums[arr[j]]) {
                for (size_t num_i = arr[j]; num_i < MAX; num_i += arr[j]) {
                    nums[num_i] = 1;
                }
            }
        }

        memset(flags, 0, MAX);
        int nearest = 0;

        flags[0] = 1;

        for (size_t num_i = 1; num_i < MAX; num_i++) {
            if (nums[num_i]) {
                for (size_t flag_i = 0; flag_i <= k; flag_i++) {
                    if (flags[flag_i]) {
                        int new_flag_i = flag_i + num_i;
                        if (k == new_flag_i) {
                            nearest = k;
                            goto print_nearest;
                        }
                        else if (k > new_flag_i) {
                            flags[new_flag_i] = 1;
                            if (nearest < new_flag_i) {
                                nearest = new_flag_i;
                            }
                        }
                    }
                }
            }
        }

print_nearest:
        printf("%d\n", nearest);
    }

    return 0;
}
