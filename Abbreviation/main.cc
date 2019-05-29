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

int cnt[1000];
int pos[1000][1000];

int main()
{
    int q;
    cin >> q;

    for (size_t i = 0; i < q; i++)
    {
        string a, b;
        cin >> a >> b;

        memset(cnt, 0, 1000 * sizeof(int));

        for (size_t j = 0; j < b.length(); j++)
        {
            char letter = b[j];

            if (0 == j)
            {
                for (size_t k = 0; k < a.length(); k++)
                {
                    if (a[k] == letter)
                    {
                        pos[j][cnt[j]++] = k;
                        break;
                    }
                    else if (letter - a[k] == 'A' - 'a')
                    {
                        pos[j][cnt[j]++] = k;
                    }
                    else if ('a' <= a[k] && 'z' >= a[k])
                    {
                        // can delete
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                if (0 == cnt[j - 1])
                {
                    break;
                }
                else
                {
                    for (size_t i_c = 0; i_c < cnt[j - 1]; i_c++)
                    {
                        int end = a.length() - 1;
                        if (i_c < cnt[j - 1] - 1)
                        {
                            end = pos[j - 1][i_c + 1];
                        }

                        for (size_t i_a = pos[j - 1][i_c] + 1; i_a <= end; i_a++)
                        {
                            if (a[i_a] == letter)
                            {
                                pos[j][cnt[j]++] = i_a;
                                break;
                            }
                            else if (letter - a[i_a] == 'A' - 'a')
                            {
                                pos[j][cnt[j]++] = i_a;
                            }
                            else if ('a' <= a[i_a] && 'z' >= a[i_a])
                            {
                                // can delete
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                }
            }
        }

        if (cnt[b.length() - 1])
        {
            bool yes = true;

            for (size_t i_a = pos[b.length() - 1][cnt[b.length() - 1] - 1] + 1; i_a < a.length(); i_a++)
            {
                if ('A' <= a[i_a] && 'Z' >= a[i_a])
                {
                    yes = false;
                    break;
                }
            }

            if (yes)
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
        else
        {
            cout << "NO" << endl;
        }
    }

    return 0;
}
