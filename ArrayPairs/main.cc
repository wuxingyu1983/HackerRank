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

long long cnt = 0;

class item
{
public:
    int val;
    int pos;

    item(int _val = 0, int _pos = 0)
    {
        val = _val;
        pos = _pos;
    }

    item(const item & v)
    {
        val = v.val;
        pos = v.pos;
    }
};

bool sort_func(const item &i, const item &j)
{
    if (i.val < j.val)
    {
        return true;
    }
    else if (i.val == j.val && i.pos < j.pos)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool find_func(const item &i, const item &j)
{
    return i.val < j.val;
}

void array_pair(vector<item> &vec, int first, int last, int maxpos)
{
    vector<item> half1;
    vector<item> half2;

    if (first < maxpos)
    {
        half1.assign(vec.begin() + first, vec.begin() + maxpos);
        sort(half1.begin(), half1.end(), sort_func);

        vector<item>::iterator above_1_low = lower_bound(half1.begin(), half1.end(), 2, find_func);

        int onecnt = above_1_low - half1.begin();
        cnt += onecnt;

        vector<item>::iterator max_low = lower_bound(half1.begin(), half1.end(), half1[half1.size() - 1].val, find_func);
        int max_middle = (max_low - half1.begin() + half1.size() - 1) / 2;

        array_pair(vec, first, maxpos - 1, half1[max_middle].pos);
    }

    if (maxpos < last)
    {
        // maxpos < last
        half2.assign(vec.begin() + maxpos + 1, vec.begin() + last + 1);
        sort(half2.begin(), half2.end(), sort_func);

        vector<item>::iterator above_1_low = lower_bound(half2.begin(), half2.end(), 2, find_func);

        int onecnt = above_1_low - half2.begin();
        cnt += onecnt;

        vector<item>::iterator max_low = lower_bound(half2.begin(), half2.end(), half2[half2.size() - 1].val, find_func);
        int max_middle = (max_low - half2.begin() + half2.size() - 1) / 2;

        array_pair(vec, maxpos + 1, last, half2[max_middle].pos);
    }

    if (0 < half1.size() && 0 < half2.size())
    {
        for (vector<item>::iterator it = half1.begin(); it != half1.end(); ++it)
        {
            vector<item>::iterator low = lower_bound(half2.begin(), half2.end(), vec[maxpos].val / (*it).val + 1, find_func);
            cnt += low - half2.begin();
        }
    }
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n;
#if DEBUG
    inFile >> n;
#else
    cin >> n;
#endif

    vector<item> vec(n);
    for (size_t i = 0; i < n; i++)
    {
        int tmp;
#if DEBUG
        inFile >> tmp;
#else
        cin >> tmp;
#endif

        vec[i] = item(tmp, i);
    }

    vector<item> sorted(vec.begin(), vec.end());

    sort(sorted.begin(), sorted.end(), sort_func);
    if (sorted[0].val == sorted[n - 1].val)
    {
        if (1 == sorted[0].val)
        {
            cnt = (long long)n * (long long)(n - 1) / 2;
        }
    }
    else
    {
        vector<item>::iterator max_low = lower_bound(sorted.begin(), sorted.end(), sorted[n - 1].val, find_func);
        int max_middle = (max_low - sorted.begin() + n - 1) / 2;
        array_pair(vec, 0, n - 1, sorted[max_middle].pos);
    }

    cout << cnt << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
