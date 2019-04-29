#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <set>
#include <iomanip>

using namespace std;

#define DEBUG 0

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

    vector<char> s;
    vector<long long> x;
    char temp;
    long templl;
    for (int i = 0; i < n; i++)
    {
#if DEBUG
        inFile >> temp >> templl;
#else
        cin >> temp >> templl;
#endif

        s.push_back(temp);
        x.push_back(templl);
    }

    multiset<long long> h1, h2;   // h1.size() == h2.size() or h1.size() = h2.size() + 1;
    long long h1_max, h2_min;
    
    for (size_t i = 0; i < n; i++)
    {
        if ('r' == s[i])
        {
            if (0 < h1.size() && x[i] <= h1_max)
            {
                multiset<long long>::iterator iter = h1.find(x[i]);
                if (iter == h1.end())
                {
                    // not found
                    cout << "Wrong!" << endl;
                    continue;
                }
                else
                {
                    h1.erase(iter);
                    if (0 < h1.size())
                    {
                        multiset<long long>::reverse_iterator riter = h1.rbegin();
                        h1_max = *riter;
                    }
                }
            }
            else if (0 < h2.size() && x[i] >= h1_max)
            {
                multiset<long long>::iterator iter = h2.find(x[i]);
                if (iter == h2.end())
                {
                    // not found
                    cout << "Wrong!" << endl;
                    continue;
                }
                else
                {
                    h2.erase(iter);
                    if (0 < h2.size())
                    {
                        multiset<long long>::iterator riter = h2.begin();
                        h2_min = *riter;
                    }
                }
            }
            else
            {
                cout << "Wrong!" << endl;
                continue;
            }
        }
        else
        {
            // add
            if (0 == h1.size() || x[i] <= h1_max)
            {
                h1.insert(x[i]);
                multiset<long long>::reverse_iterator riter = h1.rbegin();
                h1_max = *riter;
            }
            else
            {
                h2.insert(x[i]);
                multiset<long long>::iterator riter = h2.begin();
                h2_min = *riter;
            }
        }

        if (h1.size() == (h2.size() + 2))
        {
            multiset<long long>::reverse_iterator riter = h1.rbegin();
            h2_min = *riter;
            h1.erase((++riter).base());
            h2.insert(h2_min);

            riter = h1.rbegin();
            h1_max = *riter;
        }
        else if ((h1.size() + 1) == h2.size())
        {
            multiset<long long>::iterator iter = h2.begin();
            h1_max = *iter;
            h1.insert(h1_max);
            h2.erase(iter);

            iter = h2.begin();
            h2_min = *iter;
        }

        // output
        if (0 == h1.size())
        {
            cout << "Wrong!" << endl;
        }
        else if (h1.size() == h2.size())
        {
            if ((h1_max + h2_min) / 2 * 2 == (h1_max + h2_min))
            {
                cout << (h1_max + h2_min) / 2 << endl;
            }
            else
            {
                double middle = ((double)h1_max + (double)h2_min) / 2;
                cout << fixed << setprecision(1) << middle << endl; 
            }
        }
        else
        {
            cout << h1_max << endl;
        }
                
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
