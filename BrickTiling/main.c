#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

const int MOD = 1000000007;
unsigned long long tmp[22][1 << 8][1<< 8];
int n, m;
int curr, next;

int valid(int s, int pos) {
    return (s & 1 << pos) == 0;
}

void func(int p, int s1, int s2, int s3, int initk, int initl) {
    if (s1 == ((1 << m) - 1)) {
        tmp[next][s2][s3] = (tmp[next][s2][s3] + tmp[curr][initk][initl]) % MOD;
        return;
    }

    if (s1 & (1 << p)) {
        func(p + 1, s1, s2, s3, initk, initl);
    }
    else {
        // ###
        //   #
        if (p + 2 <= m - 1 && valid(s1, p) && valid(s1, p + 1) && valid(s1, p + 2) && valid(s2, p + 2)) {
            func(p + 3, s1 | (1 << p) | (1 << (p + 1)) | (1 << (p + 2)), s2 | (1 << (p + 2)), s3, initk, initl);
        }

        //   #
        // ###
        if (p >= 2 && p <= m - 1 && valid(s1, p) && valid(s2, p - 2) && valid(s2, p - 1) && valid(s2, p)) {
            func(p + 1, s1 | (1 << p), s2 | (1 << (p - 2)) | (1 << (p - 1)) | (1 << p), s3, initk, initl);
        }

        // #
        // ###
        if (p + 2 <= m - 1 && valid(s1, p) && valid(s2, p) && valid(s2, p + 1) && valid(s2, p + 2)) {
            func(p + 1, s1 | (1 << p), s2 | (1 << p) | (1 << (p + 1)) | (1 << (p + 2)), s3, initk, initl);
        }

        // ###
        // #
        if (p + 2 <= m - 1 && valid(s1, p) && valid(s1, p + 1) && valid(s1, p + 2) && valid(s2, p)) {
            func(p + 3, s1 | (1 << p) | (1 << (p + 1)) | (1 << (p + 2)), s2 | (1 << p), s3, initk, initl);
        }

        // ##
        //  #
        //  #
        if (p + 1 <= m - 1 && valid(s1, p) && valid(s1, p + 1) && valid(s2, p + 1) && valid(s3, p + 1)) {
            func(p + 2, s1 | (1 << p) | (1 << (p + 1)), s2 | (1 << (p + 1)), s3 | (1 << (p + 1)), initk, initl);
        }

        //  #
        //  #
        // ##
        if (p >= 1 && p <= m - 1 && valid(s1, p) && valid(s2, p) && valid(s3, p - 1) && valid(s3, p)) {
            func(p + 1, s1 | (1 << p), s2 | (1 << p), s3 | (1 << (p - 1)) | (1 << p), initk, initl);
        }

        // ##
        // #
        // #
        if (p + 1 <= m - 1 && valid(s1, p) && valid(s1, p + 1) && valid(s2, p) && valid(s3, p)) {
            func(p + 2, s1 | (1 << p) | (1 << (p + 1)), s2 | (1 << p), s3 | (1 << p), initk, initl);
        }

        // #
        // #
        // ##
        if (p + 1 <= m - 1 && valid(s1, p) && valid(s2, p) && valid(s3, p) && valid(s3, p + 1)) {
            func(p + 1, s1 | (1 << p), s2 | (1 << p), s3 | (1 << p) | (1 << (p + 1)), initk, initl);
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);

    unsigned long long * outputs = malloc(sizeof(unsigned long long) * t);
    for (int i = 0; i < t; i ++) {
        scanf("%d %d", &n, &m);

        int state[20];
        int cnt = 0;
        for (int j = 0; j < n; j ++) {
            state[j] = 0;
            for (int k = 0; k < m; k ++) {
                char p;
                scanf("%c", &p);
                if ('#' == p) {
                    state[j] |= (1 << k);
                }
                else {
                    cnt ++;
                }
            }
        }

        if (0 == cnt) {
            outputs[i] = 1;
            continue;
        }

        if (0 != (cnt % 4)) {
            outputs[i] = 0;
            continue;
        }

        memset(tmp, 0, sizeof(tmp));

        tmp[1][state[0]][state[1]] = 1;

        for (int j = 1; j < n - 1; j ++) {
            curr = j;
            next = j + 1;
            for (int k = 0; k < (1 << m); k ++) {
                for (int l = 0; l < (1 << m); l ++) {
                    if (0 == tmp[1][k][l]) {
                        continue;
                    }
                    func(0, k, l, state[j + 1], k, l);
                }
            }
        }

        outputs[i] = tmp[n- 1][(1 << m) - 1][(1 << m) - 1];
    }

    for (int i = 0; i < t; i ++) {
        printf("%llu\n", outputs[i]);
    }

    free(outputs);

    return 0;
}
