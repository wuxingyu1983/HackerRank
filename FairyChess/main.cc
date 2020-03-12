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

#define DEBUG   1
#define MOD     1000000007
#define MAX_M   200

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

    for (size_t i = 0; i < q; i++)
    {
        int n, m, s;
#if DEBUG
        inFile >> n >> m >> s;
#else
        cin >> n >> m >> s;
#endif

        // (2 * s + n) * (2 * s + n)
        vector< vector<char> > board(2 * s + n, vector<char>());
        vector< vector< vector<int> > > sum(2);
        vector< vector< vector< vector<int> > > > diagonal(2); // 0 - 45 degree, 1 - 135 degree

        sum[0].resize(2 * s + n);
        sum[1].resize(2 * s + n);

        diagonal[0].resize(2);
        diagonal[1].resize(2);

        diagonal[0][0].resize(2 * s + n);
        diagonal[0][1].resize(2 * s + n);
        diagonal[1][0].resize(2 * s + n);
        diagonal[1][1].resize(2 * s + n);

        for (size_t j = 0; j < 2 * s + n; j++)
        {
            board[j].resize(2 * s + n);

            sum[0][j].resize(2 * s + n);
            sum[1][j].resize(2 * s + n);

            diagonal[0][0][j].resize(2 * s + n);
            diagonal[0][1][j].resize(2 * s + n);
            diagonal[1][0][j].resize(2 * s + n);
            diagonal[1][1][j].resize(2 * s + n);
        }

        int index = 0;

        for (size_t row = s; row < s + n; row ++)
        {
            for (size_t col = s; col < s + n; col ++)
            {
                char c;
#if DEBUG
                inFile >> c;
#else
                cin >> c;
#endif

                board[col][row] = c;

                if ('L' == c)
                {
                    sum[index][col][row] = 1;
                }
            }
        }
        
        for (int row = 0; row < 2 * s + n; row ++)
        {
            for (int col = 0; col < 2 * s + n; col++)
            {
                // 更新 斜线
                if (0 <= col - 1 && 0 < row - 1)
                {
                    diagonal[index][0][col][row] = diagonal[index][0][col - 1][row - 1] + sum[index][col][row];
                }
                if (0 <= row - 1 && col + 1 < 2 * s + n)
                {
                    diagonal[index][1][col][row] = diagonal[index][1][col + 1][row - 1] + sum[index][col][row];
                }
            }
        }

        int ans = 0;

        int rhombus = -1;       // 菱形
        int rhombus_row = -1;   // row 第一个位置的 菱形

        for (size_t move = 1; move <= m; move++)
        {
            rhombus_row = -1;

            for (int row = 0; row < 2 * s + n; row ++)
            {
                for (int col = 0; col < 2 * s + n; col++)
                {
                    if (row >= s && row < s + n && col >= s && col < s + n)
                    {
                        if (col == s)
                        {
                            if (0 > rhombus_row)
                            {
                                rhombus = 0;

                                for (int y = row - s; y <= row + s; y++)
                                {
                                    for (int x = col - (s - abs(y - row)); x <= col + (s - abs(y - row)); x++)
                                    {
                                        rhombus += sum[index][x][y];
                                        rhombus %= MOD;
                                    }
                                }

                                rhombus_row = rhombus;
                            }
                            else
                            {
                                // 菱形向上
                                rhombus = 0;
                                rhombus += diagonal[index][1][col][row + s] - diagonal[index][1][col + s][row];
                                if (0 > rhombus)
                                {
                                    rhombus += MOD;
                                }
                                rhombus %= MOD;
                                rhombus += sum[index][col + s][row];
                                rhombus %= MOD;

                                rhombus -= diagonal[index][0][col + s][row - 1] - diagonal[index][0][col][row - s - 1];
                                if (0 > rhombus)
                                {
                                    rhombus += MOD;
                                }
                                rhombus %= MOD;
                                rhombus -= sum[index][col][row - s - 1];
                                if (0 > rhombus)
                                {
                                    rhombus += MOD;
                                }
                                rhombus %= MOD;

                                rhombus += rhombus_row;
                                rhombus %= MOD;
                                
                                rhombus_row = rhombus;
                            }
                        }
                        else
                        {
                            // 菱形向右
                            rhombus += diagonal[index][1][col][row + s] - diagonal[index][1][col + s][row];
                            if (0 > rhombus)
                            {
                                rhombus += MOD;
                            }
                            rhombus %= MOD;
                            rhombus += diagonal[index][0][col + s][row] - diagonal[index][0][col][row - s];
                            if (0 > rhombus)
                            {
                                rhombus += MOD;
                            }
                            rhombus %= MOD;
                            rhombus += sum[index][col][row - s];
                            rhombus %= MOD;

                            rhombus -= diagonal[index][0][col - 1][row + s] - diagonal[index][0][col - s - 1][row];
                            if (0 > rhombus)
                            {
                                rhombus += MOD;
                            }
                            rhombus %= MOD;
                            rhombus -= diagonal[index][1][col - s - 1][row] - diagonal[index][1][col - 1][row - s];
                            if (0 > rhombus)
                            {
                                rhombus += MOD;
                            }
                            rhombus %= MOD;
                            rhombus -= sum[index][col - 1][row - s];
                            if (0 > rhombus)
                            {
                                rhombus += MOD;
                            }
                            rhombus %= MOD;
                        }

                        if ('P' != board[col][row])
                        {
                            sum[1 - index][col][row] = rhombus;
                        }
                        else
                        {
                            sum[1 - index][col][row] = 0;
                        }

                        if (m == move)
                        {
                            ans += sum[1 - index][col][row];
                            ans %= MOD;
                        }
                    }

                    // 更新 斜线
                    if (0 <= col - 1 && 0 < row - 1)
                    {
                        diagonal[1 - index][0][col][row] = diagonal[1 - index][0][col - 1][row - 1] + sum[1 - index][col][row];
                        diagonal[1 - index][0][col][row] %= MOD;
                    }
                    if (0 <= row - 1 && col + 1 < 2 * s + n)
                    {
                        diagonal[1 - index][1][col][row] = diagonal[1 - index][1][col + 1][row - 1] + sum[1 - index][col][row];
                        diagonal[1 - index][1][col][row] %= MOD;
                    }
                }
            }

            index = 1 - index;
        }

        cout << ans << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}

