#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG       0
#define MAX_LEN     500001

char s[MAX_LEN * 2];
int radius[MAX_LEN * 2];

void manacher(char *str, int * out) {
    // # - pre process
    int * rl = (int *)malloc(sizeof(int) * (2 * strlen(str) + 2));
    char * tmp = (char *)malloc(2 * strlen(str) + 2);

    memset(rl, 0, sizeof(int) * (2 * strlen(str) + 2));
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
            rl[i] = rl[2 * pos - i] > (max_right - i) ? (max_right - i) : rl[2 * pos - i];
        }
        else {
            rl[i] = 1;
        }

        while (i - rl[i] >= 0 && i + rl[i] < len_tmp && tmp[i - rl[i]] == tmp[i + rl[i]]) {
            rl[i] ++;
        }

        if (i + rl[i] - 1 > max_right) {
            max_right = i + rl[i] - 1;
            pos = i;
        }
    }

    for (size_t i = 1; i < len_tmp; i += 2) {
        out[(i - 1) / 2] = rl[i] / 2;
    }

	free(tmp);
    free(rl);
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

#if DEBUG
    fclose(fp);
    fclose(fp_out);
#endif

    return 0;
}
