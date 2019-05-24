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
    int n, k, x;
    cin >> n >> k >> x;

    long long count = 0;

    long long ones = 0;
    long long others = 0;

    // pos : 1;
    ones = 1;

    // pos : 2
    ones = 0;
    others = 1;

    for (size_t i = 3; i < n; i++)
    {
        long long tmp = (long long)(k - 1) * others;

        others = ones + (long long)(k - 2) * others;
        others %=MOD;

        ones = tmp % MOD;
    }

    if (1 == x)
    {
        count = (long long)(k - 1) * others;
    }
    else
    {
        count = ones + (long long)(k - 2) * others;
    }
    count %= MOD;

    cout << count << endl;

    return 0;
}
