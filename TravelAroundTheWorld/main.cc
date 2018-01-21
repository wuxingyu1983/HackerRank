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
#include <iostream>
#include <algorithm>

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

    scanf("%u %lld", &n, &c);

    long long * a = (long long *)malloc(n * sizeof(long long));
    long long * b = (long long *)malloc(n * sizeof(long long));

    for (size_t i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        if (a[i] > c) {
            a[i] = c;
        }
    }

    for (size_t i = 0; i < n; i++) {
        scanf("%lld", &b[i]);
    }

    stack<Seq> cont_seq;

    // find first loop
    int tmp = 0;
    while (tmp <= n) {
        if (0 == cont_seq.size()) {
            Seq s(0, 0);
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

        tmp ++;
    }

    if (1 == cont_seq.size()) {
        Seq last = cont_seq.top();
        cont_seq.pop();

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

    return 0;
}
