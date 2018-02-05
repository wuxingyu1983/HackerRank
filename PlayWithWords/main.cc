#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

char str[3001];
int cnt[3000][3000];

int main() {
    int ret = 0;

    scanf("%s", str);

    int len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        cnt[i][i] = 1;
    }

    for (size_t step = 1; step < len; step++) {
        for (size_t i = 0; i < len; i++) {
            if (i + step >= len) {
                break;
            }

            if (1 == step) {
                if (str[i] == str[i + step]) {
                    cnt[i][i + step] = 2;
                }
                else {
                    cnt[i][i + step] = 1;
                }
            }
            else {
                if (str[i] == str[i + step]) {
                    cnt[i][i + step] = 2 + cnt[i + 1][i + step - 1];
                }
                else {
                    if (cnt[i][i + step - 1] > cnt[i + 1][i + step]) {
                        cnt[i][i + step] = cnt[i][i + step - 1];
                    }
                    else {
                        cnt[i][i + step] = cnt[i + 1][i + step];
                    }
                }
            }
        }
    }

    for (size_t i = 0; i < len - 1; i++) {
        if (cnt[0][i] * cnt[i + 1][len - 1] > ret) {
            ret = cnt[0][i] * cnt[i + 1][len - 1];
        }
    }

    printf("%d\n", ret);

    return 0;
}
