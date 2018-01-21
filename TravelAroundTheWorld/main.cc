//
//  main.cpp
//  test
//
//  Created by 吴星煜 on 2018/1/21.
//  Copyright © 2018年 吴星煜. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <stack>
#include <deque>
#include <iostream>
#include <algorithm>

#define DEBUG       0

using namespace std;

class Seq {
public:
    Seq(int s, int e) {
        start = s;
        end = e;
        remain = 0;
        bonus = -1;
    }

    int start, end;
    long long remain;
    long long bonus;
};

int main() {
    int n;
    long long c;
    int ret = 0;

#if DEBUG
    FILE * fp = fopen("input.txt", "r");

    fscanf(fp, "%u %lld", &n, &c);
#else
    scanf("%u %lld", &n, &c);
#endif

    long long * a = (long long *)malloc(n * sizeof(long long));
    long long * b = (long long *)malloc(n * sizeof(long long));

    for (size_t i = 0; i < n; i++) {
#if DEBUG
        fscanf(fp, "%lld", &a[i]);
#else
        scanf("%lld", &a[i]);
#endif
        if (a[i] > c) {
            a[i] = c;
        }
    }

    for (size_t i = 0; i < n; i++) {
#if DEBUG
        fscanf(fp, "%lld", &b[i]);
#else
        scanf("%lld", &b[i]);
#endif
    }

    deque<Seq> cont_deq;

    // find first loop
    int tmp = 0;
    while (tmp <= n) {
        if (0 == cont_deq.size()) {
            Seq s(0, 0);
            cont_deq.push_back(s);
        }
        else {
            Seq last = cont_deq.front();

            // ==>
            if (1 == cont_deq.size()) {
                long long tmp_remain = last.remain + a[last.end];
                if (tmp_remain > c) {
                    tmp_remain = c;
                }
                if (tmp_remain >= b[last.end]) {
                    long long tmp_bonus = c - last.remain - a[last.end];
                    if (tmp_bonus < 0) {
                        tmp_bonus = 0;
                    }

                    if (0 > last.bonus || last.bonus > tmp_bonus) {
                        last.bonus = tmp_bonus;
                    }

                    last.remain = tmp_remain - b[last.end];
                    last.end = (last.end + 1) % n;

                    cont_deq.pop_front();
                    cont_deq.push_front(last);

                    tmp ++;

                    continue;
                }
            }

            int index = (last.start - 1 + n) % n;
            if (a[index] < b[index]) {
                if (1 == index) {
                    index = 1;
                }
                Seq s(index, index);
                cont_deq.push_front(s);
            }
            else {
                last.start = index;

                if (0 <= last.bonus && a[index] - b[index] > last.bonus) {
                    last.remain += last.bonus;
                }
                else {
                    last.remain += a[index] - b[index];
                }
                last.remain = last.remain > c ? c : last.remain;

                if (last.bonus < 0) {
                    last.bonus = c - a[index];
                }
                else {
                    last.bonus = (last.bonus > c - a[index]) ? (c - a[index]) : last.bonus;
                }

                cont_deq.pop_front();

                if (0 == cont_deq.size()) {
                    cont_deq.push_front(last);
                }
                else {
                    while (0 < cont_deq.size()) {
                        if (last.remain + a[last.end] < b[last.end]) {
                            cont_deq.push_front(last);
                            break;
                        }
                        else {
                            Seq next = cont_deq.front();
                            if (0 <= next.bonus && next.bonus < (last.remain + a[last.end] - b[last.end])) {
                                last.remain = next.remain + next.bonus;
                            }
                            else {
                                last.remain = next.remain + last.remain + a[last.end] - b[last.end];
                            }
                            last.remain = last.remain > c ? c : last.remain;

                            long long tmp_bonus = c - last.remain - a[last.end];
                            if (0 > tmp_bonus) {
                                tmp_bonus = 0;
                            }

                            if (0 <= next.bonus && next.bonus < tmp_bonus) {
                                tmp_bonus = next.bonus;
                            }

                            if (0 <= last.bonus && last.bonus < tmp_bonus) {
                                tmp_bonus = last.bonus;
                            }

                            last.bonus = tmp_bonus;

                            last.end = next.end;

                            cont_deq.pop_front();
                        }
                    }

                    if (0 == cont_deq.size()) {
                        cont_deq.push_front(last);
                    }
                }
            }
        }

        tmp ++;
    }

    if (1 == cont_deq.size()) {
        stack<Seq> cont_seq;
        Seq last = cont_deq.front();

        tmp = 0;
        while (tmp < n) {
            if (0 == cont_seq.size()) {
                Seq s(last.start, last.start);
                cont_seq.push(s);
            }
            else {
                Seq last = cont_seq.top();

                int index = (last.start - 1 + n) % n;
                if (a[index] < b[index]) {
                    Seq s(index, index);
                    cont_seq.push(s);
                }
                else {
                    last.start = index;

                    if (0 <= last.bonus && a[index] - b[index] > last.bonus) {
                        last.remain += last.bonus;
                    }
                    else {
                        last.remain += a[index] - b[index];
                    }
                    last.remain = last.remain > c ? c : last.remain;

                    if (last.bonus < 0) {
                        last.bonus = c - a[index];
                    }
                    else {
                        last.bonus = (last.bonus > c - a[index]) ? (c - a[index]) : last.bonus;
                    }

                    cont_seq.pop();

                    if (0 == cont_seq.size()) {
                        cont_seq.push(last);
                    }
                    else {
                        while (0 < cont_seq.size()) {
                            if (last.remain + a[last.end] < b[last.end]) {
                                cont_seq.push(last);
                                break;
                            }
                            else {
                                Seq next = cont_seq.top();

                                if (0 <= next.bonus && next.bonus < (last.remain + a[last.end] - b[last.end])) {
                                    last.remain = next.remain + next.bonus;
                                }
                                else {
                                    last.remain = next.remain + last.remain + a[last.end] - b[last.end];
                                }
                                last.remain = last.remain > c ? c : last.remain;

                                long long tmp_bonus = c - last.remain - a[last.end];
                                if (0 > tmp_bonus) {
                                    tmp_bonus = 0;
                                }

                                if (0 <= next.bonus && next.bonus < tmp_bonus) {
                                    tmp_bonus = next.bonus;
                                }

                                if (0 <= last.bonus && last.bonus < tmp_bonus) {
                                    tmp_bonus = last.bonus;
                                }

                                last.bonus = tmp_bonus;

                                last.end = next.end;

                                cont_seq.pop();
                            }
                        }

                        if (0 == cont_seq.size()) {
                            cont_seq.push(last);
                        }
                    }
                }
            }

            if (1 == cont_seq.size()) {
                ret ++;
            }

            tmp ++;
        }
    }

    printf("%d\n", ret);

    free(a);
    free(b);

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
