/*
    Convex hull trick
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <deque>
#include <map>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <limits.h>

#define DEBUG 0

using namespace std;

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    unsigned long long n, h;
#if DEBUG
    inFile >> n >> h;
#else
    cin >> n >> h;
#endif

    vector<unsigned long long> x(n);
    for (size_t i = 0; i < n; i++)
    {
#if DEBUG
        inFile >> x[i];
#else
        cin >> x[i];
#endif
    }

    if (0 == n || 0 == h)
    {
        cout << 0 << endl;
    }
    else
    {
        deque<int> deq;
        vector<unsigned long long> cost(n);
        vector<unsigned long long> y(n);
        deque<double> slope;

        slope.push_back(0);
        deq.push_back(0);
        cost[0] = h;
        y[0] = x[0] * x[0];

        for (size_t i = 1; i < n; i++)
        {
            cost[i] = cost[i - 1] + h;
            if (1 == i)
            {
                deq.push_back(i);
                if (h + (x[i] - x[i - 1]) * (x[i] - x[i - 1]) < cost[i])
                {
                    cost[i] = h + (x[i] - x[i - 1]) * (x[i] - x[i - 1]);
                }
                y[i] = cost[i - 1] + x[i] * x[i];
                slope.push_back((double)(y[i] - y[i - 1]) / (double)(x[i] - x[i - 1]));
            }
            else
            {
                int index = 0;
                if (y[deq[1]] - y[deq[0]] >= 2 * x[i] * (x[deq[1]] - x[deq[0]]))
                {
                    index = deq[0];
                }
                else if (y[deq[deq.size() - 1]] - y[deq[deq.size() - 2]] <= 2 * x[i] * (x[deq[deq.size() - 1]] - x[deq[deq.size() - 2]]))
                {
                    index = deq[deq.size() - 1];
                }
                else
                {
                    deque<double>::iterator it = lower_bound(slope.begin(), slope.end(), 2 * x[i]);
                    index = deq[it - slope.begin() - 1];
                }

                unsigned long long tmp = h + (x[i] - x[index]) * (x[i] - x[index]);
                if (0 < index)
                {
                    tmp += cost[index - 1];
                }

                if (tmp < cost[i])
                {
                    cost[i] = tmp;
                }

                y[i] = cost[i - 1] + x[i] * x[i];

                while (true)
                {
                    int last_index = deq[deq.size() - 1];
                    int pre_last_index = deq[deq.size() - 2];
                    if ((y[i] - y[last_index]) * (x[last_index] - x[pre_last_index]) <= (y[last_index] - y[pre_last_index]) * (x[i] - x[last_index]))
                    {
                        deq.pop_back();
                        slope.pop_back();
                        if (1 == deq.size())
                        {
                            deq.push_back(i);
                            slope.push_back((double)(y[i] - y[pre_last_index]) / (double)(x[i] - x[pre_last_index]));
                            break;
                        }
                    }
                    else
                    {
                        deq.push_back(i);
                        slope.push_back((double)(y[i] - y[last_index]) / (double)(x[i] - x[last_index]));
                        break;
                    }
                }
            }
        }

        cout << cost[n - 1] << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
