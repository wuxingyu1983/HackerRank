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

#define DEBUG 0
#define MAX_N 51

int cell[MAX_N][MAX_N][MAX_N];
int cube[MAX_N][MAX_N][MAX_N][MAX_N];  // cube[len][x][y][z]
int dir_x[MAX_N][MAX_N][MAX_N][MAX_N]; // dir_x[len][x][y][z]
int dir_y[MAX_N][MAX_N][MAX_N][MAX_N]; // dir_y[len][x][y][z]
int dir_z[MAX_N][MAX_N][MAX_N][MAX_N]; // dir_z[len][x][y][z]

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

    for (size_t i_q = 0; i_q < q; i_q++)
    {
        int n;
#if DEBUG
        inFile >> n;
#else
        cin >> n;
#endif

        vector<int> a;
        int cnt = n * n * n;

        for (size_t i = 0; i < cnt; i++)
        {
            int tmp;
#if DEBUG
            inFile >> tmp;
#else
            cin >> tmp;
#endif
            a.push_back(tmp);
        }

        memset(cell, 0, sizeof(int) * MAX_N * MAX_N * MAX_N);

        for (size_t x = 1; x <= n; x++)
        {
            for (size_t y = 1; y <= n; y++)
            {
                for (size_t z = 1; z <= n; z++)
                {
                    int idx = (x - 1) * n * n + (y - 1) * n + z - 1;
                    cell[x][y][z] = a[idx];
                }
            }
        }

        memset(cube, 0, sizeof(int) * MAX_N * MAX_N * MAX_N * MAX_N);
        memset(dir_x, 0, sizeof(int) * MAX_N * MAX_N * MAX_N * MAX_N);
        memset(dir_y, 0, sizeof(int) * MAX_N * MAX_N * MAX_N * MAX_N);
        memset(dir_z, 0, sizeof(int) * MAX_N * MAX_N * MAX_N * MAX_N);

        for (size_t i = 1; i <= n; i++)
        {
            int cnt = 0;
            if (1 == i)
            {
                for (size_t x = 1; x <= n; x++)
                {
                    for (size_t y = 1; y <= n; y++)
                    {
                        for (size_t z = 1; z <= n; z++)
                        {
                            dir_x[i][x][y][z] = cell[x][y][z];
                            dir_y[i][x][y][z] = cell[x][y][z];
                            dir_z[i][x][y][z] = cell[x][y][z];
                            cube[i][x][y][z] = cell[x][y][z];

                            if (i == cube[i][x][y][z])
                            {
                                cnt++;
                            }
                        }
                    }
                }

                cout << cnt;
            }
            else
            {
                for (size_t x = 1; x <= n; x++)
                {
                    for (size_t y = 1; y <= n; y++)
                    {
                        for (size_t z = 1; z <= n; z++)
                        {
                            if (x + i - 1 <= n)
                            {
                                if (cell[x + i - 1][y][z] > dir_x[i - 1][x][y][z])
                                {
                                    dir_x[i][x][y][z] = cell[x + i - 1][y][z];
                                }
                                else
                                {
                                    dir_x[i][x][y][z] = dir_x[i - 1][x][y][z];
                                }
                            }

                            if (y + i - 1 <= n)
                            {
                                if (cell[x][y + i - 1][z] > dir_y[i - 1][x][y][z])
                                {
                                    dir_y[i][x][y][z] = cell[x][y + i - 1][z];
                                }
                                else
                                {
                                    dir_y[i][x][y][z] = dir_y[i - 1][x][y][z];
                                }
                            }

                            if (z + i - 1 <= n)
                            {
                                if (cell[x][y][z + i - 1] > dir_z[i - 1][x][y][z])
                                {
                                    dir_z[i][x][y][z] = cell[x][y][z + i - 1];
                                }
                                else
                                {
                                    dir_z[i][x][y][z] = dir_z[i - 1][x][y][z];
                                }
                            }
                        }
                    }
                }

                for (size_t x = 1; x <= n + 1 - i; x++)
                {
                    for (size_t y = 1; y <= n + 1 - i; y++)
                    {
                        for (size_t z = 1; z <= n + 1 - i; z++)
                        {
                            int max = cube[i - 1][x][y][z];

                            for (size_t j = 0; j < i; j++)
                            {
                                if (max < dir_y[i][x + i - 1][y][z + j])
                                {
                                    max = dir_y[i][x + i - 1][y][z + j];
                                }
                            }

                            for (size_t j = 0; j < i; j++)
                            {
                                if (max < dir_z[i][x + j][y + i - 1][z])
                                {
                                    max = dir_z[i][x + j][y + i - 1][z];
                                }
                            }

                            for (size_t j = 0; j < i; j++)
                            {
                                if (max < dir_x[i][x][y + j][z + i - 1])
                                {
                                    max = dir_x[i][x][y + j][z + i - 1];
                                }
                            }

                            cube[i][x][y][z] = max;

                            if (i == max)
                            {
                                cnt++;
                            }
                        }
                    }
                }

                cout << " " << cnt;
            }
        }

        cout << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
