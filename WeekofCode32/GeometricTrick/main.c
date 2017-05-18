#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>


int main() {
    int n;
    scanf("%d", &n);
    char* s = (char *)malloc(n * sizeof(char));
    scanf("%s", s);

    unsigned long long result = 0;

    for (size_t i = 0; i < n; i++) {
        if ('b' == s[i]) {
            unsigned long long tmp = (unsigned long long)(i + 1) * (unsigned long long)(i + 1);
            int j = i - 1;
            while (0 <= j) {
                if ('b' != s[j]) {
                    if (0 == tmp % (j + 1)) {
                        int oth = tmp / (j + 1) - 1;
                        if (n - 1 < oth) {
                            break;
                        }
                        else {
                            if (s[j] != s[oth] && 'b' != s[oth]) {
                                result ++;
                            }
                        }
                    }
                }

                j --;
            }
        }
    }

    printf("%llu\n", result);

    free(s);

    return 0;
}
