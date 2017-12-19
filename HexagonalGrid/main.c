#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define DEBUG       1

int main() {
#if DEBUG
    FILE * fp;
    fp = fopen("input.txt", "r");

    FILE * fp_out;
    fp_out = fopen("output.txt", "w");
#endif

    int t;

#if DEBUG
    fscanf(fp, "%d", &t);
#else
    scanf("%d", &t);
#endif

    char * * output = (char * *)malloc(t * sizeof(char *));

    for (size_t i = 0; i < t; i++) {
        int n;

#if DEBUG
        fscanf(fp, "%d", &n);
#else
        scanf("%d", &n);
#endif

        char * grid1 = malloc(n + 2);
        char * grid2 = malloc(n + 2);

#if DEBUG
        fscanf(fp, "%s", grid1 + 1);
        fscanf(fp, "%s", grid2 + 1);
#else
        scanf("%s", grid1 + 1);
        scanf("%s", grid2 + 1);
#endif

        unsigned char * * cnt = (unsigned char * *)malloc((n + 1) * sizeof(unsigned char *));
        for (size_t j = 0; j < n + 1; j++) {
            cnt[j] = (unsigned char *)malloc(n + 1);
            memset(cnt[j], 0, n + 1);
        }

        cnt[0][0] = 1;

        for (size_t j = 1; j <= n; j++) {
            if (1 == j) {
                if ('0' == grid1[j] && '0' == grid2[j]) {
                    cnt[j][j] = 1;
                }
                else if ('1' == grid1[j] && '1' == grid2[j]) {
                    cnt[j][j] = 1;
                }
                else if ('1' == grid1[j]) {
                    cnt[j][0] = 1;
                }
                else {
                    cnt[0][j] = 1;
                }
            }
            else {
                if ('0' == grid1[j] && '0' == grid2[j]) {
                    // [j][j - 2]
                    if ('0' == grid1[j - 1]) {
                        cnt[j][j - 2] = cnt[j - 2][j - 2];
                    }

                    // [j][j - 1]
                    if ('0' == grid1[j - 1]) {
                        cnt[j][j - 1] = cnt[j - 2][j - 1];
                    }

                    if ('0' == grid2[j - 1]) {
                        cnt[j][j - 1] += cnt[j - 1][j - 2];
                    }

                    if (0 < cnt[j][j - 1]) {
                        cnt[j][j - 1] = 1;
                    }

                    // [j - 2][j]
                    if ('0' == grid2[j - 1]) {
                        cnt[j - 2][j] = cnt[j - 2][j - 2];
                    }

                    // [j - 1][j]
                    if ('0' == grid2[j - 1]) {
                        cnt[j - 1][j] = cnt[j - 1][j - 2];
                    }

                    // [j][j]
                    cnt[j][j] = cnt[j - 1][j - 1];

                    if ('0' == grid1[j - 1] && '0' == grid2[j - 1]) {
                        cnt[j][j] += cnt[j - 2][j - 2];
                    }

                    if (0 < cnt[j][j]) {
                        cnt[j][j] = 1;
                    }
                }
                else if ('1' == grid1[j] && '1' == grid2[j]) {
                    cnt[j][j] = cnt[j - 1][j - 1];
                }
                else if ('1' == grid1[j]) {
                    // [j][j - 2]
                    cnt[j][j - 2] = cnt[j - 1][j - 2];

                    // [j][j - 1]
                    cnt[j][j - 1] = cnt[j - 1][j - 1];

                    // [j][j]
                    if ('0' == grid2[j - 1]) {
                        cnt[j][j] = cnt[j - 1][j - 2];
                    }
                }
                else {
                    // [j - 2][j]
                    cnt[j - 2][j] = cnt[j - 2][j - 1];

                    // [j - 1][j]
                    cnt[j - 1][j] = cnt[j - 1][j - 1];

                    //[j][j]
                    if ('0' == grid1[j - 1]) {
                        cnt[j][j] = cnt[j - 2][j - 1];
                    }

                    if ('0' == grid2[j - 1]) {
                        cnt[j][j] += cnt[j - 1][j - 2];
                    }

                    if (0 < cnt[j][j]) {
                        cnt[j][j] = 1;
                    }
                }
            }
        }

        output[i] = malloc(4);

        if (cnt[n][n]) {
            sprintf(output[i], "%s", "YES");
        }
        else {
            sprintf(output[i], "%s", "NO");
        }

        free(grid1);
        free(grid2);

        for (size_t j = 0; j < n + 1; j++) {
            free(cnt[j]);
        }
        free(cnt);
    }

    for (size_t i = 0; i < t; i++) {
#if DEBUG
        fprintf(fp_out, "%s\n", output[i]);
#else
        printf("%s\n", output[i]);
#endif
    }

#if DEBUG
    fclose(fp);
    fclose(fp_out);
#endif

    return 0;
}
