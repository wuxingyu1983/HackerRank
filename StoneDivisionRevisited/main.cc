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

#define DEBUG 1

bool myfunction(long long i, long long j)
{
    return (i > j);
}

long long division(vector<long long> &s, vector<long long> &subs, int idx, long long n, long long cnt)
{
    long long ret = 0;

    if (0 < subs[idx])
    {
        ret = (1 + subs[idx]) * cnt;
    }
    else
    {
        for (size_t i = idx; i < s.size(); i++)
        {
            if (s[i] < n)
            {
                if (0 == n % s[i])
                {
                    long long tmp = cnt;
                    tmp += division(s, subs, i, s[i], cnt * (n / s[i]));

                    if (tmp > ret)
                    {
                        ret = tmp;
                    }
                }
            }
        }

        subs[idx] = (ret - cnt) / cnt;
    }

    return ret;
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int q;
#if DEBUG
    inFile >> q;
#else
    cin >> q;
#endif

    for (size_t i_q = 0; i_q < q; i_q++)
    {
        long long n;
        int m;
#if DEBUG
        inFile >> n >> m;
#else
        cin >> n >> m;
#endif

        vector<long long> s(m);
        vector<long long> subs(m);

        for (size_t i_m = 0; i_m < m; i_m++)
        {
#if DEBUG
            inFile >> s[i_m];
#else
            cin >> s[i_m];
#endif
        }

        sort(s.begin(), s.end(), myfunction);

        long long ans = 0;

        for (size_t i = 0; i < s.size(); i++)
        {
            if (s[i] < n)
            {
                if (0 == n % s[i])
                {
                    long long tmp = 1;
                    tmp += division(s, subs, i, s[i], n / s[i]);

                    if (tmp > ans)
                    {
                        ans = tmp;
                    }
                }
            }
        }

        cout << ans << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}

