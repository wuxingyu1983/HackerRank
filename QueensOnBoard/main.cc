#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define DEBUG   0
#define MOD     1000000007
#define N       50
#define M       5

// row, major diagonal, minor diagonal
unsigned int status[N][1 << M][1 << M][1 << M];
unsigned char board[N];

bool valid_current(char sta, char board, int m) {
    bool ret = true;

    int pre_pos = -1;
    for (size_t pos = 0; pos < m; pos++) {
        if (sta & (1 << pos)) {
            if (board & (1 << pos)) {
                // blocked
                ret = false;
                break;
            }
            else {
                if (0 > pre_pos) {
                    pre_pos = pos;
                }
                else {
                    // no blocked square between pre_pos and pos
                    ret = false;
                    break;
                }
            }
        }
        else {
            if (board & (1 << pos)) {
                // blocked, clean pre pos
                pre_pos = -1;
            }
        }
    }

    return ret;
}

bool valid_pre(char sta, char pre_sta, char pre_major, char pre_minor) {
    if (sta & pre_sta) {
        return false;
    }

    if (sta & (pre_major << 1)) {
        return false;
    }

    if (sta & (pre_minor >> 1)) {
        return false;
    }

    return true;
}

int main() {
    int t;

#if DEBUG
    FILE * fp = fopen("input.txt", "r");
    fscanf(fp, "%d", &t);
#else
    scanf("%d", &t);
#endif

    for (size_t i = 0; i < t; i++) {
        int n, m;

#if DEBUG
        fscanf(fp, "%d %d", &n, &m);
#else
        scanf("%d %d", &n, &m);
#endif

        for (size_t row = 0; row < n; row++) {
            board[row] = 0;

            char c[30];
#if DEBUG
            fscanf(fp, "%s", c);
#else
            scanf("%s", c);
#endif
            for (size_t col = 0; col < m; col++) {
                if ('#' == c[col]) {
                    // a blocked square
                    board[row] |= 1 << col;
                }
            }
        }

        // process
        memset(status, 0, sizeof(status));
        unsigned int ret = 0;
        for (size_t row = 0; row < n; row++) {
            for (char sta = 0; sta < (1 << m); sta++) {
                if (valid_current(sta, board[row], m)) {
                    if (0 == row) {
                        status[row][sta][sta][sta] = 1;
                        if ((n - 1) == row) {
                            // last row
                            ret ++;
                        }
                    }
                    else {
                        for (char pre_sta = 0; pre_sta < (1 << m); pre_sta++) {
                            for (char pre_major = 0; pre_major < (1 << m); pre_major++) {
                                for (char pre_minor = 0; pre_minor < (1 << m); pre_minor++) {
                                    if (status[row - 1][pre_sta][pre_major][pre_minor]) {
                                        if (valid_pre(sta, pre_sta, pre_major, pre_minor)) {
                                            // new_sta, new_major, new_minor
                                            char new_sta = 0;
                                            for (size_t pos = 0; pos < m; pos++) {
                                                if (board[row] & (1 << pos)) {
                                                    // blocked
                                                }
                                                else {
                                                    new_sta |= ((sta & (1 << pos)) | (pre_sta & (1 << pos)));
                                                }
                                            }

                                            char new_major = 0;
                                            for (size_t pos = 0; pos < m; pos++) {
                                                if (0 == pos) {
                                                    if (sta & 1) {
                                                        new_major = 1;
                                                    }
                                                }
                                                else {
                                                    if (board[row] & (1 << pos)) {
                                                        // blocked
                                                    }
                                                    else {
                                                        if ((sta & (1 << pos)) || (pre_major & (1 << (pos - 1)))) {
                                                            new_major |= 1 << pos;
                                                        }
                                                    }
                                                }
                                            }

                                            char new_minor = 0;
                                            for (size_t pos = 0; pos < m; pos++) {
                                                if (m - 1 == pos) {
                                                    if (sta & (1 << pos)) {
                                                        new_minor |= (1 << pos);
                                                    }
                                                }
                                                else {
                                                    if (board[row] & (1 << pos)) {
                                                        // blocked
                                                    }
                                                    else {
                                                        if ((sta & (1 << pos)) || (pre_minor & (1 << (pos + 1)))) {
                                                            new_minor |= 1 << pos;
                                                        }
                                                    }
                                                }
                                            }

                                            status[row][new_sta][new_major][new_minor] += status[row - 1][pre_sta][pre_major][pre_minor];
                                            status[row][new_sta][new_major][new_minor] %= MOD;

                                            if ((n - 1) == row) {
                                                // last row
                                                ret += status[row - 1][pre_sta][pre_major][pre_minor];
                                                ret %= MOD;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        ret += MOD - 1;
        ret %= MOD;

        printf("%u\n", ret);
    }

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
