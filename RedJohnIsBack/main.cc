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

int cnt[41];

int main()
{
    cnt[0] = 1;
    for (int i = 1; i <= 40; i++)
    {
        cnt[i] = cnt[i - 1];
        if (0 <= i - 4)
        {
            cnt[i] += cnt[i - 4];
        }
    }

    vector<unsigned char> flags(cnt[40] + 1, 0);
    flags[0] = 1;
    flags[1] = 1;
    for (size_t i = 2; i <= cnt[40]; i++)
    {
        if (0 == flags[i])
        {
            for (size_t j = 2 * i; j <= cnt[40]; j += i)
            {
                flags[j] = 1;
            }
        }
    }

    vector<int> primes;
    for (int i = 2; i <= cnt[40]; i++)
    {
        if (0 == flags[i])
        {
            primes.push_back(i);
        }
    }

    int t;
    cin >> t;

    for (size_t i = 0; i < t; i++)
    {
        int n;
        cin >> n;

        std::vector<int>::iterator low = lower_bound(primes.begin(), primes.end(), cnt[n]);
        if (cnt[n] == *low)
        {
            cout << low - primes.begin() + 1 << endl;
        }
        else
        {
            cout << low - primes.begin() << endl;
        }
    }

    return 0;
}
