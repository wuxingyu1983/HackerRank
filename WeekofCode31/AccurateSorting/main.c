#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main() {
    int q;
    scanf("%d", &q);

    char output[10][4];

    for(int a0 = 0; a0 < q; a0++){
        memset(output[a0], 0, 4);
        int n;
        scanf("%d", &n);
        int *a = malloc(sizeof(int) * n);
        for(int a_i = 0; a_i < n; a_i++){
           scanf("%d",&a[a_i]);
        }

        for (int a_i = 0; a_i < n; a_i ++) {
            if (a[a_i] == a_i || (a[a_i] == (a_i + 1) || (0 <= (a_i - 1) && a[a_i] == (a_i - 1)))) {
                if (a_i == n - 1) {
                    strcpy(output[a0], "Yes");
                }
            }
            else {
                strcpy(output[a0], "No");
                break;
            }
        }

        free(a);
    }

    for(int a0 = 0; a0 < q; a0++){
        printf("%s\n", output[a0]);
    }

    return 0;
}
