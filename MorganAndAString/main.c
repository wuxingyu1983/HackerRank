#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define DEBUG       0

int getNextDiff(char s[], int index) {
    int ret = index + 1;

    while (s[ret]) {
        if (s[ret] != s[index]) {
            break;
        }

        ret ++;
    }

    return ret;
}

int aOrB(char a[], int a_i, char b[], int b_i, int val) {
    int ret = 0;

    while (a[a_i] || b[b_i]) {
        if (a[a_i] && b[b_i]) {
            if (a[a_i] == b[b_i] && a[a_i] <= val) {
                a_i ++;
                b_i ++;
            }
            else if (a[a_i] < b[b_i]) {
                ret = -1;
                break;
            }
            else {
                ret = 1;
                break;
            }
        }
        else if (a[a_i]) {
            ret = -1;
            break;
        }
        else {
            ret = 1;
            break;
        }
    }

    return ret;
}

void morgan(char a[], char b[]) {
    int a_i = 0, b_i = 0;
    while (a[a_i] || b[b_i]) {
        if (a[a_i] && b[b_i]) {
            if (a[a_i] == b[b_i]) {
                int next_a = getNextDiff(a, a_i);
                int next_b = getNextDiff(b, b_i);

                if (a[next_a] && b[next_b]) {
                    if (a[next_a] > a[a_i] && b[next_b] > b[b_i]) {
                        while (a_i < next_a) {
                            printf("%c", a[a_i ++]);
                        }
                        while (b_i < next_b) {
                            printf("%c", b[b_i ++]);
                        }
                    }
                    else if (a[next_a] < a[a_i] && b[next_b] < b[b_i]) {
                        if ((next_a - a_i) == (next_b - b_i)) {
                            if (0 > aOrB(a, next_a, b, next_b, a[a_i])) {
                                while (a_i < next_a) {
                                    printf("%c", a[a_i ++]);
                                }
                            }
                            else {
                                while (b_i < next_b) {
                                    printf("%c", b[b_i ++]);
                                }
                            }
                        }
                        else if ((next_a - a_i) < (next_b - b_i)) {
                            while (a_i < next_a) {
                                printf("%c", a[a_i ++]);
                            }
                        }
                        else {
                            while (b_i < next_b) {
                                printf("%c", b[b_i ++]);
                            }
                        }
                    }
                    else if (a[next_a] < b[next_b] ) {
                        while (a_i < next_a) {
                            printf("%c", a[a_i ++]);
                        }
                    }
                    else {
                        while (b_i < next_b) {
                            printf("%c", b[b_i ++]);
                        }
                    }
                }
                else if (a[next_a]) {
                    if (a[next_a] > a[a_i]) {
                        printf("%s", &b[b_i]);
                        printf("%s", &a[a_i]);
                        break;
                    }
                    else {
                        while (a_i < next_a) {
                            printf("%c", a[a_i ++]);
                        }
                    }
                }
                else if (b[next_b]) {
                    if (b[next_b] > b[b_i]) {
                        printf("%s", &a[a_i]);
                        printf("%s", &b[b_i]);
                        break;
                    }
                    else {
                        while (b_i < next_b) {
                            printf("%c", b[b_i ++]);
                        }
                    }
                }
                else {
                    printf("%s", &a[a_i]);
                    printf("%s", &b[b_i]);
                    break;
                }
            }
            else {
                if (a[a_i] < b[b_i]) {
                    printf("%c", a[a_i]);
                    a_i ++;
                }
                else {
                    // a[a_i] > b[b_i]
                    printf("%c", b[b_i]);
                    b_i ++;
                }
            }
        }
        else if (a[a_i]) {
            printf("%s", &a[a_i]);
            break;
        }
        else {
            printf("%s", &b[b_i]);
            break;
        }
    }

    printf("\n");
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
        morgan(a[i], b[i]);
    }

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
