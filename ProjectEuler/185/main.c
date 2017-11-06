#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

char s[30][13];
char output[13];
int c[30][13];

bool func(int n, int index) {
    bool ret = true;

    for (size_t i = 0; i <= 9; i++) {
        ret = true;
        for (size_t j = 0; j < n; j++) {
            if (11 == index) {
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
            if (11 > index) {
                ret = func(n, index + 1);
            }
            else {
                // 11 == index
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
