#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int t;

    scanf("%d", &t);

    for (size_t i = 0; i < t; i++) {
        int n;
        scanf("%d", &n);

        char * grid1 = malloc(n + 2);
        char * grid2 = malloc(n + 2);

        scanf("%s", grid1 + 1);
        scanf("%s", grid2 + 1);

        unsigned char * * cnt = (unsigned char * *)malloc((n + 1) * sizeof(unsigned char *));
        for (size_t j = 0; j < n + 1; j++) {
            cnt[j] = (unsigned char *)malloc(n + 1);
            memset(cnt[j], 0, n + 1);
        }

        cnt[0][0] = 1;

        

        free(grid1);
        free(grid2);

        for (size_t j = 0; j < n + 1; j++) {
            free(cnt[j]);
        }
        free(cnt);
    }

    return 0;
}
