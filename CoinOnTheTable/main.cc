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

char cell[52][52];
int cnt[1002][52][52];

int main(int argc, char const *argv[])
{
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0; i < n; i++)
    {
        cin >> cell[i];
    }

    for (int t = 0; t <= k; t++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cnt[t][i][j] = -1;
            }
        }
    }

    cnt[0][0][0] = 0;

    for (int t = 0; t < k; t++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (0 <= cnt[t][i][j])
                {
                    if ('U' == cell[i][j])
                    {
                        // 'U'
                        if (0 <= i - 1)
                        {
                            if (0 > cnt[t + 1][i - 1][j])
                            {
                                cnt[t + 1][i - 1][j] = cnt[t][i][j];
                            }
                            else if (cnt[t + 1][i - 1][j] > cnt[t][i][j])
                            {
                                cnt[t + 1][i - 1][j] = cnt[t][i][j];
                            }
                        }

                        // 'D'
                        if (n > i + 1)
                        {
                            if (0 > cnt[t + 1][i + 1][j])
                            {
                                cnt[t + 1][i + 1][j] = cnt[t][i][j] + 1;
                            }
                            else if (cnt[t + 1][i + 1][j] > cnt[t][i][j] + 1)
                            {
                                cnt[t + 1][i + 1][j] = cnt[t][i][j] + 1;
                            }
                        }

                        // 'L'
                        if (0 <= j - 1)
                        {
                            if (0 > cnt[t + 1][i][j - 1])
                            {
                                cnt[t + 1][i][j - 1] = cnt[t][i][j] + 1;
                            }
                            else if (cnt[t + 1][i][j - 1] > cnt[t][i][j] + 1)
                            {
                                cnt[t + 1][i][j - 1] = cnt[t][i][j] + 1;
                            }
                        }

                        // 'R'
                        if (m > j + 1)
                        {
                            if (0 > cnt[t + 1][i][j + 1])
                            {
                                cnt[t + 1][i][j + 1] = cnt[t][i][j] + 1;
                            }
                            else if (cnt[t + 1][i][j + 1] > cnt[t][i][j] + 1)
                            {
                                cnt[t + 1][i][j + 1] = cnt[t][i][j] + 1;
                            }
                        }
                    }
                    else if ('L' == cell[i][j])
                    {
                        // 'U'
                        if (0 <= i - 1)
                        {
                            if (0 > cnt[t + 1][i - 1][j])
                            {
                                cnt[t + 1][i - 1][j] = cnt[t][i][j] + 1;
                            }
                            else if (cnt[t + 1][i - 1][j] > cnt[t][i][j] + 1)
                            {
                                cnt[t + 1][i - 1][j] = cnt[t][i][j] + 1;
                            }
                        }

                        // 'D'
                        if (n > i + 1)
                        {
                            if (0 > cnt[t + 1][i + 1][j])
                            {
                                cnt[t + 1][i + 1][j] = cnt[t][i][j] + 1;
                            }
                            else if (cnt[t + 1][i + 1][j] > cnt[t][i][j] + 1)
                            {
                                cnt[t + 1][i + 1][j] = cnt[t][i][j] + 1;
                            }
                        }

                        // 'L'
                        if (0 <= j - 1)
                        {
                            if (0 > cnt[t + 1][i][j - 1])
                            {
                                cnt[t + 1][i][j - 1] = cnt[t][i][j];
                            }
                            else if (cnt[t + 1][i][j - 1] > cnt[t][i][j])
                            {
                                cnt[t + 1][i][j - 1] = cnt[t][i][j];
                            }
                        }

                        // 'R'
                        if (m > j + 1)
                        {
                            if (0 > cnt[t + 1][i][j + 1])
                            {
                                cnt[t + 1][i][j + 1] = cnt[t][i][j] + 1;
                            }
                            else if (cnt[t + 1][i][j + 1] > cnt[t][i][j] + 1)
                            {
                                cnt[t + 1][i][j + 1] = cnt[t][i][j] + 1;
                            }
                        }
                    }
                    else if ('D' == cell[i][j])
                    {
                        // 'U'
                        if (0 <= i - 1)
                        {
                            if (0 > cnt[t + 1][i - 1][j])
                            {
                                cnt[t + 1][i - 1][j] = cnt[t][i][j] + 1;
                            }
                            else if (cnt[t + 1][i - 1][j] > cnt[t][i][j] + 1)
                            {
                                cnt[t + 1][i - 1][j] = cnt[t][i][j] + 1;
                            }
                        }

                        // 'D'
                        if (n > i + 1)
                        {
                            if (0 > cnt[t + 1][i + 1][j])
                            {
                                cnt[t + 1][i + 1][j] = cnt[t][i][j];
                            }
                            else if (cnt[t + 1][i + 1][j] > cnt[t][i][j])
                            {
                                cnt[t + 1][i + 1][j] = cnt[t][i][j];
                            }
                        }

                        // 'L'
                        if (0 <= j - 1)
                        {
                            if (0 > cnt[t + 1][i][j - 1])
                            {
                                cnt[t + 1][i][j - 1] = cnt[t][i][j] + 1;
                            }
                            else if (cnt[t + 1][i][j - 1] > cnt[t][i][j] + 1)
                            {
                                cnt[t + 1][i][j - 1] = cnt[t][i][j] + 1;
                            }
                        }

                        // 'R'
                        if (m > j + 1)
                        {
                            if (0 > cnt[t + 1][i][j + 1])
                            {
                                cnt[t + 1][i][j + 1] = cnt[t][i][j] + 1;
                            }
                            else if (cnt[t + 1][i][j + 1] > cnt[t][i][j] + 1)
                            {
                                cnt[t + 1][i][j + 1] = cnt[t][i][j] + 1;
                            }
                        }
                    }
                    else if ('R' == cell[i][j])
                    {
                        // 'U'
                        if (0 <= i - 1)
                        {
                            if (0 > cnt[t + 1][i - 1][j])
                            {
                                cnt[t + 1][i - 1][j] = cnt[t][i][j] + 1;
                            }
                            else if (cnt[t + 1][i - 1][j] > cnt[t][i][j] + 1)
                            {
                                cnt[t + 1][i - 1][j] = cnt[t][i][j] + 1;
                            }
                        }

                        // 'D'
                        if (n > i + 1)
                        {
                            if (0 > cnt[t + 1][i + 1][j])
                            {
                                cnt[t + 1][i + 1][j] = cnt[t][i][j] + 1;
                            }
                            else if (cnt[t + 1][i + 1][j] > cnt[t][i][j] + 1)
                            {
                                cnt[t + 1][i + 1][j] = cnt[t][i][j] + 1;
                            }
                        }

                        // 'L'
                        if (0 <= j - 1)
                        {
                            if (0 > cnt[t + 1][i][j - 1])
                            {
                                cnt[t + 1][i][j - 1] = cnt[t][i][j] + 1;
                            }
                            else if (cnt[t + 1][i][j - 1] > cnt[t][i][j] + 1)
                            {
                                cnt[t + 1][i][j - 1] = cnt[t][i][j] + 1;
                            }
                        }

                        // 'R'
                        if (m > j + 1)
                        {
                            if (0 > cnt[t + 1][i][j + 1])
                            {
                                cnt[t + 1][i][j + 1] = cnt[t][i][j];
                            }
                            else if (cnt[t + 1][i][j + 1] > cnt[t][i][j])
                            {
                                cnt[t + 1][i][j + 1] = cnt[t][i][j];
                            }
                        }
                    }
                    else
                    {
                        // '*'
                        if (0 > cnt[t + 1][i][j])
                        {
                            cnt[t + 1][i][j] = cnt[t][i][j];
                        }
                        else if (cnt[t + 1][i][j] > cnt[t][i][j])
                        {
                            cnt[t + 1][i][j] = cnt[t][i][j];
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if ('*' == cell[i][j])
            {
                cout << cnt[k][i][j] << '\n';
                return 0;
            }
        }
    }

    return 0;
}
