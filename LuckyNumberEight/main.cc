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
#define MOD     1000000007

int sum[2][8];
int r[8] = {0, 2, 4, 6, 0, 2, 4, 6};

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

    string num;
#if DEBUG
    inFile >> num;
#else
    cin >> num;
#endif     

    int curr = 0;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            sum[curr][j] = sum[1 - curr][j];     
        }

        int c = (num[i] - '0') % 8;

        for (size_t j = 0; j < 8; j++)
        {
            int new_idx = (r[j] + c) % 8;

            sum[curr][new_idx] += sum[1 - curr][j];
            sum[curr][new_idx] %= MOD;
        }

        sum[curr][c] += 1;
        sum[curr][c] %= MOD;

        curr = 1 - curr;
    }

    cout << sum[1 - curr][0] << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
