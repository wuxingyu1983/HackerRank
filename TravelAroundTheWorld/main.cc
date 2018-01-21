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
    }

    for (size_t i = 0; i < n; i++) {
        scanf("%lld", &b[i]);
    }

    stack<Seq> cont_seq;

    // find first loop
    int tmp = 0;
    while (tmp < n) {
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
                if (last.bonus < 0) {
                    last.bonus = c - a[index];
                }
                else {
                    last.bonus = (last.bonus > c - a[index]) ? (c - a[index]) : last.bonus;
                }
                last.remain += last.bonus;
                last.remain = last.remain > c ? c : last.remain;

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
                            long long tmp_bonus = c - last.remain - a[last.end];
                            if (0 > tmp_bonus) {
                                tmp_bonus = 0;
                            }

                            if (last.remain > tmp_bonus) {
                                last.remain = next.remain + tmp_bonus;
                            }
                            else {
                                last.remain = next.remain + last.remain;
                            }
                            last.remain = last.remain > c ? c : last.remain;

                            last.end = next.end;

                            if (0 >= last.bonus && last.bonus < tmp_bonus) {
                                tmp_bonus = last.bonus;
                            }

                            if (0 >= next.bonus && next.bonus < tmp_bonus) {
                                tmp_bonus = next.bonus;
                            }

                            last.bonus = tmp_bonus;

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



    printf("%d\n", ret);

    free(a);
    free(b);

    return 0;
}
