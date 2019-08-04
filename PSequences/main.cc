#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#define DEBUG 0
#define MOD 1000000007

using namespace std;

int main()
{
    int n, p;
    cin >> n;
    cin >> p;

    vector<int> divisor;
    vector<int> cnt;
    divisor.reserve(2 * 32000);
    cnt.reserve(2 * 32000);

    int last = p;
    int div = 1;
    while (true)
    {
        int tmp = p / (div + 1) + 1;
        if (tmp == last)
        {
            break;
        }
        else
        {
            divisor.push_back(div);
            cnt.push_back(last - tmp + 1);
            last = tmp - 1;
            div++;
        }
    }

    while (0 < last)
    {
        if (p / last == divisor.back())
        {
            cnt[cnt.size() - 1] += 1;
        }
        else
        {
            divisor.push_back(p / last);
            cnt.push_back(1);
        }
        last--;
    }

    reverse(divisor.begin(), divisor.end());
    reverse(cnt.begin(), cnt.end());

    long long sum[2][divisor.size()];
    int index = 0;
    ;

    for (size_t i = 0; i < divisor.size(); i++)
    {
        sum[index][i] = 1;
    }
    index = 1 - index;

    for (size_t i_n = 1; i_n < n; i_n++)
    {
        for (size_t i_d = 0; i_d < divisor.size(); i_d++)
        {
            if (0 == i_d)
            {
                sum[index][divisor.size() - 1 - i_d] = sum[1 - index][i_d] * cnt[i_d] % MOD;
            }
            else
            {
                sum[index][divisor.size() - 1 - i_d] = sum[index][divisor.size() - i_d] + sum[1 - index][i_d] * cnt[i_d] % MOD;
                sum[index][divisor.size() - 1 - i_d] %= MOD;
            }
        }

        index = 1 - index;
    }

    long long ret = 0;
    index = 1 - index;
    for (size_t i = 0; i < divisor.size(); i++)
    {
        ret += sum[index][i] * (long long)cnt[i] % MOD;
        ret %= MOD;
    }

    cout << ret << endl;

    return 0;
}
