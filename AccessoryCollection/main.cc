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

    for (int i = 0; i < t; i++)
    {
        int l, a, n, d;
#if DEBUG
        inFile >> l >> a >> n >> d;
#else
        cin >> l >> a >> n >> d;
#endif

        if (a < d)
        {
            cout << "SAD"
                 << "\n";
        }
        else
        {
            long long max = 0;

            if (1 == d)
            {
                cout << (long long)l * (long long)a << "\n";
            }
            else if (2 == d)
            {
                int step = n - 1;
                int c = l / step;

                if (l == c * step)
                {
                    if (c > a)
                    {
                        cout << "SAD"
                             << "\n";
                    }
                    else
                    {
                        // c <= a
                        max = (long long)step * (long long)(2 * a - c + 1) * (long long)c / 2;
                        cout << max << "\n";
                    }
                }
                else
                {
                    if (c + 1 > a)
                    {
                        cout << "SAD"
                             << "\n";
                    }
                    else
                    {
                        // c+ 1 <= a
                        max = (long long)step * (long long)(2 * a - c + 1) * (long long)c / 2;
                        max += (long long)(l - c * step) * (long long)(a - c);
                        cout << max << "\n";
                    }
                }
            }
            else
            {
                for(int j = n / d; j <= n - d + 1; j++)
                {
                    int step = (n - j - 1) / (d - 1 - 1);

                    if (step > j)
                    {
                        continue;
                    }
                    else
                    {
                        long long tmp = (long long)j * (long long)a;
                        int c = (l - j) / step;
                        if (l - j == c * step)
                        {
                            if (c + 1 > a)
                            {
                            }
                            else
                            {
                                tmp += (long long)step * (long long)(2 * a - 1 - c) * (long long)c / 2;
                                if (0 == max || tmp > max)
                                {
                                    max = tmp;
                                }
                            }
                        }
                        else
                        {
                            if (c + 1 + 1 > a)
                            {
                            }
                            else
                            {
                                tmp += (long long)step * (long long)(2 * a - 1 - c) * (long long)c / 2;
                                tmp += (long long)(l - j - c * step) * (long long)(a - c - 1);
                                if (0 == max || tmp > max)
                                {
                                    max = tmp;
                                }
                            }
                        }
                    }
                    
                }
                
                if (0 == max)
                {
                    cout << "SAD"
                         << "\n";
                }
                else
                {
                    cout << max << "\n";
                }
            }
        }
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
