#include <queue>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>

using namespace std;

class Pump {
public:
    Pump(int index, int amnt, int dist) {
        m_index = index;
        m_amount = amnt;
        m_distance = dist;
    }

    int m_index;
    int m_amount;
    int m_distance;
};

#define DEBUG       0

int main() {
    int n;

#if DEBUG
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        printf("open file error!\n");
        return -1;
    }
    fin >> n;
#else
    cin >> n;
#endif

    queue<Pump> pumps;
    string s;
    for (size_t i = 0; i < n; i++) {
        int amnt, dist;
#if DEBUG
        fin >> amnt >> dist;
#else
        cin >> amnt >> dist;
#endif
        Pump item(i, amnt, dist);
        pumps.push(item);
    }

    queue<Pump> res;

    int remain = 0;
    while (0 < pumps.size()) {
        Pump &item = pumps.front();
        pumps.pop();
        if ((remain + item.m_amount < item.m_distance) || (remain + item.m_amount == item.m_distance && 0 < pumps.size())) {
            if (0 == res.size()) {
                pumps.push(item);
            }
            else {
                while (0 < res.size()) {
                    Pump &pre = res.front();
                    res.pop();
                    pumps.push(pre);

                    remain = remain - pre.m_amount + pre.m_distance;
                    if ((remain + item.m_amount) < item.m_distance || (remain + item.m_amount == item.m_distance && 0 == pumps.size())) {
                        break;
                    }
                }

                if ((remain + item.m_amount) < item.m_distance || (remain + item.m_amount == item.m_distance && 0 == pumps.size())) {
                    res.push(item);
                }
                else {
                    pumps.push(item);
                }
            }
        }
        else {
            // remain + item.m_amount > item.m_distance || remain + item.m_amount == item.m_distance && 0 == pumps.size()
            remain = remain + item.m_amount - item.m_distance;
            res.push(item);
        }
    }

    Pump &first = res.front();
    cout << first.m_index << endl;

    return 0;
}
