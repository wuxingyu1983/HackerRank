#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int cnt[26];
int remain[26];
int pos[26][10000];

int getPLT(int curr_pos, int letter) {
    int ret = -1;

    for (size_t i = 0; i < cnt[letter]; i++) {
        if (curr_pos > pos[letter][i]) {
            ret = pos[letter][i];
            break;
        }
    }

    return ret;
}

bool valid(int letter, int new_pos) {
    bool ret = true;

    return ret;
}

int main() {
    char str[10001];
    scanf("%s", str);

    int len = strlen(str);

    char * output = malloc(sizeof(char) * (len / 2 + 1));
    memset(output, 0, sizeof(char) * (len / 2 + 1));

    memset(cnt, 0, sizeof(int) * 26);
    memset(remain, 0, sizeof(int) * 26);

    for (int i = len - 1; i >= 0; i --) {
        int index = str[i] - 'a';
        pos[index][cnt[index]] = i;
        cnt[index] ++;
    }

    for (size_t i = 0; i < 26; i++) {
        remain[i] = cnt[i] / 2;
    }

    int curr = 0;
    int curr_pos = 10001;
    while (curr < (len / 2)) {
        for (size_t i = 0; i < 26; i++) {
            if (remain[i]) {
                // find max pos < curr_pos, binary search
                int tmp_pos = getPLT(curr_pos, i);
                if (0 > tmp_pos) {
                    continue;
                }
                size_t j = 0;
                for (j = 0; j < 26; j++) {
                    if (j != i && remain[j]) {
                        if (pos[j][cnt[j] - remain[j]] > tmp_pos) {
                            break;
                        }
                    }
                }

                if (26 == j) {
                    output[curr] = 'a' + i;
                    remain[i] --;
                    curr_pos = tmp_pos;
                    break;
                }
            }
        }

        curr ++;
    }

    printf("%s\n", output);

    free(output);

    return 0;
}
