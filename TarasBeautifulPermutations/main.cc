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
#define MAX_N 2000

int a[MAX_N];
int sum[1001][MAX_N];

using namespace std;

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
    
    for (int query = 0; query < q; query++)
    {
        int n;
#if DEBUG
        inFile >> n;
#else
        cin >> n;
#endif
        
        for (int i = 0; i < n; i++)
        {
#if DEBUG
            inFile >> a[i];
#else
            cin >> a[i];
#endif
        }
        
        // sort
        sort(a, a + n);
       
        int p = 0;
        int max_pair = 0;
        int has_0 = 0;

        while (p < n)
        {
            if (p + 1 < n && a[p] == a[p + 1])
            {
                // 2 same num
                if (0 == p)
                {
                    sum[0][p + 1] = 0;
                    sum[1][p + 1] = 1;
                    max_pair = 1;
                    
                    has_0 = 0;
                }
                else
                {
                    for (int pair = 0; pair <= max_pair + 1; pair ++) {
                        sum[pair][p + 1] = 0;
                    }
                    
                    if (has_0)
                    {
                        long long tmp = (long long)sum[0][p - 1] * (long long)(p + 1) * (long long)p / 2;
                        tmp %= MOD;
                        sum[0][p + 1] += tmp;
                        sum[0][p + 1] %= MOD;
                        
                        tmp = (long long)sum[0][p - 1] * (long long)(p + 1);
                        tmp %= MOD;
                        sum[1][p + 1] += tmp;
                        sum[1][p + 1] %= MOD;
                    }
                    
                    for (long long pair = 1; pair <= max_pair; pair ++)
                    {
                        if (1 < pair)
                        {
                            long long tmp = (long long)sum[pair][p - 1] * pair * (pair - 1) / 2;
                            tmp %= MOD;
                            sum[pair - 2][p + 1] += tmp;
                            sum[pair - 2][p + 1] %= MOD;
                        }
                        
                        long long tmp = (long long)sum[pair][p - 1] * (long long)(p + 1 - pair) * pair;
                        tmp %= MOD;
                        sum[pair - 1][p + 1] += tmp;
                        sum[pair - 1][p + 1] %= MOD;
                        
                        if (1 == pair)
                        {
                            has_0 = 1;
                        }
                        
                        tmp = (long long)sum[pair][p - 1] * pair;
                        tmp %= MOD;
                        sum[pair][p + 1] += tmp;
                        sum[pair][p + 1] %= MOD;
                        
                        tmp = (long long)sum[pair][p - 1] * (long long)(p + 1 - pair) * (long long)(p - pair) / 2;
                        tmp %= MOD;
                        sum[pair][p + 1] += tmp;
                        sum[pair][p + 1] %= MOD;
                       
                        tmp = (long long)sum[pair][p - 1] * (long long)(p + 1 - pair);
                        tmp %= MOD;
                        sum[pair + 1][p + 1] += tmp;
                        sum[pair + 1][p + 1] %= MOD;
                        
                    }

                    max_pair ++;
                }
                
                p += 2;
            }
            else
            {
                if (0 == p)
                {
                    sum[0][p] = 1;
                    max_pair = 0;
                    
                    has_0 = 1;
                }
                else
                {
                    for (int pair = 0; pair <= max_pair; pair ++) {
                        sum[pair][p] = 0;
                    }
                    
                    if (has_0)
                    {
                        long long tmp = (long long)sum[0][p - 1] * (long long)(p + 1);
                        tmp %= MOD;
                        sum[0][p] += tmp;
                        sum[0][p] %= MOD;
                    }
                    
                    for (long long pair = 1; pair <= max_pair; pair ++)
                    {
                        long long tmp = (long long)sum[pair][p - 1] * pair;
                        tmp %= MOD;
                        sum[pair - 1][p] += tmp;
                        sum[pair - 1][p] %= MOD;
                        
                        if (1 == pair)
                        {
                            has_0 = 1;
                        }
                        
                        tmp = (long long)sum[pair][p - 1] * (long long)(p + 1 - pair);
                        tmp %= MOD;
                        sum[pair][p] += tmp;
                        sum[pair][p] %= MOD;
                    }
                }
                
                p += 1;
            }
        }
        
        cout << sum[0][n - 1] << "\n";
    }
    
    return 0;
}

