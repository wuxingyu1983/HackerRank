#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <limits.h>

#define DEBUG       0
#define MAX_A       1000000000

using namespace std;

class Segment
{
public:
    int start, end;
    int cnt;

    Segment(int _start = 0, int _end = 0, int _cnt = 0)
    {
        start = _start;
        end = _end;
        cnt = _cnt;
    }

    Segment(const Segment & v)
    {
        start = v.start;
        end = v.end;
        cnt = v.cnt;
    }
};

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

    vector<Segment> segs[2];
    segs[0].reserve(2 * n);
    segs[1].reserve(2 * n);

    int index = 0;

    vector<int> a(n);
    for (size_t i_n = 0; i_n < n; i_n++)
    {
#if DEBUG
        inFile >> a[i_n];
#else
        cin >> a[i_n];
#endif

        segs[index].clear();
        int min_curr = i_n + 1;     // 当前轮最小的可能值
        if (0 == i_n)
        {
            if (min_curr < a[i_n])
            {
                segs[index].push_back(Segment(min_curr, a[i_n] - 1, 1));
            }

            segs[index].push_back(Segment(a[i_n], a[i_n], 0));

            segs[index].push_back(Segment(a[i_n] + 1, INT_MAX, 1));
        }
        else
        {
            if (min_curr > a[i_n])
            {
                int min_tmp = INT_MAX;
                for (vector<Segment>::iterator it = segs[1 - index].begin(); it != segs[1 - index].end(); it++)
                {
                    if (0 == segs[index].size())
                    {
                        min_tmp = (*it).cnt;
                        if (INT_MAX == (*it).end)
                        {
                            segs[index].push_back(Segment((*it).start + 1, INT_MAX, min_tmp + 1));
                        }
                        else
                        {
                            segs[index].push_back(Segment((*it).start + 1, (*it).end + 1, min_tmp + 1));
                        }
                    }
                    else
                    {
                        if (min_tmp > (*it).cnt)
                        {
                            min_tmp = (*it).cnt;
                        }
                        
                        if (min_tmp + 1 == segs[index].back().cnt)
                        {
                            // merge
                            if (INT_MAX == (*it).end)
                            {
                                segs[index][segs[index].size() - 1].end = INT_MAX;
                            }
                            else
                            {
                                segs[index][segs[index].size() - 1].end = (*it).end + 1;
                            }
                        }
                        else
                        {
                            if (INT_MAX == (*it).end)
                            {
                                segs[index].push_back(Segment((*it).start + 1, INT_MAX, min_tmp + 1));
                            }
                            else
                            {
                                segs[index].push_back(Segment((*it).start + 1, (*it).end + 1, min_tmp + 1));
                            }
                        }
                    }
                }
            }
            else
            {
                // min_curr <= a[i_n]
                int min_tmp = INT_MAX;
                for (vector<Segment>::iterator it = segs[1 - index].begin(); it != segs[1 - index].end(); it++)
                {
                    if ((*it).start <= a[i_n] - 1 && (*it).end >= a[i_n] - 1)
                    {
                        // split
                        if (0 == segs[index].size())
                        {
                            min_tmp = (*it).cnt;
                            if ((*it).start + 1 < a[i_n])
                            {
                                segs[index].push_back(Segment((*it).start + 1, a[i_n] - 1, min_tmp + 1));
                            }

                            segs[index].push_back(Segment(a[i_n], a[i_n], min_tmp));

                            if ((*it).end > a[i_n] - 1)
                            {
                                if (INT_MAX == (*it).end)
                                {
                                    segs[index].push_back(Segment(a[i_n] + 1, INT_MAX, min_tmp + 1));
                                }
                                else
                                {
                                    segs[index].push_back(Segment(a[i_n] + 1, (*it).end + 1, min_tmp + 1));
                                }
                            }
                        }
                        else
                        {
                            if (min_tmp > (*it).cnt)
                            {
                                min_tmp = (*it).cnt;
                            }

                            if ((*it).start + 1 < a[i_n])
                            {
                                if (min_tmp + 1 == segs[index].back().cnt)
                                {
                                    // merge
                                    segs[index][segs[index].size() - 1].end = a[i_n] - 1;
                                }
                                else
                                {
                                    segs[index].push_back(Segment((*it).start + 1, a[i_n] - 1, min_tmp + 1));
                                }
                            }

                            if (min_tmp == segs[index].back().cnt)
                            {
                                // merge
                                segs[index][segs[index].size() - 1].end = a[i_n];
                            }
                            else
                            {
                                segs[index].push_back(Segment(a[i_n], a[i_n], min_tmp));
                            }

                            if ((*it).end > a[i_n] - 1)
                            {
                                if (INT_MAX == (*it).end)
                                {
                                    segs[index].push_back(Segment(a[i_n] + 1, INT_MAX, min_tmp + 1));
                                }
                                else
                                {
                                    segs[index].push_back(Segment(a[i_n] + 1, (*it).end + 1, min_tmp + 1));
                                }
                            }
                        }
                    }
                    else
                    {
                        if (0 == segs[index].size())
                        {
                            min_tmp = (*it).cnt;
                            if (INT_MAX == (*it).end)
                            {
                                segs[index].push_back(Segment((*it).start + 1, INT_MAX, min_tmp + 1));
                            }
                            else
                            {
                                segs[index].push_back(Segment((*it).start + 1, (*it).end + 1, min_tmp + 1));
                            }
                        }
                        else
                        {
                            if (min_tmp > (*it).cnt)
                            {
                                min_tmp = (*it).cnt;
                            }

                            if (min_tmp + 1 == segs[index].back().cnt)
                            {
                                // merge
                                if (INT_MAX == (*it).end)
                                {
                                    segs[index][segs[index].size() - 1].end = INT_MAX;
                                }
                                else
                                {
                                    segs[index][segs[index].size() - 1].end = (*it).end + 1;
                                }
                            }
                            else
                            {
                                if (INT_MAX == (*it).end)
                                {
                                    segs[index].push_back(Segment((*it).start + 1, INT_MAX, min_tmp + 1));
                                }
                                else
                                {
                                    segs[index].push_back(Segment((*it).start + 1, (*it).end + 1, min_tmp + 1));
                                }
                            }
                        }
                    }
                }    
            }
        }

        index = 1 - index;
    }

    index = 1 - index;
    int min = INT_MAX;
    for (vector<Segment>::iterator it = segs[index].begin(); it != segs[index].end(); it++)
    {
        if (min > (*it).cnt)
        {
            min = (*it).cnt;
        }
    }

    cout << min << endl;    

#if DEBUG
    inFile.close();
#endif

    return 0;
}