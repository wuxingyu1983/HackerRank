//
//  main.cpp
//  test
//
//  Created by 吴星煜 on 2018/8/18.
//  Copyright © 2018年 吴星煜. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX_LEN        1500

int c[MAX_LEN][MAX_LEN];
int l[MAX_LEN][MAX_LEN];

int lcs(string& s1, string& s2, int k) {
    int ret = 0;

    memset(c, 0, sizeof(int) * MAX_LEN * MAX_LEN);
    memset(l, 0, sizeof(int) * MAX_LEN * MAX_LEN);

    int len = s1.length();

    for (size_t i = 0; i < len; i++) {
        for (size_t j = i; j < len; j++) {
            if (0 == i) {
                if (s1.at(i) == s2.at(j)) {
                    l[i][j] = 1;
                    if (ret < 1) {
                        ret = 1;
                    }
                }
                else {
                    l[i][j] = 1;
                    c[i][j] = 1;
                }
            }
            else {
                if (s1.at(i) == s2.at(j)) {
                    if (c[i - 1][j - 1] <= k) {
                        l[i][j] = l[i - 1][j - 1] + 1;
                        c[i][j] = c[i - 1][j - 1];
                    }
                    else {
                        if (s1.at(i - l[i - 1][j - 1]) == s2.at(j - l[i - 1][j - 1])) {
                            l[i][j] = l[i - 1][j - 1];
                            c[i][j] = c[i - 1][j - 1];
                        }
                        else {
                            l[i][j] = l[i - 1][j - 1];
                            c[i][j] = c[i - 1][j - 1] - 1;
                        }
                    }

                    if (c[i][j] <= k && l[i][j] > ret) {
                        ret = l[i][j];
                    }
                }
                else {
                    if (c[i - 1][j - 1] + 1 <= k) {
                        l[i][j] = l[i - 1][j - 1] + 1;
                        c[i][j] = c[i - 1][j - 1] + 1;
                    }
                    else {
                        if (s1.at(i - l[i - 1][j - 1]) == s2.at(j - l[i - 1][j - 1])) {
                            l[i][j] = l[i - 1][j - 1];
                            c[i][j] = c[i - 1][j - 1] + 1;
                        }
                        else {
                            l[i][j] = l[i - 1][j - 1];
                            c[i][j] = c[i - 1][j - 1];
                        }
                    }

                    if (c[i][j] <= k && l[i][j] > ret) {
                        ret = l[i][j];
                    }
                }
            }
        }
    }

    for (size_t j = 0; j < len; j++) {
        for (size_t i = j; i < len; i++) {
            if (0 == j) {
                if (s1.at(i) == s2.at(j)) {
                    l[i][j] = 1;
                    if (ret < 1) {
                        ret = 1;
                    }
                }
                else {
                    l[i][j] = 1;
                    c[i][j] = 1;
                }
            }
            else {
                if (s1.at(i) == s2.at(j)) {
                    if (c[i - 1][j - 1] <= k) {
                        l[i][j] = l[i - 1][j - 1] + 1;
                        c[i][j] = c[i - 1][j - 1];
                    }
                    else {
                        if (s1.at(i - l[i - 1][j - 1]) == s2.at(j - l[i - 1][j - 1])) {
                            l[i][j] = l[i - 1][j - 1];
                            c[i][j] = c[i - 1][j - 1];
                        }
                        else {
                            l[i][j] = l[i - 1][j - 1];
                            c[i][j] = c[i - 1][j - 1] - 1;
                        }
                    }

                    if (c[i][j] <= k && l[i][j] > ret) {
                        ret = l[i][j];
                    }
                }
                else {
                    if (c[i - 1][j - 1] + 1 <= k) {
                        l[i][j] = l[i - 1][j - 1] + 1;
                        c[i][j] = c[i - 1][j - 1] + 1;
                    }
                    else {
                        if (s1.at(i - l[i - 1][j - 1]) == s2.at(j - l[i - 1][j - 1])) {
                            l[i][j] = l[i - 1][j - 1];
                            c[i][j] = c[i - 1][j - 1] + 1;
                        }
                        else {
                            l[i][j] = l[i - 1][j - 1];
                            c[i][j] = c[i - 1][j - 1];
                        }
                    }

                    if (c[i][j] <= k && l[i][j] > ret) {
                        ret = l[i][j];
                    }
                }
            }
        }
    }

    return ret;
}

int main()
{
    int t;
    cin >> t;

    for (int t_itr = 0; t_itr < t; t_itr++)
    {
        int k;
        string s1, s2;

        cin >> k >> s1 >> s2;

        int result = lcs(s1, s2, k);

        cout << result << "\n";
    }

    return 0;
}
