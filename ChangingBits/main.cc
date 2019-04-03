//
//  main.cpp
//  test
//
//  Created by Julian on 2019/4/1.
//  Copyright © 2019 Julian. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <set>

#define DEBUG 0

using namespace std;

class Seg
{
  public:
    int start, end;
    int value; // 0 or 1

    Seg() {}
    Seg(int s, int e, int v) : start(s), end(e), value(v) {}

    bool operator<(const Seg &seg) const
    {
        return this->end < seg.start;
    }
};

int main()
{
//    cout << "begin" << endl;
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n, q;
#if DEBUG
    inFile >> n >> q;
#else
    cin >> n >> q;
#endif

    string a, b;
#if DEBUG
    inFile >> a;
    inFile >> b;
#else
    cin >> a;
    cin >> b;
#endif

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    vector<int> c;
    c.reserve(n + 1);

    int carry = 0;
    for (size_t i = 0; i < n; i++)
    {
        int tmp = (a[i] - '0') + (b[i] - '0') + carry;
        if (0 == tmp)
        {
            c.push_back(0);
            carry = 0;
        }
        else if (1 == tmp)
        {
            c.push_back(1);
            carry = 0;
        }
        else if (2 == tmp)
        {
            c.push_back(0);
            carry = 1;
        }
        else
        {
            c.push_back(1);
            carry = 1;
        }
    }
    if (carry)
    {
        c.push_back(1);
    }

    multiset<Seg> seg_set;
    Seg *pre = NULL;

    size_t i = 0;
    for (i = 0; i < c.size(); i++)
    {
        if (!pre)
        {
            pre = new Seg(0, 0, c[i]);
        }
        else
        {
            if (pre->value != c[i])
            {
                pre->end = i - 1;
                seg_set.insert(*pre);

                pre = new Seg(i, i, c[i]);
            }
        }
    }

    pre->end = i - 1;
    seg_set.insert(*pre);

    for (size_t i = 0; i < q; i++)
    {
        string op;
#if DEBUG
        inFile >> op;
#else
        cin >> op;
#endif

        if (op == "get_c")
        {
            int idx;
#if DEBUG
            inFile >> idx;
#else
            cin >> idx;
#endif

            multiset<Seg>::iterator it = seg_set.find(Seg(idx, idx, 0));
            if (it == seg_set.end())
            {
                cout << "0";
            }
            else
            {
                cout << (*it).value;
            }
        }
        else
        {
            int offset = 0;
            int idx, x;
            if (op == "set_a")
            {
#if DEBUG
                inFile >> idx >> x;
#else
                cin >> idx >> x;
#endif

                offset = x - (a[idx] - '0');
                a[idx] = '0' + x;
            }
            else if (op == "set_b")
            {
#if DEBUG
                inFile >> idx >> x;
#else
                cin >> idx >> x;
#endif

                offset = x - (b[idx] - '0');
                b[idx] = '0' + x;
            }

            if (0 == offset)
            {
                // do nothing
            }
            else
            {
                multiset<Seg>::iterator it = seg_set.find(Seg(idx, idx, 0));
                if (0 < offset)
                {
                    // + 1
                    if (0 == it->value)
                    {
                        // 0 + 1
                        if (it->start == idx && it->end == idx)
                        {
                            multiset<Seg>::iterator it_nxt = seg_set.find(Seg(idx + 1, idx + 1, 0));
                            multiset<Seg>::iterator it_pre = seg_set.find(Seg(idx - 1, idx - 1, 0));

                            Seg *item = new Seg(idx, idx, 1);

                            if (it_nxt != seg_set.end())
                            {
                                item->end = it_nxt->end;
                                seg_set.erase(it_nxt);
                            }

                            if (it_pre != seg_set.end())
                            {
                                item->start = it_pre->start;
                                seg_set.erase(it_pre);
                            }

                            seg_set.insert(*item);
                        }
                        else
                        {
                            if (it->start == idx)
                            {
                                Seg *item = new Seg(idx, idx, 1);

                                multiset<Seg>::iterator it_pre = seg_set.find(Seg(idx - 1, idx - 1, 0));

                                if (it_pre != seg_set.end())
                                {
                                    item->start = it_pre->start;
                                    seg_set.erase(it_pre);
                                }

                                seg_set.insert(*item);

                                seg_set.insert(Seg(idx + 1, it->end, 0));
                            }
                            else if (it->end == idx)
                            {
                                Seg *item = new Seg(idx, idx, 1);

                                multiset<Seg>::iterator it_nxt = seg_set.find(Seg(idx + 1, idx + 1, 0));

                                if (it_nxt != seg_set.end())
                                {
                                    item->end = it_nxt->end;
                                    seg_set.erase(it_nxt);
                                }

                                seg_set.insert(*item);

                                seg_set.insert(Seg(it->start, idx - 1, 0));
                            }
                            else
                            {
                                seg_set.insert(Seg(idx, idx, 1));
                                seg_set.insert(Seg(it->start, idx - 1, 0));
                                seg_set.insert(Seg(idx + 1, it->end, 0));
                            }
                        }
                    }
                    else
                    {
                        // 1, 1 + 1
                        Seg * item = new Seg(idx, it->end, 0);

                        if (idx == it->start)
                        {
                            multiset<Seg>::iterator it_pre = seg_set.find(Seg(idx - 1, idx - 1, 0));
                            if (it_pre != seg_set.end())
                            {
                                item->start = it_pre->start;
                                seg_set.erase(it_pre);
                            }
                        }
                        else
                        {
                            seg_set.insert(Seg(it->start, idx - 1, 1));
                        }

                        seg_set.insert(*item);
                        
                        // 进位 
                        multiset<Seg>::iterator it_nxt = seg_set.find(Seg(it->end + 1, it->end + 1, 0));
                        if (it_nxt != seg_set.end())
                        {
                            if (it_nxt->end == it_nxt->start)
                            {
                                multiset<Seg>::iterator it_nxt2 = seg_set.find(Seg(it->end + 2, it->end + 2, 0));
                                if (it_nxt2 != seg_set.end())
                                {
                                    seg_set.insert(Seg(it->end + 1, it_nxt2->end, 1));
                                    seg_set.erase(it_nxt2);
                                }
                                else
                                {
                                    seg_set.insert(Seg(it->end + 1, it->end + 1, 1));
                                }
                            }
                            else
                            {
                                seg_set.insert(Seg(it->end + 1, it->end + 1, 1));
                                seg_set.insert(Seg(it->end + 2, it_nxt->end, 0));
                            }
                            seg_set.erase(it_nxt);
                        }
                        else
                        {
                            seg_set.insert(Seg(it->end + 1, it->end + 1, 1));
                        }
                    }

                    seg_set.erase(it);
                }
                else
                {
                    // 0 > offset, - 1
                    if (0 == it->value)
                    {
                        // 0 - 1
                        Seg * item = new Seg(idx, it->end, 1);

                        if (idx == it->start)
                        {
                            multiset<Seg>::iterator it_pre = seg_set.find(Seg(idx - 1, idx - 1, 0));
                            if (it_pre != seg_set.end())
                            {
                                item->start = it_pre->start;
                                seg_set.erase(it_pre);
                            }
                        }
                        else
                        {
                            seg_set.insert(Seg(it->start, idx - 1, 0));
                        }

                        seg_set.insert(*item);

                        // 借位
                        multiset<Seg>::iterator it_nxt = seg_set.find(Seg(it->end + 1, it->end + 1, 0));
                        if (it_nxt != seg_set.end())
                        {
                            if (it_nxt->end == it_nxt->start)
                            {
                                multiset<Seg>::iterator it_nxt2 = seg_set.find(Seg(it->end + 2, it->end + 2, 0));
                                if (it_nxt2 != seg_set.end())
                                {
                                    seg_set.insert(Seg(it->end + 1, it_nxt2->end, 0));
                                    seg_set.erase(it_nxt2);
                                }
                                else
                                {
                                    seg_set.insert(Seg(it->end + 1, it->end + 1, 0));
                                }
                            }
                            else
                            {
                                seg_set.insert(Seg(it->end + 1, it->end + 1, 0));
                                seg_set.insert(Seg(it->end + 2, it_nxt->end, 1));
                            }
                            seg_set.erase(it_nxt);
                        }
                    }
                    else
                    {
                        // 1, 1 - 1
                        if (idx == it->start && idx == it->end)
                        {
                            multiset<Seg>::iterator it_nxt = seg_set.find(Seg(idx + 1, idx + 1, 0));
                            multiset<Seg>::iterator it_pre = seg_set.find(Seg(idx - 1, idx - 1, 0));

                            Seg *item = new Seg(idx, idx, 0);

                            if (it_nxt != seg_set.end())
                            {
                                item->end = it_nxt->end;
                                seg_set.erase(it_nxt);
                            }

                            if (it_pre != seg_set.end())
                            {
                                item->start = it_pre->start;
                                seg_set.erase(it_pre);
                            }

                            seg_set.insert(*item);
                        }
                        else
                        {
                            if (it->start == idx)
                            {
                                Seg *item = new Seg(idx, idx, 0);

                                multiset<Seg>::iterator it_pre = seg_set.find(Seg(idx - 1, idx - 1, 0));

                                if (it_pre != seg_set.end())
                                {
                                    item->start = it_pre->start;
                                    seg_set.erase(it_pre);
                                }

                                seg_set.insert(*item);

                                seg_set.insert(Seg(idx + 1, it->end, 1));
                            }
                            else if (it->end == idx)
                            {
                                Seg *item = new Seg(idx, idx, 0);

                                multiset<Seg>::iterator it_nxt = seg_set.find(Seg(idx + 1, idx + 1, 0));

                                if (it_nxt != seg_set.end())
                                {
                                    item->end = it_nxt->end;
                                    seg_set.erase(it_nxt);
                                }

                                seg_set.insert(*item);

                                seg_set.insert(Seg(it->start, idx - 1, 1));
                            }
                            else
                            {
                                seg_set.insert(Seg(idx, idx, 0));
                                seg_set.insert(Seg(it->start, idx - 1, 1));
                                seg_set.insert(Seg(idx + 1, it->end, 1));
                            }
                        }
                    }

                    seg_set.erase(it);
                }
            }
        }
    }

    cout << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
