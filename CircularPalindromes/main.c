#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG       0
#define MAX_LEN     500001

char s[MAX_LEN * 2];
int radius[MAX_LEN * 4 + 4];

void manacher(char *str, int * out) {
    // # - pre process
    char * tmp = (char *)malloc(2 * strlen(str) + 2);

    memset(tmp, 0, 2 * strlen(str) + 2);

    size_t j = 0;
    for (size_t i = 0; i < strlen(str); i++) {
        tmp[j++] = '#';
        tmp[j++] = str[i];
    }
    tmp[j] = '#';

    int max_right = 0, pos = 0;
    int len_tmp = strlen(tmp);

    for (int i = 0; i < len_tmp; i++) {
        if (i < max_right) {
            out[i] = out[2 * pos - i] > (max_right - i) ? (max_right - i) : out[2 * pos - i];
        }
        else {
            out[i] = 1;
        }

        while (i - out[i] >= 0 && i + out[i] < len_tmp && tmp[i - out[i]] == tmp[i + out[i]]) {
            out[i] ++;
        }

        if (i + out[i] - 1 > max_right) {
            max_right = i + out[i] - 1;
            pos = i;
        }
    }

	free(tmp);
}

int main() {
    int n;

#if DEBUG
    FILE * fp = fopen("input.txt", "r");
    FILE * fp_out = fopen("output.txt", "w");
    fscanf(fp, "%d", &n);
    fscanf(fp, "%s", s);
#else
    scanf("%d", &n);
    scanf("%s", s);
#endif

    // copy
    for (size_t i = 0; i < n; i++) {
        s[i + n] = s[i];
    }

    manacher(s, radius);

    for (size_t start = 1; start < 2 * n; start += 2) {
        int max = 0;

        for (size_t j = start; j < start + 2 * n; j ++) {
            int r = radius[j];
            int left = j + 1 - radius[j];
            int right = j - 1 + radius[j];

            if (left < (start - 1)) {
                r = j - (start - 1) + 1;
            }

            if (right >= start + 2 * n) {
                if (r > (start + 2 * n - j)) {
                    r = start + 2 * n - j;
                }
            }

            if ((r - 1) > max) {
                max = r - 1;
            }
        }

#if DEBUG
        fprintf(fp_out, "%d\n", max);
#else
        printf("%d\n", max);
#endif
    }

#if DEBUG
    fclose(fp);
    fclose(fp_out);
#endif

    return 0;
}
