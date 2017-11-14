#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN     12
#define MAX_N       31

char s[MAX_N][MAX_LEN + 1];     // 排序后的
int impossible[MAX_LEN][10];
int c[MAX_N];                   // 排序后的
int output[MAX_LEN];

char tmp_s[4][MAX_N][MAX_LEN + 1];

bool unique() {
    bool ret = true;

    for (size_t i = 0; i < MAX_LEN; i++) {
        if (0 > output[i]) {
            int possible = 0;
            for (size_t j = 0; j < 10; j++) {
                if (0 == impossible[i][j]) {
                    possible ++;
                }
            }
            if (1 < possible) {
                ret = false;
                break;
            }
        }
    }

    return ret;
}

void print_output() {
    for (size_t i = 0; i < MAX_LEN; i++) {
        if (0 <= output[i]) {
            printf("%d", output[i]);
        }
        else {
            for (size_t j = 0; j < 10; j++) {
                if (0 == impossible[i][j]) {
                    printf("%ld", j);
                    break;
                }
            }
        }
    }
    printf("\n");
}

bool func(int n, int index) {
    bool ret = true;

    int already = 0;
    for (size_t i = 0; i < MAX_LEN; i++) {
        if (output[i] == (s[index][i] - '0')) {
            already ++;
        }
    }

    if (0 == c[index]) {
        // mark impossible
        for (size_t i = 0; i < MAX_LEN; i++) {
            impossible[i][s[index][i] - '0'] ++;
        }

        if (index < n - 1) {
            ret = func(n, index + 1);
        }
        else {
            if (unique()) {
                ret = true;
            }
            else {
                ret = false;
            }
        }
    }
    else if (1 == c[index]) {
        if (1 < already) {
            ret = false;
        }
        else if (1 == already) {
            for (size_t i = 0; i < MAX_LEN; i++) {
                if (output[i] != (s[index][i] - '0')) {
                    impossible[i][s[index][i] - '0'] ++;
                }
            }

            if (index < n - 1) {
                ret = func(n, index + 1);
            }
            else {
                if (unique()) {
                    ret = true;
                }
                else {
                    ret = false;
                }
            }

            if (false == ret) {
                for (size_t i = 0; i < MAX_LEN; i++) {
                    if (output[i] != (s[index][i] - '0')) {
                        impossible[i][s[index][i] - '0'] --;
                    }
                }
            }
        }
        else {
            // 0 == already
            for (size_t i = 0; i < MAX_LEN; i++) {
                if (output[i] != (s[index][i] - '0')) {
                    impossible[i][s[index][i] - '0'] ++;
                }
            }

            ret = false;
            for (size_t pos1 = 0; pos1 < MAX_LEN; pos1++) {
                if (0 > output[pos1] && 1 == impossible[pos1][s[index][pos1] - '0']) {
                    impossible[pos1][s[index][pos1] - '0'] --;
                    output[pos1] = s[index][pos1] - '0';

                    if (index < n - 1) {
                        ret = func(n, index + 1);
                    }
                    else {
                        if (unique()) {
                            ret = true;
                        }
                        else {
                            ret = false;
                        }
                    }

                    if (ret) {
                        return ret;
                    }
                    else {
                        impossible[pos1][s[index][pos1] - '0'] ++;
                        output[pos1] = -1;
                    }
                }
            }

            if (false == ret) {
                for (size_t i = 0; i < MAX_LEN; i++) {
                    if (output[i] != (s[index][i] - '0')) {
                        impossible[i][s[index][i] - '0'] --;
                    }
                }
            }
        }
    }
    else if (2 == c[index]) {
        if (2 < already) {
            ret = false;
        }
        else if (2 == already) {
            for (size_t i = 0; i < MAX_LEN; i++) {
                if (output[i] != (s[index][i] - '0')) {
                    impossible[i][s[index][i] - '0'] ++;
                }
            }

            if (index < n - 1) {
                ret = func(n, index + 1);
            }
            else {
                if (unique()) {
                    ret = true;
                }
                else {
                    ret = false;
                }
            }

            if (false == ret) {
                for (size_t i = 0; i < MAX_LEN; i++) {
                    if (output[i] != (s[index][i] - '0')) {
                        impossible[i][s[index][i] - '0'] --;
                    }
                }
            }
        }
        else if (1 == already) {
            for (size_t i = 0; i < MAX_LEN; i++) {
                if (output[i] != (s[index][i] - '0')) {
                    impossible[i][s[index][i] - '0'] ++;
                }
            }

            ret = false;
            for (size_t pos1 = 0; pos1 < MAX_LEN; pos1++) {
                if (0 > output[pos1] && 1 == impossible[pos1][s[index][pos1] - '0']) {
                    impossible[pos1][s[index][pos1] - '0'] --;
                    output[pos1] = s[index][pos1] - '0';

                    if (index < n - 1) {
                        ret = func(n, index + 1);
                    }
                    else {
                        if (unique()) {
                            ret = true;
                        }
                        else {
                            ret = false;
                        }
                    }

                    if (ret) {
                        return ret;
                    }
                    else {
                        impossible[pos1][s[index][pos1] - '0'] ++;
                        output[pos1] = -1;
                    }
                }
            }

            if (false == ret) {
                for (size_t i = 0; i < MAX_LEN; i++) {
                    if (output[i] != (s[index][i] - '0')) {
                        impossible[i][s[index][i] - '0'] --;
                    }
                }
            }
        }
        else {
            // 0 == already
            for (size_t i = 0; i < MAX_LEN; i++) {
                if (output[i] != (s[index][i] - '0')) {
                    impossible[i][s[index][i] - '0'] ++;
                }
            }

            ret = false;
            for (size_t pos1 = 0; pos1 < MAX_LEN - 1; pos1++) {
                for (size_t pos2 = pos1 + 1; pos2 < MAX_LEN; pos2++) {
                    if (0 > output[pos1] && 1 == impossible[pos1][s[index][pos1] - '0'] && 0 > output[pos2] && 1 == impossible[pos2][s[index][pos2] - '0']) {
                        impossible[pos1][s[index][pos1] - '0'] --;
                        output[pos1] = s[index][pos1] - '0';
                        impossible[pos2][s[index][pos2] - '0'] --;
                        output[pos2] = s[index][pos2] - '0';

                        if (index < n - 1) {
                            ret = func(n, index + 1);
                        }
                        else {
                            if (unique()) {
                                ret = true;
                            }
                            else {
                                ret = false;
                            }
                        }

                        if (ret) {
                            return ret;
                        }
                        else {
                            impossible[pos1][s[index][pos1] - '0'] ++;
                            output[pos1] = -1;
                            impossible[pos2][s[index][pos2] - '0'] ++;
                            output[pos2] = -1;
                        }
                    }
                }
            }

            if (false == ret) {
                for (size_t i = 0; i < MAX_LEN; i++) {
                    if (output[i] != (s[index][i] - '0')) {
                        impossible[i][s[index][i] - '0'] --;
                    }
                }
            }
        }
    }
    else {
        // 3 == c[index]
        if (3 < already) {
            ret = false;
        }
        else if (3 == already) {
            for (size_t i = 0; i < MAX_LEN; i++) {
                if (output[i] != (s[index][i] - '0')) {
                    impossible[i][s[index][i] - '0'] ++;
                }
            }

            if (index < n - 1) {
                ret = func(n, index + 1);
            }
            else {
                if (unique()) {
                    ret = true;
                }
                else {
                    ret = false;
                }
            }

            if (false == ret) {
                for (size_t i = 0; i < MAX_LEN; i++) {
                    if (output[i] != (s[index][i] - '0')) {
                        impossible[i][s[index][i] - '0'] --;
                    }
                }
            }
        }
        else if (2 == already) {
            for (size_t i = 0; i < MAX_LEN; i++) {
                if (output[i] != (s[index][i] - '0')) {
                    impossible[i][s[index][i] - '0'] ++;
                }
            }

            ret = false;
            for (size_t pos1 = 0; pos1 < MAX_LEN; pos1++) {
                if (0 > output[pos1] && 1 == impossible[pos1][s[index][pos1] - '0']) {
                    impossible[pos1][s[index][pos1] - '0'] --;
                    output[pos1] = s[index][pos1] - '0';

                    if (index < n - 1) {
                        ret = func(n, index + 1);
                    }
                    else {
                        if (unique()) {
                            ret = true;
                        }
                        else {
                            ret = false;
                        }
                    }

                    if (ret) {
                        return ret;
                    }
                    else {
                        impossible[pos1][s[index][pos1] - '0'] ++;
                        output[pos1] = -1;
                    }
                }
            }

            if (false == ret) {
                for (size_t i = 0; i < MAX_LEN; i++) {
                    if (output[i] != (s[index][i] - '0')) {
                        impossible[i][s[index][i] - '0'] --;
                    }
                }
            }
        }
        else if (1 == already) {
            for (size_t i = 0; i < MAX_LEN; i++) {
                if (output[i] != (s[index][i] - '0')) {
                    impossible[i][s[index][i] - '0'] ++;
                }
            }

            ret = false;
            for (size_t pos1 = 0; pos1 < MAX_LEN - 1; pos1++) {
                for (size_t pos2 = pos1 + 1; pos2 < MAX_LEN; pos2++) {
                    if (0 > output[pos1] && 1 == impossible[pos1][s[index][pos1] - '0'] && 0 > output[pos2] && 1 == impossible[pos2][s[index][pos2] - '0']) {
                        impossible[pos1][s[index][pos1] - '0'] --;
                        output[pos1] = s[index][pos1] - '0';
                        impossible[pos2][s[index][pos2] - '0'] --;
                        output[pos2] = s[index][pos2] - '0';

                        if (index < n - 1) {
                            ret = func(n, index + 1);
                        }
                        else {
                            if (unique()) {
                                ret = true;
                            }
                            else {
                                ret = false;
                            }
                        }

                        if (ret) {
                            return ret;
                        }
                        else {
                            impossible[pos1][s[index][pos1] - '0'] ++;
                            output[pos1] = -1;
                            impossible[pos2][s[index][pos2] - '0'] ++;
                            output[pos2] = -1;
                        }
                    }
                }
            }

            if (false == ret) {
                for (size_t i = 0; i < MAX_LEN; i++) {
                    if (output[i] != (s[index][i] - '0')) {
                        impossible[i][s[index][i] - '0'] --;
                    }
                }
            }
        }
        else {
            // 0 == already
            for (size_t i = 0; i < MAX_LEN; i++) {
                if (output[i] != (s[index][i] - '0')) {
                    impossible[i][s[index][i] - '0'] ++;
                }
            }

            ret = false;
            for (size_t pos1 = 0; pos1 < MAX_LEN - 2; pos1++) {
                for (size_t pos2 = pos1 + 1; pos2 < MAX_LEN - 1; pos2++) {
                    for (size_t pos3 = pos2 + 1; pos3 < MAX_LEN; pos3++) {
                        if (0 > output[pos1] && 1 == impossible[pos1][s[index][pos1] - '0'] && 0 > output[pos2] && 1 == impossible[pos2][s[index][pos2] - '0'] && 0 > output[pos3] && 1 == impossible[pos3][s[index][pos3] - '0']) {
                            impossible[pos1][s[index][pos1] - '0'] --;
                            output[pos1] = s[index][pos1] - '0';
                            impossible[pos2][s[index][pos2] - '0'] --;
                            output[pos2] = s[index][pos2] - '0';
                            impossible[pos3][s[index][pos3] - '0'] --;
                            output[pos3] = s[index][pos3] - '0';

                            if (index < n - 1) {
                                ret = func(n, index + 1);
                            }
                            else {
                                if (unique()) {
                                    ret = true;
                                }
                                else {
                                    ret = false;
                                }
                            }

                            if (ret) {
                                return ret;
                            }
                            else {
                                impossible[pos1][s[index][pos1] - '0'] ++;
                                output[pos1] = -1;
                                impossible[pos2][s[index][pos2] - '0'] ++;
                                output[pos2] = -1;
                                impossible[pos3][s[index][pos3] - '0'] ++;
                                output[pos3] = -1;
                            }
                        }
                    }
                }
            }

            if (false == ret) {
                for (size_t i = 0; i < MAX_LEN; i++) {
                    if (output[i] != (s[index][i] - '0')) {
                        impossible[i][s[index][i] - '0'] --;
                    }
                }
            }
        }
    }

    return ret;
}

