#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

#define DEBUG       0

using namespace std;

class Interval {
public:
    Interval(int a, int b) {
        m_a = a;
        m_b = b;
    }

    int m_a, m_b;
};

bool comp(const Interval &v1, const Interval &v2)
{
    if (v1.m_b < v2.m_b) {
        return true;
    }

    if (v1.m_b == v2.m_b) {
        return v1.m_a < v2.m_a;
    }

    return false;
}

int main() {
    int s;
#if DEBUG
    FILE * fp = fopen("input.txt", "r");
    fscanf(fp, "%d", &s);
#else
    scanf("%d", &s);
#endif

    for (size_t i = 0; i < s; i++) {
        int n;
#if DEBUG
        fscanf(fp, "%d", &n);
#else
        scanf("%d", &n);
#endif

        vector<Interval> vec;
        vec.reserve(1000);

        for (size_t j = 0; j < n; j++) {
            int a, b;
#if DEBUG
            fscanf(fp, "%d %d", &a, &b);
#else
            scanf("%d %d", &a, &b);
#endif

            Interval inteval(a, b);
            vec.push_back(inteval);
        }

        sort(vec.begin(), vec.end(), comp);

        int ret = 0;
        int b[2] = {0, 0};

        for (size_t j = 0; j < n; j++) {
            Interval &inteval = vec[j];

            if (b[0] < inteval.m_a && b[1] < inteval.m_a) {
                if (b[1] > b[0]) {
                    b[1] = inteval.m_b;
                    ret ++;
                }
                else {
                    b[0] = inteval.m_b;
                    ret ++;
                }
            }
            else if (b[0] < inteval.m_a) {
                b[0] = inteval.m_b;
                ret ++;
            }
            else if (b[1] < inteval.m_a) {
                b[1] = inteval.m_b;
                ret ++;
            }
            else {

            }
        }

        printf("%d\n", ret);
    }

#if DEBUG
    fclose(fp);
#endif
    return 0;
}
