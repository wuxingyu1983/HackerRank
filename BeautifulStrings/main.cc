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

    string str;
#if DEBUG
    inFile >> str;
#else
    cin >> str;
#endif

    vector<int> cnt;
    int dup = 0;
    int tmp = 1;
    for (size_t i = 1; i < str.length(); i++)
    {
        if (str[i] == str[i - 1])
        {
            tmp++;
            if (i == str.length() - 1)
            {
                cnt.push_back(tmp);
                dup += tmp;
            }
        }
        else
        {
            if (1 < tmp)
            {
                cnt.push_back(tmp);
                dup += tmp;
            }

            tmp = 1;
        }
    }

    long long ret = 0;

    long long non_dup = str.length() - dup;

    if (non_dup) {
        // 2个全从未重复中选取
        ret += non_dup * (non_dup - 1) / 2;

        // 1个从未重复、1个从重复中选取
        if (0 < cnt.size())
        {
            ret += (long long)cnt.size() * non_dup;
        }
    }

    // 2个从重复中选取
    if (0 < cnt.size())
    {
        for (vector<int>::iterator it = cnt.begin(); it != cnt.end(); it++)
        {
            ret += 1;
            ret += it - cnt.begin();
        }
    }

    for (size_t i = 0; i < str.length() - 2; i++)
    {
        if (str[i] == str[i + 2] && str[i] != str[i + 1])
        {
            ret --;
        }
    }

    cout << ret << endl; 

#if DEBUG
    inFile.close();
#endif

    return 0;
}
