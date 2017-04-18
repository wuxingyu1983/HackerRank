#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

const int MOD = 1000000007;
int *ss[200][200];

int rfn (char * input, int index1, int index2, int index3) {
    int ret = 0;

    if (0 < ss[index1][index2][index3]) {
        ret = ss[index1][index2][index3];
        printf("retrun ss[%d][%d][%d] : %d\n", index1, index2, index3, ret);
    }
    else {
        if (input[index1] == input[index3]) {
            ret = 1;
            if (0 < index1 && index3 > index2 + 1) {
                ret += rfn(input, index1 - 1, index2, index3 - 1);
                ret %= MOD;
            }
            ss[index1][index2][index3] = ret;
            printf("ss[%d][%d][%d] = %d\n", index1, index2, index3, ret);
        }
        else {
            if (0 < index1) {
                ret += rfn(input, index1 - 1, index2, index3);
                ret %= MOD;
            }
            if (index3 > index2 + 1) {
                ret += rfn(input, index1, index2, index3 - 1);
                ret %= MOD;
            }
        }
    }

    return ret;
}

int func(char * input, int len) {
    int ret = 0;

    if (1 < len) {
        unsigned long long cnt = 0;
        // init

        for (size_t i = 0; i < 200; i++) {
            for (size_t j = 0; j < 200; j++) {
                memset(ss[i][j], 0, sizeof(int) * 200);
            }
        }
        for (size_t i = 1; i < len; i++) {
            for (size_t j = 0; j < i; j++) {
                if (input[j] == input[i]) {
                    cnt += rfn(input, j, j, i);
                    cnt %= MOD;
                }
            }

        }
        ret = cnt;
    }

    return ret;
}

int main() {
    int t;
    scanf("%d", &t);

    for (size_t i = 0; i < 200; i++) {
        for (size_t j = 0; j < 200; j++) {
            ss[i][j] = malloc(sizeof(int) * 200);
            if (!ss[i][j]) {
                printf("malloc error !\n");
                return -1;
            }
        }
    }

    int *output = malloc(sizeof(int) * t);
    char s[201];
    for (int i = 0; i < t; i ++) {
        memset(s, 0, sizeof(s));
        scanf("%s", s);

        int len = strlen(s);

        output[i] = func(s, len);
    }

    for (int i = 0; i < t; i ++) {
        printf("%d\n", output[i]);
    }

    for (size_t i = 0; i < 200; i++) {
        for (size_t j = 0; j < 200; j++) {
            free(ss[i][j]);
        }
    }

    free(output);

    return 0;
}
