#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG		0

char p[10][100001];
char v[10][100001];

int output[10][100000];
int cnt[10];

int save_humanity(char pat[], char vir[], int out[]) {
    int ret = 0;
    int len_p = strlen(pat);
    int len_v = strlen(vir);

    if (len_p >= len_v) {
        
    }

    return ret;
}

int main() {
    int t;

#if DEBUG
    FILE * fp = fopen("input.txt", "r");
    fscanf(fp, "%d", &t);
    FILE * fp_out = fopen("output.txt", "w");
#else
    scanf("%d", &t);
#endif

    for (size_t i = 0; i < t; i++) {
#if DEBUG
        fscanf(fp, "%s %s", p[i], v[i]);
#else
        scanf("%s %s", p[i], v[i]);
#endif
        cnt[i] = save_humanity(p[i], v[i], output[i]);
    }

    for (size_t i = 0; i < t; i++) {
        if (0 >= cnt[i]) {
            printf("No Match!\n");
        }
        else {
            int j = 0;
            printf("%d", output[i][j++]);
            while (j < cnt[i]) {
                printf(" %d", output[i][j++]);
            }
            printf("\n");
        }
    }

#if DEBUG
    fclose(fp);
    fclose(fp_out);
#endif

    return 0;
}
