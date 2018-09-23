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

using namespace std;

long long arr[5][100000];
long long smax[5][100000];

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int t;
 #if DEBUG
    inFile >> t;
#else
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
#endif

    for (int i = 0; i < t; i ++)
    {
        int n;
#if DEBUG
        inFile >> n;
#else
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
#endif

        for (int j = 0; j < n; j ++)
        {
#if DEBUG
            inFile >> arr[i][j];
#else
            cin >> arr[i][j];
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
#endif
        }

        long long sum = 0;
        for (int j = n - 1; j >= 0; j--)
        {
            sum += arr[i][j];
            if (n - 1 == j)
            {
                smax[i][j] = arr[i][j];
            }
            else if (n - 2 == j)
            {
                smax[i][j] = arr[i][j] + arr[i][j + 1];
            }
            else if (n - 3 == j)
            {
                smax[i][j] = arr[i][j] + arr[i][j + 1] + arr[i][j + 2];
            }
            else 
            {
                smax[i][j] = sum - smax[i][j + 1];

                if (smax[i][j] < sum - smax[i][j + 2])
                {
                    smax[i][j] = sum - smax[i][j + 2];
                }

                if (smax[i][j] < sum - smax[i][j + 3])
                {
                    smax[i][j] = sum - smax[i][j + 3];
                }
            }
        }

        cout << smax[i][0] << "\n";
    }

    return 0;
}