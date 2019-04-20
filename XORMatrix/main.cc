#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

#define DEBUG   0

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    long long n, m;
#if DEBUG
    inFile >> n >> m;
#else
    cin >> n >> m;
#endif

    vector<int> a[2];
    a[0].resize(n);
    a[1].resize(n);
    int index = 0;

    for (size_t i = 0; i < n; i++)
    {
#if DEBUG
        inFile >> a[index][i];
#else
        cin >> a[index][i];
#endif
    }

    if (1 < m)
    {
        for (int bits = 60; bits >= 0; bits--)
        {
            long long tmp = 1;
            tmp <<= bits;

            if ((m - 1) & tmp)
            {
                index = 1 - index;

                for (long long i = 0; i < n; i++)
                {
                    a[index][i] = a[1 - index][i] ^ a[1 - index][(i + tmp) % n];
                }
            }
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        if (i)
        {
            cout << " ";
        }

        cout << a[index][i];
    }

    cout << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