int main() {
    int n;
    scanf("%d", &n);

    char tmp[MAX_LEN + 1];
    int correct;
    int index0 = 0, index1 = 0, index2 = 0, index3 = 0;
    for (size_t i = 0; i < n; i++) {
        scanf("%s %d", tmp, &correct);
        switch (correct) {
            case 0: {
                strcpy(tmp_s[0][index0 ++], tmp);
            }
            break;
            case 1: {
                strcpy(tmp_s[1][index1 ++], tmp);
            }
            break;
            case 2: {
                strcpy(tmp_s[2][index2 ++], tmp);
            }
            break;
            case 3:
            default: {
                strcpy(tmp_s[3][index3 ++], tmp);
            }
            break;
        }
    }

    int index = 0;
    for (size_t i = 0; i < index0; i++) {
        strcpy(s[index], tmp_s[0][i]);
        c[index ++] = 0;
    }

    for (size_t i = 0; i < index1; i++) {
        strcpy(s[index], tmp_s[1][i]);
        c[index ++] = 1;
    }

    for (size_t i = 0; i < index2; i++) {
        strcpy(s[index], tmp_s[2][i]);
        c[index ++] = 2;
    }

    for (size_t i = 0; i < index3; i++) {
        strcpy(s[index], tmp_s[3][i]);
        c[index ++] = 3;
    }

    for (size_t i = 0; i < MAX_LEN; i++) {
        output[i] = -1;
    }

    func(n, 0);

    print_output();

    return 0;
}
