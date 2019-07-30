#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <limits.h>

#define DEBUG       0
#define MAX_PB      1001

using namespace std;

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
#endif

    for (size_t i_t = 0; i_t < t; i_t++)
    {
        int n, m;
#if DEBUG
        inFile >> n >> m;
#else
        cin >> n >> m;
#endif

        int p[n][m];
        for (size_t i_n = 0; i_n < n; i_n++)
        {
            for (size_t i_m = 0; i_m < m; i_m++)
            {
#if DEBUG
                inFile >> p[i_n][i_m];
#else
                cin >> p[i_n][i_m];
#endif
            }
        }

        int b[n][MAX_PB];   // b[n][use to kill] = get bullet
        memset(b, 0, n * MAX_PB * sizeof(int));
        for (size_t i_n = 0; i_n < n; i_n++)
        {
            for (size_t i_m = 0; i_m < m; i_m++)
            {
                int bullet;
#if DEBUG
                inFile >> bullet;
#else
                cin >> bullet;
#endif

                if (bullet > b[i_n][p[i_n][i_m]])
                {
                    b[i_n][p[i_n][i_m]] = bullet;
                }
            }
        }

        int cnt[n][MAX_PB]; // cnt[n][bullet remain] = use to kill
        memset(cnt, 0, n * MAX_PB * sizeof(int));
        for (size_t i_n = 0; i_n < n; i_n++)
        {
            for (size_t i = 0; i < MAX_PB; i++)
            {
                // b[n][use to kill] = get bullet
                if (0 < b[i_n][i])
                {
                    if (0 == i_n)
                    {
                        if (0 == cnt[i_n][b[i_n][i]] || cnt[i_n][b[i_n][i]] > i)
                        {
                            cnt[i_n][b[i_n][i]] = i;
                        }
                    }
                    else
                    {
                        for (size_t j = 0; j < MAX_PB; j++)
                        {
                            // cnt[n][bullet remain] = use to kill
                            if (0 < cnt[i_n - 1][j])
                            {
                                if (j >= i)
                                {
                                    if (0 == cnt[i_n][b[i_n][i]] || cnt[i_n][b[i_n][i]] > cnt[i_n - 1][j])
                                    {
                                        cnt[i_n][b[i_n][i]] = cnt[i_n - 1][j];
                                    }
                                }
                                else
                                {
                                    if (0 == cnt[i_n][b[i_n][i]] || cnt[i_n][b[i_n][i]] > (cnt[i_n - 1][j] + i - j))
                                    {
                                        cnt[i_n][b[i_n][i]] = cnt[i_n - 1][j] + i - j;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        int min = 0;
        for (size_t i = 0; i < MAX_PB; i++)
        {
            if (cnt[n - 1][i])
            {
                if (0 == min || min > cnt[n - 1][i])
                {
                    min = cnt[n - 1][i];
                }
            }
        }

        cout << min << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
