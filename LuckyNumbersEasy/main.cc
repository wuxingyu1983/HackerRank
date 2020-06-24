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
#include <queue>
#include <stack>

using namespace std;

#define DEBUG   0

char flag[56];

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

    flag[0] = 1;
    flag[4] = 1;
    flag[7] = 1;

    for (size_t i = 8; i < 56; i++)
    {
        if (flag[i - 4] || flag[i - 7])
        {
            flag[i] = 1;
        }
    }

    for (size_t i = 0; i < q; i++)
    {
        long long n;
#if DEBUG
        inFile >> n;
#else
        cin >> n;
#endif

        int tmp = n % 56;
        
        if (flag[tmp])
        {
            cout << "Yes" << endl;
        }
        else
        {
            tmp += 28;
            if (tmp <= n && flag[tmp])
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
        }
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
