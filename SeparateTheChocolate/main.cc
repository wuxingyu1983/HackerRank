#include <cmath>
#include <cstdio>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <limits.h>

#define DEBUG   0
#define MAX_MN  8
#define BITS    3

char c[MAX_MN][MAX_MN];
int flag[256][256];

using namespace std;

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    unsigned int m, n, k;
#if DEBUG
    inFile >> m >> n >> k;
#else
    cin >> m >> n >> k;
#endif

    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
#if DEBUG
            inFile >> c[i][j];
#else
            cin >> c[i][j];
#endif
        }
    }

    int pn = pow(2, n);

    for (size_t i = 0; i < pn; i++)
    {
        for (size_t j = 0; j < pn; j++)
        {
            flag[i][j] = -1;
        }
    }

    unsigned int ret = 0;
    map<unsigned int, unsigned int> cnt[2][pn][2 * m * n + 1]; // cnt[index][pn][difference]
    int index = 0;

    map<unsigned int, int> vtv[pn][pn];
    map<unsigned int, bool> canAdd[pn][pn];

    for (size_t i_m = 0; i_m < m; i_m++)
    {
        if (1 < i_m)
        {
            // clear all maps
            for (size_t i_pn = 0; i_pn < pn; i_pn++)
            {
                for (size_t difference = 0; difference < 2 * m * n + 1; difference++)
                {
                    cnt[index][i_pn][difference].clear();
                }
            }
        }

        for (size_t curr_pn = 0; curr_pn < pn; curr_pn++)
        {
            // i - new
            // 'D' - 0, 'T' - 1, 'U'
            bool nextI = false;
            for (size_t mask = 1, pos = 0; mask < pn; mask = mask << 1, pos++)
            {
                if ((curr_pn & mask) && 'D' == c[i_m][pos])
                {
                    nextI = true;
                    break;
                }

                if (0 == (curr_pn & mask) && 'T' == c[i_m][pos])
                {
                    nextI = true;
                    break;
                }
            }

            if (nextI)
            {
                continue;
            }

            if (0 == i_m)
            {
                unsigned int group = 0;
                unsigned int val = 0;
                int offset = 0;
                unsigned int difference = 0;
                set<unsigned int> new_group;
                for (size_t pos = 0, mask = 3; pos < n; pos++)
                {
                    if (curr_pn & (1 << pos))
                    {
                        offset++;
                    }
                    else
                    {
                        offset--;
                    }

                    if (0 == pos)
                    {
                        val = group;
                        new_group.insert(group);
                    }
                    else
                    {
                        if ((curr_pn & mask) == mask || 0 == (curr_pn & mask))
                        {
                            // 11 or 00
                            val |= group << (pos * BITS);
                        }
                        else
                        {
                            group++;
                            val |= group << (pos * BITS);
                            new_group.insert(group);
                        }

                        mask <<= 1;
                    }
                }

                difference = m * n + offset;

                if (0 == m - 1 && 2 < new_group.size())
                {
                }
                else
                {
                    if (0 == m - 1)
                    {
                        ret++;
                    }
                    else
                    {
                        cnt[index][curr_pn][difference].insert(pair<unsigned int, unsigned int>(val, 1));
                    }
                }
            }
            else
            {
                int offset = 0;
                for (size_t pos = 0; pos < n; pos++)
                {
                    if (curr_pn & (1 << pos))
                    {
                        offset++;
                    }
                    else
                    {
                        offset--;
                    }
                }

                for (size_t last_pn = 0; last_pn < pn; last_pn++)
                {
                    if (0 <= flag[last_pn][curr_pn])
                    {
                        if (0 == flag[last_pn][curr_pn])
                        {
                            continue;
                        }
                    }
                    else
                    {
                        bool nextJ = false;
                        // j for 1 - index
                        for (size_t pos = 1, mask = 3; pos < n; pos++, mask <<= 1)
                        {
                            if (0 == (curr_pn & mask) || mask == (curr_pn & mask))
                            {
                                if ((curr_pn & mask) == (last_pn & mask))
                                {
                                    // have 2x2 square
                                    nextJ = true;
                                    flag[last_pn][curr_pn] = 0;
                                    flag[curr_pn][last_pn] = 0;
                                    break;
                                }
                            }
                        }

                        if (nextJ)
                        {
                            continue;
                        }

                        flag[last_pn][curr_pn] = 1;
                        flag[curr_pn][last_pn] = 1;
                    }

                    for (size_t difference = 0; difference < 2 * m * n + 1; difference++)
                    {
                        if (0 < cnt[1 - index][last_pn][difference].size())
                        {
                            for (map<unsigned int, unsigned int>::iterator it = cnt[1 - index][last_pn][difference].begin(); it != cnt[1 - index][last_pn][difference].end(); it++)
                            {
                                unsigned int old_val = it->first;
                                unsigned int new_val = 0;

                                if (vtv[last_pn][curr_pn].find(old_val) == vtv[last_pn][curr_pn].end())
                                {
                                    unsigned char old_c[n];
                                    unsigned char new_c[n];
                                    char old_v[n];
                                    char new_v[n];
                                    set<unsigned int> old_group;
                                    set<unsigned int> toNext;
                                    set<unsigned int> new_group;
                                    unsigned int already_end = old_val >> (BITS * n);

                                    for (size_t pos = 0; pos < n; pos++)
                                    {
                                        if (curr_pn & (1 << pos))
                                        {
                                            new_c[pos] = 1;
                                        }
                                        else
                                        {
                                            new_c[pos] = 0;
                                        }

                                        if (last_pn & (1 << pos))
                                        {
                                            old_c[pos] = 1;
                                        }
                                        else
                                        {
                                            old_c[pos] = 0;
                                        }

                                        old_v[pos] = (old_val & (7 << (BITS * pos))) >> (BITS * pos);
                                        new_v[pos] = -1;

                                        old_group.insert(old_v[pos]);

                                        if (old_c[pos] == new_c[pos])
                                        {
                                            toNext.insert(old_v[pos]);
                                        }
                                    }

                                    for (size_t pos = 0; pos < n; pos++)
                                    {
                                        if (0 == pos)
                                        {
                                            if (old_c[pos] == new_c[pos])
                                            {
                                                new_v[pos] = old_v[pos];
                                                new_group.insert(new_v[pos]);
                                            }
                                        }
                                        else
                                        {
                                            if (new_c[pos] == new_c[pos - 1])
                                            {
                                                if (0 <= new_v[pos - 1])
                                                {
                                                    // 连续相同
                                                    if (new_c[pos] == old_c[pos])
                                                    {
                                                        if (old_v[pos] == new_v[pos - 1])
                                                        {
                                                            new_v[pos] = old_v[pos];
                                                        }
                                                        else
                                                        {
                                                            if (new_group.find(old_v[pos]) != new_group.end())
                                                            {
                                                                // old_v[pos] 已经存在
                                                                for (int p = pos + 1; p < n; p++)
                                                                {
                                                                    if (old_v[p] == new_v[pos - 1])
                                                                    {
                                                                        old_v[p] = old_v[pos];
                                                                    }
                                                                }

                                                                new_group.erase(new_v[pos - 1]);
                                                                new_v[pos] = old_v[pos];
                                                                for (int p = 0; p <= pos - 1; p++)
                                                                {
                                                                    if (new_v[p] == new_v[pos - 1])
                                                                    {
                                                                        new_v[p] = new_v[pos];
                                                                    }
                                                                }
                                                            }
                                                            else
                                                            {
                                                                new_v[pos] = new_v[pos - 1];
                                                                for (int p = pos + 1; p < n; p++)
                                                                {
                                                                    if (old_v[p] == old_v[pos])
                                                                    {
                                                                        old_v[p] = new_v[pos];
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                    else
                                                    {
                                                        new_v[pos] = new_v[pos - 1];
                                                    }
                                                }
                                                else
                                                {
                                                    if (old_c[pos] == new_c[pos])
                                                    {
                                                        new_v[pos] = old_v[pos];
                                                        new_group.insert(new_v[pos]);
                                                        for (int p = pos - 1; p >= 0; p--)
                                                        {
                                                            if (new_c[p] != new_c[pos])
                                                            {
                                                                break;
                                                            }
                                                            else
                                                            {
                                                                new_v[p] = new_v[pos];
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                if (old_c[pos] == new_c[pos])
                                                {
                                                    new_v[pos] = old_v[pos];
                                                    new_group.insert(new_v[pos]);
                                                }
                                            }
                                        }
                                    }

                                    for (unsigned int p = 0, v = 0; p < n; p++)
                                    {
                                        if (0 > new_v[p])
                                        {
                                            while (new_group.find(v) != new_group.end())
                                            {
                                                v++;
                                            }

                                            new_group.insert(v);

                                            // no use
                                            while (0 > new_v[p])
                                            {
                                                new_v[p] = v;
                                                p++;

                                                if (p >= n)
                                                {
                                                    break;
                                                }

                                                if (new_c[p] != new_c[p - 1])
                                                {
                                                    p--;
                                                    break;
                                                }
                                            }
                                        }
                                    }

                                    already_end += old_group.size() - toNext.size();

                                    if (1 < already_end)
                                    {
                                        vtv[last_pn][curr_pn].insert(pair<unsigned int, int>(old_val, -1));
                                        continue;
                                    }
                                    else if (1 == already_end)
                                    {
                                        if (1 < new_group.size())
                                        {
                                            vtv[last_pn][curr_pn].insert(pair<unsigned int, int>(old_val, -1));
                                            continue;
                                        }
                                    }

                                    if (2 >= new_group.size() + already_end)
                                    {
                                        canAdd[last_pn][curr_pn].insert(pair<unsigned int, bool>(old_val, true));
                                    }

                                    if (i_m == m - 1)
                                    {
                                        if (2 < new_group.size() + already_end)
                                        {
                                        }
                                        else
                                        {
                                            if (m * n - k <= difference + offset && m * n + k >= difference + offset)
                                            {
                                                ret += it->second;
                                            }
                                        }
                                        continue;
                                    }

                                    char v = 0;
                                    char fv[n];
                                    for (size_t pos = 0; pos < n; pos++)
                                    {
                                        if (0 <= new_v[pos])
                                        {
                                            for (size_t p = pos + 1; p < n; p++)
                                            {
                                                if (new_v[p] == new_v[pos])
                                                {
                                                    fv[p] = v;
                                                    new_v[p] = -1;
                                                }
                                            }

                                            fv[pos] = v;
                                            new_v[pos] = -1;

                                            v++;
                                        }
                                    }

                                    for (size_t p = 0; p < n; p++)
                                    {
                                        new_val |= fv[p] << (BITS * p);
                                    }

                                    new_val |= already_end << (BITS * n);

                                    vtv[last_pn][curr_pn].insert(pair<unsigned int, int>(old_val, new_val));
                                }
                                else
                                {
                                    if (0 > vtv[last_pn][curr_pn].find(old_val)->second)
                                    {
                                        continue;
                                    }
                                    else
                                    {
                                        if (i_m == m - 1)
                                        {
                                            if (canAdd[last_pn][curr_pn].find(old_val) != canAdd[last_pn][curr_pn].end())
                                            {
                                                if (m * n - k <= difference + offset && m * n + k >= difference + offset)
                                                {
                                                    ret += it->second;
                                                }
                                            }
                                            continue;
                                        }
                                        else
                                        {
                                            new_val = vtv[last_pn][curr_pn].find(old_val)->second;
                                        }
                                    }
                                }

                                if (!cnt[index][curr_pn][difference + offset][new_val])
                                {
                                    cnt[index][curr_pn][difference + offset][new_val] = it->second;
                                }
                                else
                                {
                                    cnt[index][curr_pn][difference + offset][new_val] += it->second;
                                }
                            }
                        }
                    }
                }
            }
        }

        index = 1 - index;
    }

    cout << ret << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
