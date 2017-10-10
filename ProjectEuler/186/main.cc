#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

#define MAX     1000000

int s[56];

int getCallerAndCalled(int k, bool over) {
    if (over) {
        s[k] = (s[k + 55 - 24] + s[k]) % MAX;
    }
    else {
        long long tmp = k;
        tmp *= (long long)k;
        tmp *= (long long)k;
        tmp *= 300007;

        tmp += 100003;

        tmp -= (long long)(k * 200003);

        s[k] = tmp % MAX;
    }

    return s[k];
}

vector<int> friend_index(MAX);
vector<int> free_index(MAX/2);
vector< vector<int> > friends(MAX/2);

int pm_friend_index = -1;
int next_free = 0;
int pm = 0;

void makeFriend(int caller, int called) {
    if (friend_index[caller] < 0 && friend_index[called] < 0) {
        // make new friend group
        int new_index = next_free;
        next_free = free_index[next_free];

        friends[new_index].push_back(caller);
        friends[new_index].push_back(called);

        free_index[new_index] = -1;

        friend_index[caller] = new_index;
        friend_index[called] = new_index;
    }
    else if (friend_index[caller] >= 0 && friend_index[called] >= 0) {
        // merge two friend groups
        if (friend_index[caller] != friend_index[called]) {
            int called_size = friends[friend_index[called]].size();
            int caller_size = friends[friend_index[caller]].size();
            int from_index;
            int to_index;
            if (caller_size > called_size) {
                // called => caller
                from_index = friend_index[called];
                to_index = friend_index[caller];
            }
            else {
                // caller => called
                from_index = friend_index[caller];
                to_index = friend_index[called];
            }
            for (size_t i = 0; i < friends[from_index].size(); i++) {
                friends[to_index].push_back(friends[from_index][i]);
                friend_index[friends[from_index][i]] = to_index;
            }
            friends[from_index].clear();
            free_index[from_index] = next_free;
            next_free = from_index;
        }
    }
    else {
        // add to one friend group
        if (friend_index[caller] < 0) {
            friend_index[caller] = friend_index[called];
            friends[friend_index[called]].push_back(caller);
        }
        else {
            // friend_index[called] < 0
            friend_index[called] = friend_index[caller];
            friends[friend_index[caller]].push_back(called);
        }
    }

    if (pm == caller) {
        pm_friend_index = friend_index[caller];
    }
    if (pm == called) {
        pm_friend_index = friend_index[called];
    }
}

int main() {
    string prime_minister;
    int p;

    cin >> prime_minister >> p;

    for (size_t i = 0; i < prime_minister.length(); i++) {
        pm = pm * 10 + (prime_minister[0] - '0');
    }

    for (size_t i = 0; i < free_index.size(); i++) {
        free_index[i] = i + 1;
    }

    for (size_t i = 0; i < friend_index.size(); i++) {
        friend_index[i] = -1;
    }

    long long output = 0;
    int k = 1;
    bool over = false;

    while(true) {
        int caller = getCallerAndCalled(k, over);
        k ++;
        if (k > 55) {
            k = 1;
            over = true;
        }
        int called = getCallerAndCalled(k, over);

        // cout << caller << "  " << called << endl;

        if (caller != called) {
            output ++;

            makeFriend(caller, called);

            if (0 <= pm_friend_index) {
                if ((friends[pm_friend_index].size() + 1) >= (MAX / 100 * p)) {
                    break;
                }
            }
        }
        k ++;
        if (k > 55) {
            k = 1;
            over = true;
        }
    }

    cout << output << endl;

    return 0;
}
