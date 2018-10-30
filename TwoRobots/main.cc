//
//  main.cpp
//  test
//
//  Created by wuxingyu on 2018/10/31.
//  Copyright © 2018 wuxingyu. All rights reserved.
//

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

int d[2][1001][1001];

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
    
    for (int i_t = 0; i_t < t; i_t++)
    {
        int m, n;
#if DEBUG
        inFile >> m >> n;
#else
        cin >> m >> n;
#endif

        memset(d, 0, sizeof(int) * 2 * (m + 1) * (m + 1));

        int index = 0;

        for (int i_n = 0; i_n < n; i_n ++)
        {
            int ma, mb;
#if DEBUG
            inFile >> ma >> mb;
#else
            cin >> ma >> mb;
#endif

            if (0 == i_n)
            {
                d[index][0][mb] = abs(ma - mb);
            }
            else
            {
                for (int b = 0; b <= m; b ++)
                {
                    for (int a = 0; a <= b; a ++)
                    {
                        d[index][a][b] = 0;
                    }
                }

                for (int b = 0; b <= m; b++)
                {
                    for (int a = 0; a <= b; a++)
                    {
                        if (d[1 - index][a][b])
                        {
                            // b => ma => mb
                            int tmp = d[1 - index][a][b] + abs(ma - mb) + abs(b - ma);

                            if (a <= mb)
                            {
                                if (0 == d[index][a][mb] || d[index][a][mb] > tmp)
                                {
                                    d[index][a][mb] = tmp;
                                }
                            }
                            else
                            {
                                if (0 == d[index][mb][a] || d[index][mb][a] > tmp)
                                {
                                    d[index][mb][a] = tmp;
                                }
                            }

                            // a => ma => mb
                            if (0 == a)
                            {
                                tmp = d[1 - index][a][b] + abs(ma - mb);
                            }
                            else
                            {
                                tmp = d[1 - index][a][b] + abs(ma - mb) + abs(a - ma);
                            }

                            if (b <= mb)
                            {
                                if (0 == d[index][b][mb] || d[index][b][mb] > tmp)
                                {
                                    d[index][b][mb] = tmp;
                                }
                            }
                            else
                            {
                                if (0 == d[index][mb][b] || d[index][mb][b] > tmp)
                                {
                                    d[index][mb][b] = tmp;
                                }
                            }
                        }
                    }
                }
            }

            if (i_n == n - 1)
            {
                int ret = 0;

                for (int b = 0; b <= m; b++)
                {
                    for (int a = 0; a <= b; a++)
                    {
                        if (d[index][a][b])
                        {
                            if (0 == ret || ret > d[index][a][b])
                            {
                                ret = d[index][a][b];
                            }
                        }
                    }
                }

                cout << ret << "\n";
            }
            else
            {
                index = 1 - index;
            }
        }
    }

    return 0;
}
