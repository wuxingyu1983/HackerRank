#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN     12

char s[30][MAX_LEN + 1];
char output[MAX_LEN + 1];
int c[30][MAX_LEN + 1];

bool func(int n, int index) {
    bool ret = true;

    for (size_t i = 0; i <= 9; i++) {
        ret = true;
        for (size_t j = 0; j < n; j++) {
            if ((MAX_LEN - 1) == index) {
                if (i == (s[j][index] - '0')) {
                    c[j][index + 1] = c[j][index] - 1;
                }
                else {
                    c[j][index + 1] = c[j][index];
                }

                if (0 != c[j][index + 1]) {
                    ret = false;
                    break;
                }
            }
            else {
                if (i == (s[j][index] - '0')) {
                    c[j][index + 1] = c[j][index] - 1;
                    if (0 > c[j][index + 1]) {
                        ret = false;
                        break;
                    }
                }
                else {
                    c[j][index + 1] = c[j][index];
                }
            }
        }

        if (ret) {
            output[index] = i + '0';
            if ((MAX_LEN - 1) > index) {
                ret = func(n, index + 1);
                if (ret) {
                    break;
                }
            }
            else {
                // MAX_LEN - 1 == index
                break;
            }
        }
    }

    return ret;
}

int main() {
    int n;
    scanf("%d", &n);

    for (size_t i = 0; i < n; i++) {
        scanf("%s %d", s[i], &c[i][0]);
    }

    func(n, 0);

    printf("%s\n", output);

    return 0;
}
