#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

#define MOD 1000000007

int main()
{
    string str;
    cin >> str;

    long long sum = 0;
    long long sub_sum = 0;

    for (int i = 0; i < str.length(); i++)
    {
        sub_sum = sub_sum * 10 + (i + 1) * (str[i] - '0');
        sub_sum %= MOD;

        sum += sub_sum;
        sum %= MOD;
    }

    cout << sum << endl;

    return 0;
}
