#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define DEBUG       1

char getNextDiff(char * s, char letter) {
    char ret = letter;

    int i = 0;
//    printf("s[0] is %c\n", s[i]);
    while (s[i]) {
        if (s[i] != letter) {
            ret = s[i];
            break;
        }

        i ++;
    }

//    printf("the next diff from %c is %c\n", letter, ret);

    return ret;
}

int main() {
#if DEBUG
    FILE * fp = fopen("input.txt", "r");
#endif

    int t;

#if DEBUG
    fscanf(fp, "%d", &t);
#else
    scanf("%d", &t);
#endif

    char a[5][100001];
    char b[5][100001];

    for (size_t i = 0; i < t; i++) {
        memset(a[i], 0, 100001);
        memset(b[i], 0, 100001);

#if DEBUG
        fscanf(fp, "%s", a[i]);
        fscanf(fp, "%s", b[i]);
#else
        scanf("%s", a[i]);
        scanf("%s", b[i]);
#endif
    }

    for (size_t i = 0; i < t; i++) {
        int a_i = 0, b_i = 0;
        while (a[i][a_i] || b[i][b_i]) {
            if (a[i][a_i] && b[i][b_i]) {
                if (a[i][a_i] == b[i][b_i]) {
                    char next_a = getNextDiff(&(a[i][a_i + 1]), a[i][a_i]);
                    char next_b = getNextDiff(&(b[i][b_i + 1]), b[i][b_i]);

                    if (next_a < next_b) {
                        printf("%c", a[i][a_i]);
                        a_i ++;
                    }
                    else {
                        printf("%c", b[i][b_i]);
                        b_i ++;
                    }
                }
                else {
                    if (a[i][a_i] < b[i][b_i]) {
                        printf("%c", a[i][a_i]);
                        a_i ++;
                    }
                    else {
                        printf("%c", b[i][b_i]);
                        b_i ++;
                    }
                }
            }
            else if (a[i][a_i]) {
                printf("%c", a[i][a_i]);
                a_i ++;
            }
            else {
                printf("%c", b[i][b_i]);
                b_i ++;
            }
        }

        printf("\n");
    }

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
