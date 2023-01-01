#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define DEBUG 0

class Element
{
public:
    unsigned int a;
    unsigned int w;

    unsigned int idx;

    Element() {idx = 0;}

};

unsigned long long update(vector<unsigned long long> &d, unsigned int idx, unsigned long long c, unsigned int s, unsigned int t, unsigned int p)
{
    // idx 为修改 index, c 为被修改的元素的变化量, [s, t] 为当前节点包含的区间, p
    // 为当前节点的编号
    if (idx == s && idx == t)
    {
        d[p] = c;
        return c;
    } // 当前区间为修改区间的子集时直接修改当前节点的值,然后打标记,结束修改
    int m = s + ((t - s) >> 1);
    if (idx <= m)
    {
        unsigned long long tmp = update(d, idx, c, s, m, p * 2);
        if (tmp > d[p])
        {
            d[p] = tmp;
        }
    }
    if (idx > m)
    {
        unsigned long long tmp = update(d, idx, c, m + 1, t, p * 2 + 1);
        if (tmp > d[p])
        {
            d[p] = tmp;
        }
    }

    return d[p];
}

unsigned long long getMax(vector<unsigned long long> &d, int l, int r, int s, int t, int p)
{
    if (l <= s && t <= r)
        return d[p];
    int m = s + ((t - s) >> 1);
    unsigned long long max = 0;
    if (l <= m)
    {
        max = getMax(d, l, r, s, m, p * 2);
    }
    if (r > m)
    {
        unsigned long long tmp = getMax(d, l, r, m + 1, t, p * 2 + 1);
        if (tmp > max)
        {
            max = tmp;
        }
    }
    return max;
}

int main()
{
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

    for (size_t i_t = 0; i_t < t; i_t ++)
    {
        unsigned int n;
#if DEBUG
        inFile >> n;
#else
        cin >> n;
#endif

        set<unsigned int> set_a;
        vector<Element> elems;
        for (size_t i_n = 0; i_n < n; i_n ++)
        {
            Element elem;

#if DEBUG
            inFile >> elem.a;
#else
            cin >> elem.a;
#endif

            elems.push_back(elem);

            set_a.insert(elem.a);
        }

        for (size_t i_n = 0; i_n < n; i_n ++)
        {
#if DEBUG
            inFile >> elems[i_n].w;
#else
            cin >> elems[i_n].w;
#endif
        }

        vector<unsigned int> vec_a;
        for (set<unsigned int>::iterator it = set_a.begin(); it != set_a.end(); it ++)
        {
            vec_a.push_back(*it);
        }

        for (size_t i_n = 0; i_n < n; i_n ++)
        {
            vector<unsigned int>::iterator it = lower_bound(vec_a.begin(), vec_a.end(), elems[i_n].a);
            elems[i_n].idx = it - vec_a.begin();
        }

        // init segment tree
        unsigned int size = ceil(log((double)n) / log(2.0));
        size = pow(2, size + 1);

        vector<unsigned long long> maxs(size + 1, 0);

        for (size_t i_n = 0; i_n < n; i_n ++)
        {
            if (0 == i_n)
            {
                update(maxs, elems[i_n].idx + 1, elems[i_n].w, 1, n + 1, 1);
            }
            else
            {
                unsigned long long left_max = getMax(maxs, 1, elems[i_n].idx, 1, n + 1, 1);
                update(maxs, elems[i_n].idx + 1, elems[i_n].w + left_max, 1, n + 1, 1);
            }
        }

        unsigned long long ans = getMax(maxs, 1, n + 1, 1, n + 1, 1);
        cout << ans << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
