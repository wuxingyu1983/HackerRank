//
//  main.cpp
//  test
//
//  Created by 吴星煜 on 2018/4/11.
//  Copyright © 2018年 吴星煜. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX_N       400000
#define MOD         1000000007
#define DEBUG		0

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43};
int flag[45];
int sum[10000];
int tmp_sum[2][10000];
int digital[10000][10];

unsigned int cnt[MAX_N + 1];

int main() {
    int q;

#if DEBUG
    FILE * fp = fopen("input.txt", "r");
    FILE * fp_out = fopen("output.txt", "w");
    fscanf(fp, "%d", &q);
#else
    scanf("%d", &q);
#endif

    vector<unsigned int> inputs;
    inputs.reserve(q);

    unsigned int max_n = 0;
    for (size_t i = 0; i < q; i++) {
        unsigned int n;
#if DEBUG
        fscanf(fp, "%u", &n);
#else
        scanf("%u", &n);
#endif
        if (n > max_n) {
            max_n = n;
        }
        inputs.push_back(n);
    }

    for (size_t i = 0; i < 14; i++) {
        flag[primes[i]] = 1;
    }

    for (size_t i = 0; i < 10000; i++) {
        digital[i][0] = -1;
    }

    vector< set<int> > tmp_set(2);

    cnt[1] = 9;
    cnt[2] = 90;
    for (size_t i = 3; i <= max_n; i++) {
        if (3 == i) {
            for (size_t j = 1; j <= 9; j++) {
                if (flag[j]) {
                    sum[j] = j;
                }
            }
            for (size_t j = 10; j <= 99; j++) {
                int s = (j / 10) + (j % 10);
                if (flag[s]) {
                    sum[j] = s;
                }
            }
            int c = 0;
            for (size_t j = 100; j <= 999; j++) {
                int s = (j / 100) + (j % 100) / 10 + (j % 10);
                if (flag[s]) {
                    sum[j] = s;
                    c ++;
                }
            }
            cnt[i] = c;
        }
        else if (4 == i) {
            int c = 0;
            for (size_t j = 1000; j <= 9999; j++) {
                if (sum[(j / 10)] && sum[(j % 1000)]) {
                    int s = (j / 1000) + sum[(j % 1000)];
                    if (flag[s]) {
                        sum[j] = s;
                        c ++;
                    }
                }
            }
            cnt[i] = c;
        }
        else if (5 == i) {
            int c = 0;
            tmp_set[i % 2].clear();
            for (size_t j = 10000; j <= 99999; j++) {
                if (sum[(j / 10)] && sum[(j % 10000)]) {
                    int s = (j / 10000) + sum[(j % 10000)];
                    if (flag[s]) {
                        tmp_sum[i % 2][j % 10000] ++;
                        tmp_set[i % 2].insert(j % 10000);
                        c ++;
                    }
                }
            }
            cnt[i] = c;
        }
        else {
            int c = 0;
            tmp_set[i % 2].clear();
            set<int>::iterator iter = tmp_set[1 - i % 2].begin();
            while (iter != tmp_set[1 - i % 2].end()) {
                if (-1 == digital[*iter][0]) {
                    int index_in_digital = 0;
                    for (size_t j = 0; j < 10; j++) {
                        int new_index = (*iter * 10 + j) % 10000;
                        if (sum[new_index]) {
                            int s = sum[new_index] + (*iter / 1000);
                            if (flag[s]) {
                                digital[*iter][index_in_digital ++] = j;

                                set<int>::iterator find_it = tmp_set[i % 2].find(new_index);
                                if (find_it == tmp_set[i % 2].end()) {
                                    // no found
                                    tmp_sum[i % 2][new_index] = tmp_sum[1 - i % 2][*iter];
                                }
                                else {
                                    tmp_sum[i % 2][new_index] += tmp_sum[1 - i % 2][*iter];
                                    tmp_sum[i % 2][new_index] %= MOD;
                                }
                                c += tmp_sum[1 - i % 2][*iter];
                                c %= MOD;

                                tmp_set[i % 2].insert(new_index);
                            }
                        }
                    }

                    digital[*iter][index_in_digital] = -2;
                }
                else if (0 <= digital[*iter][0]) {
                    int index_in_digital = 0;
                    while(0 <= digital[*iter][index_in_digital]) {
                        int j = digital[*iter][index_in_digital];
                        int new_index = (*iter * 10 + j) % 10000;
                        if (sum[new_index]) {
                            int s = sum[new_index] + (*iter / 1000);
                            if (flag[s]) {
                                set<int>::iterator find_it = tmp_set[i % 2].find(new_index);
                                if (find_it == tmp_set[i % 2].end()) {
                                    // no found
                                    tmp_sum[i % 2][new_index] = tmp_sum[1 - i % 2][*iter];
                                }
                                else {
                                    tmp_sum[i % 2][new_index] += tmp_sum[1 - i % 2][*iter];
                                    tmp_sum[i % 2][new_index] %= MOD;
                                }
                                c += tmp_sum[1 - i % 2][*iter];
                                c %= MOD;

                                tmp_set[i % 2].insert(new_index);
                            }
                        }

                        index_in_digital ++;
                    }
                }
                else {
                    // - 2
                }

                ++ iter;
            }

            cnt[i] = c;
        }
    }

    for (size_t i = 0; i < q; i++) {
#if DEBUG
        fprintf(fp_out, "%u\n", cnt[inputs[i]]);
#else
        printf("%u\n", cnt[inputs[i]]);
#endif
    }

#if DEBUG
    fclose(fp);
    fclose(fp_out);
#endif

    return 0;
}
