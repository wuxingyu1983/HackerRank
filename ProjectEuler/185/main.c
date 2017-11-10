#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN     12
#define MAX_N       30

char s[MAX_N][MAX_LEN + 1];
char impossible[MAX_LEN][10];
int c[MAX_N];
int output[MAX_LEN];

bool func(int n, int index) {
    bool ret = true;

    if (0 == c[index]) {
        // mark impossible
        for (size_t i = 0; i < MAX_LEN; i++) {
            impossible[i][s[index][i] - '0'] ++;
        }

        for (size_t i = 0; i < MAX_LEN; i++) {
            if (output[i] == (s[index][i] - '0')) {
                ret = false;
                break;
            }
        }
        if (ret && index < (n - 1)) {
            ret = func(n, index + 1);
        }
    }
    else if (1 == c[index]) {
        int already = 0;
        for (size_t i = 0; i < MAX_LEN; i++) {
            if (output[i] == (s[index][i] - '0')) {
                already ++;
            }
        }
        if (1 < already) {
            ret = false;
        }
        else if (1 == already) {
            // mark impossible
            for (size_t i = 0; i < MAX_LEN; i++) {
                if (output[i] != (s[index][i] - '0')) {
                    impossible[i][s[index][i] - '0'] ++;
                }
            }

            if (index < n - 1) {
                ret = func(n, index + 1);
                if (false == ret) {
                    // unmark impossible
                    for (size_t i = 0; i < MAX_LEN; i++) {
                        if (output[i] != (s[index][i] - '0')) {
                            impossible[i][s[index][i] - '0'] --;
                        }
                    }
                }
            }
        }
        else {
            // 0 == already
            // mark impossible
            for (size_t i = 0; i < MAX_LEN; i++) {
                impossible[i][s[index][i] - '0'] ++;
            }

            ret = false;
            for (size_t pos = 0; pos < MAX_LEN; pos++) {
                if (1 == impossible[pos][s[index][pos] - '0'] && 0 > output[pos]) {
                    // unmark impossible
                    impossible[pos][s[index][pos] - '0'] --;
                    output[pos] = s[index][pos] - '0';

                    if (index < n - 1) {
                        ret = func(n, index + 1);
                        if (ret) {
                            break;
                        }
                        else {
                            // mark impossible
                            impossible[pos][s[index][pos] - '0'] ++;
                            output[pos] = -1;
                        }
                    }
                }
            }

            if (false == ret) {
                // unmark impossible
                for (size_t i = 0; i < MAX_LEN; i++) {
                    impossible[i][s[index][i] - '0'] --;
                }
            }
        }
    }
    else if (2 == c[index]) {

    }
    else {
        // 3 == c[index]

    }

    return ret;
}

int main() {
    int n;
    scanf("%d", &n);

    for (size_t i = 0; i < n; i++) {
        scanf("%s %d", s[i], &c[i]);
    }

    for (size_t i = 0; i < MAX_LEN; i++) {
        output[i] = -1;
    }

    func(n, 0);

    for (size_t i = 0; i < MAX_LEN; i++) {
        if (0 <= output[i]) {
            printf("%d", output[i]);
        }
        else {
            for (size_t j = 0; j < 10; j++) {
                if (0 == impossible[i][j]) {
                    printf("%d", j);
                    break;
                }
            }
        }
    }
    printf("\n");

    return 0;
}
