#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

const int MOD = 1000000007;

int func(char * input, int len) {
    int ret = 0;

    if (1 < len) {
        int s[200][200];

        unsigned long long cnt = 0;
        // init
        for (size_t i = 0; i < 200; i++) {
            memset(s[i], 0, sizeof(int) * 200);
        }

        for (size_t i = 1; i < len; i++) {
            for (size_t j = 0; j < i; j++) {
                if (input[j] == input[i]) {
                    s[j][i] = 1;
                    if (0 < j && j < i - 1) {
                        for (size_t k = 0; k < j; k ++) {
                            for (size_t l = j + 1; l < i; l ++) {
                                if (s[k][l]) {
                                    s[j][i] += s[k][l];
                                    s[j][i] %= MOD;
                                }
                            }
                        }
                    }

                    printf("s[%d][%d] = %d\n", (int)j, (int)i, s[j][i]);

                    cnt += s[j][i];
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

    free(output);

    return 0;
}
