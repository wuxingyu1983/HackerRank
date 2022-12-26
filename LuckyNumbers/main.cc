#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

#define DEBUG   0
#define MAX_MAG 18
#define MAX_SUM 162
#define MAX_SQ_SUM 1458

unsigned char primes[1460];
unsigned long long dp[19][164][1460];
unsigned long long ans[19][164][1460];
int sq_sum_start[19][164];
int sq_sum_end[19][164];

void init_primes()
{
    for (int i = 0; i <= MAX_SQ_SUM; i++)
    {
        primes[i] = 1;
    }
    primes[0] = primes[1] = 0;
    for (int i = 2; i * i <= MAX_SQ_SUM; i++)
    {
        if (primes[i] == 0)
            continue;
        for (int j = 2; j * i <= MAX_SQ_SUM; j++)
        {
            primes[i * j] = 0;
        }
    }
}

void init_dp()
{
    dp[0][0][0] = 1;
    for (int i = 0; i < MAX_MAG; i++)
    {
        for (int j = 0; j <= 9 * i; j++)
        {
            for (int k = 0; k <= 9 * 9 * i; k++)
            {
                for (int l = 0; l < 10; l++)
                {
                    dp[i + 1][j + l][k + l * l] += dp[i][j][k];
                }
            }
        }
    }

    for (int i = 0; i <= MAX_MAG; i++)
    {
        for (int j = 0; j <= MAX_SUM; j++)
        {
            for (int k = 0; k <= MAX_SQ_SUM; k++)
            {
                if (dp[i][j][k])
                {
                    sq_sum_start[i][j] = k;
                    break;
                }
            }
            for (int k = MAX_SQ_SUM; k >= 0; k--)
            {
                if (dp[i][j][k])
                {
                    sq_sum_end[i][j] = k;
                    break;
                }
            }
        }
    }
}

unsigned long long get_lucky(unsigned long long upper)
{
    unsigned long long result = 0;
    int len = 0;
    int bit_max[MAX_MAG];
    while (upper)
    {
        bit_max[len] = upper % 10;
        upper /= 10;
        len++;
    }
    // sum: sum of `upper` bits till `current bit`
    int sum = 0;
    // sq_sum: square sum of `upper` bits till `current bit`
    int sq_sum = 0;
    long long bit_result;
    long long bit_val_result;
    // most significant bit to least significant bit
    for (int i = len - 1; i >= 0; i--)
    {
        bit_result = 0;
        // bit result <- lucky count of {[0 ~ (current bit - 1)] 00...0 ~ 99...9}
        for (int l = 0; l < bit_max[i]; l++)
        {
            bit_val_result = 0;
            // x: sum of bits including current bits `l`
            // y: square sum of bits including current bits `l`
            int x = l + sum, y = l * l + sq_sum;

            if (ans[i][x][y])
            {
                // answer is cached
                bit_result += ans[i][x][y];
                continue;
            }
            
            // 00...0 ~ 99...9
            for (int j = 0; j <= i * 9; j++)
            {
                // j: sum of bits
                if (primes[j + x])
                {
                    for (int k = sq_sum_start[i][j]; k <= sq_sum_end[i][j]; k++)
                    {
                        if (primes[k + y])
                        {
                            bit_result += dp[i][j][k];
                            bit_val_result += dp[i][j][k];
                        }
                    }
                }
            }
            ans[i][x][y] = bit_val_result;
        }
        result += bit_result;
        sum += bit_max[i];
        sq_sum += bit_max[i] * bit_max[i];
    }

    // at last, `upper` itself
    if (primes[sum] && primes[sq_sum])
    {
        ++result;
    }
    return result;
}

int main()
{
    init_primes();
    init_dp();

#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    unsigned int t;
#if DEBUG
    inFile >> t;
#else
    cin >> t;
#endif

    for (size_t i = 0; i < t; i++)
    {
        unsigned long long a, b;
#if DEBUG
        inFile >> a >> b;
#else
        cin >> a >> b;
#endif

        cout << get_lucky(b) - get_lucky(a - 1) << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
