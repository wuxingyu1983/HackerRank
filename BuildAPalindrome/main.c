#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG       0
#define MAX_LEN     500005

char output[10][2 * MAX_LEN];
int rl[2 * MAX_LEN];
int pallen[2 * MAX_LEN];

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

    memset(rl, 0, sizeof(rl));

    int max_right = 0, pos = 0;
    int len_tmp = strlen(tmp);
    for (int i = 0; i < len_tmp; i++) {
        if (i < max_right) {
            rl[i] = rl[2 * pos - 1] > (max_right - 1) ? (max_right - 1) : rl[2 * pos - 1];
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
/*
	for (size_t i = 0; i < strlen(str); i++) {
		out[i] = 1;
	}
*/
    for (size_t i = 0; i < len_tmp; i ++) {
        pallen[i] = 1;
    }

    for (size_t i = 0; i < len_tmp; i ++) {
        int left = i - rl[i] + 1;   // must # position
        int len = rl[i] * 2 - 1;

        if (1 < len) {
            if (len > pallen[left]) {
                pallen[left] = len;
            }

            if (left + 1 < len_tmp && (len - 1) / 2 > pallen[left + 1]) {
                pallen[left + 1] = (len - 1) / 2;
            }
        }
    }

    for (size_t i = 1, j = 0; i < len_tmp; i = i + 2, j ++) {
        out[j] = pallen[i];
    }

	free(tmp);
}

// p_a[i] : a[i] ¿ªÊ¼µÄ×î´ó»ØÎÄµÄ³¤¶È
int p_a[MAX_LEN], p_b[MAX_LEN];

void build(char *a, char *b, char *out) {
    // reverse b[]
    int len_b = strlen(b);
    for (size_t i = 0; i < len_b / 2; i++) {
        char tmp = b[i];
        b[i] = b[len_b - 1 - i];
        b[len_b - 1 - i] = tmp;
    }

    memset(p_a, 0, sizeof(p_a));
    memset(p_b, 0, sizeof(p_b));

    manacher(a, p_a);
    manacher(b, p_b);

#if 1
	printf("%s 's palindrome array is : ", a);
	for (size_t i = 0; i < strlen(a); i ++) {
		printf("%d ", p_a[i]);
	}
	printf("\n");

	printf("%s 's palindrome array is : ", b);
	for (size_t i = 0; i < strlen(b); i ++) {
		printf("%d ", p_b[i]);
	}
	printf("\n");
#endif

}

int main() {
    int q;

#if DEBUG
    FILE * fp = fopen("input.txt", "r");
    FILE * fp_out = fopen("output.txt", "w");
    fscanf(fp,"%d",&q);
#else
    scanf("%d",&q);
#endif

    char a[MAX_LEN];
    char b[MAX_LEN];
    for (size_t i = 0; i < q; i++) {
        memset(a, 0, MAX_LEN);
        memset(b, 0, MAX_LEN);

#if DEBUG
        fscanf(fp,"%s",a);
        fscanf(fp,"%s",b);
#else
        scanf("%s",a);
        scanf("%s",b);
#endif

        build(a, b, output[i]);
    }

    for (size_t i = 0; i < q; i++) {
        if (0 == strlen(output[i])) {
#if DEBUG
            fprintf(fp_out, "-1\n");
#else
            printf("-1\n");
#endif
        }
        else {
#if DEBUG
            fprintf(fp_out, "%s\n", output[i]);
#else
            printf("%s\n", output[i]);
#endif
        }
    }

#if DEBUG
    fclose(fp);
    fclose(fp_out);
#endif

	system("pause");

    return 0;
}
