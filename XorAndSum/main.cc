//
//  main.cpp
//  test
//
//  Created by 吴星煜 on 2018/9/19.
//  Copyright © 2018年 吴星煜. All rights reserved.
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#define MOD         1000000007
#define MAX         414159
#define DEBUG       0

using namespace std;

int num[MAX + 1];
int cnt0[100000];
int cnt1[100000];

int main()
{
    string str_a, str_b;
    cin >> str_a;
    reverse(str_a.begin(), str_a.end());
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> str_b;
    reverse(str_b.begin(), str_b.end());

    int len_a = str_a.length();
    int len_b = str_b.length();

    for (int i = len_b + 314159 - 1, j = len_b - 1; i >= len_a && i >= len_b; i --, j --) {
        if (0 <= j) {
            num[i] = num[i + 1] + ('1' == str_b[j] ? 1 : 0);
        }
        else {
            num[i] = num[i + 1];
        }
    }

    for (size_t i = 0; i < len_a || i < len_b; i++) {
        if (0 == i) {
            if ('1' == str_b[i]) {
                cnt1[i] = 1;
            }
            else {
                cnt0[i] = 1;
            }
        }
        else {
            if (i < len_b) {
                if ('1' == str_b[i]) {
                    cnt1[i] = cnt1[i - 1] + 1;
                    cnt0[i] = cnt0[i - 1];
                }
                else {
                    cnt0[i] = cnt0[i - 1] + 1;
                    cnt1[i] = cnt1[i - 1];
                }
            }
            else {
                cnt0[i] = cnt0[i - 1];
                cnt1[i] = cnt1[i - 1];
            }
        }

        if (i < len_b) {
            if (i < len_a && '1' == str_a[i]) {
                num[i] = cnt0[i] + (314159 - i);
            }
            else {
                num[i] = cnt1[i];
            }
        }
        else {
            if ('1' == str_a[i]) {
                num[i] = cnt0[len_b - 1] + (314159 - len_b + 1);
            }
            else {
                num[i] = cnt1[i];
            }
        }
    }

    long long sum = 0;
    long long tmp = 1;

    for (size_t i = 0; i < len_b + 314159; i++) {
        sum += (long long)num[i] * tmp;
        sum %= MOD;

        tmp *= 2;
        tmp %= MOD;
    }

    cout << sum << '\n';

    return 0;
}
