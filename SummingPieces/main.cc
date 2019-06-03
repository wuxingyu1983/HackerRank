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

#define DEBUG   0
#define MOD     1000000007

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif
    
    int n;
#if DEBUG
    inFile >> n;
#else
    cin >> n;
#endif
    
    long long sum;
    long long half1 = 0;
    long long half2 = 0;
    long long cnt1 = 0;
    long long cnt2 = 0;
    long long cnt = 0;
    
    for (size_t i = 0; i < n; i++)
    {
        int a;
#if DEBUG
        inFile >> a;
#else
        cin >> a;
#endif
        
        if (0 == i)
        {
            sum = a;
        }
        else if (1 == i)
        {
            half1 = a + (sum + a);
            sum = sum + a + (sum + a) * 2;
            cnt = 2;
            cnt1 = 2;
            half2 = 5;
            cnt2 = 2;
        }
        else
        {
            long long tmp = sum + half1 + (half2 * a % MOD);
            tmp %= MOD;
            sum += (cnt * a % MOD) + tmp;
            
            half1 += cnt1 * a % MOD + cnt * a % MOD;
            half1 %= MOD;
            
            cnt1 += cnt;
            cnt1 %= MOD;
            
            half2 += cnt2 + cnt * 2;
            half2 %= MOD;
            
            cnt2 += cnt;
            cnt2 %= MOD;
            
            cnt *= 2;
            cnt %= MOD;
        }
        
        sum %= MOD;
    }
    
    cout << sum << endl;
    
#if DEBUG
    inFile.close();
#endif
    
    return 0;
}
