#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define DEBUG       1

int getNextDiff(char * s, int index) {
    int ret = index + 1;

    while (s[ret]) {
        if (s[ret] != s[index]) {
            break;
        }

        ret ++;
    }

//   printf("\nthe next diff from %c at %d is %c\n", s[index], index, ret);

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
                    int next_a = getNextDiff(a[i], a_i);
                    int next_b = getNextDiff(b[i], b_i);

                    if (a[i][next_a] && b[i][next_b]) {
                        if (a[i][next_a] > a[i][a_i] && b[i][next_b] > b[i][b_i]) {
                            while (a_i < next_a) {
                                printf("%c", a[i][a_i ++]);
                            }
                            while (b_i < next_b) {
                                printf("%c", b[i][b_i ++]);
                            }
                        }
                        else if (a[i][next_a] < a[i][a_i] && b[i][next_b] < b[i][b_i]) {
                            if ((next_a - a_i) == (next_b - b_i)) {
                                if (a[i][next_a] < b[i][next_b]) {
                                    while (a_i < next_a) {
                                        printf("%c", a[i][a_i ++]);
                                    }
                                }
                                else {
                                    while (b_i < next_b) {
                                        printf("%c", b[i][b_i ++]);
                                    }
                                }
                            }
                            else if ((next_a - a_i) < (next_b - b_i)) {
                                while (a_i < next_a) {
                                    printf("%c", a[i][a_i ++]);
                                }
                            }
                            else {
                                while (b_i < next_b) {
                                    printf("%c", b[i][b_i ++]);
                                }
                            }
                        }
                        else if (a[i][next_a] < b[i][next_b] ) {
                            while (a_i < next_a) {
                                printf("%c", a[i][a_i ++]);
                            }
                        }
                        else {
                            while (b_i < next_b) {
                                printf("%c", b[i][b_i ++]);
                            }
                        }
                    }
                    else if (a[i][next_a]) {
                        if (a[i][next_a] > a[i][a_i]) {
                            printf("%s", &b[i][b_i]);
                            printf("%s", &a[i][a_i]);
                            break;
                        }
                        else {
                            while (a_i < next_a) {
                                printf("%c", a[i][a_i ++]);
                            }
                        }
                    }
                    else if (b[i][next_b]) {
                        if (b[i][next_b] > b[i][b_i]) {
                            printf("%s", &a[i][a_i]);
                            printf("%s", &b[i][b_i]);
                            break;
                        }
                        else {
                            while (b_i < next_b) {
                                printf("%c", b[i][b_i ++]);
                            }
                        }
                    }
                    else {
                        printf("%s", &a[i][a_i]);
                        printf("%s", &b[i][b_i]);
                        break;
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
