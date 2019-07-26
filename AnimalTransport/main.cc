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

#define DEBUG       1
#define MAX_MN      50001

using namespace std;

class Animal
{
public:
    char type;
    int src, dst;

    Animal(char _type = 0, int _src = 0, int _dst = 0)
    {
        type = _type;
        src = _src;
        dst = _dst;
    }

    Animal(const Animal & v)
    {
        type = v.type;
        src = v.src;
        dst = v.dst;
    }
};

bool comp(Animal& v1, Animal& v2)
{
    bool ret = false;

    if (v1.src < v2.src)
    {
        ret = true;
    }

    return ret;
}


int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int t;
#if DEBUG
    inFile >> t;
#else
    cin >> t;
#endif

    for (size_t i_t = 0; i_t < t; i_t++)
    {
        int m, n;
#if DEBUG
        inFile >> m >> n;
#else
        cin >> m >> n;
#endif

        vector<Animal> tmp_animals(n);
        for (size_t i_n = 0; i_n < n; i_n++)
        {
            char type;
#if DEBUG
            inFile >> type;
#else
            cin >> type;
#endif

            tmp_animals[i_n] = Animal(type, 0, 0);
        }

        for (size_t i_n = 0; i_n < n; i_n++)
        {
            int src;
#if DEBUG
            inFile >> src;
#else
            cin >> src;
#endif
            tmp_animals[i_n].src = src;
        }
        
        // 0 - {E, C}, 1 - {D, M}
        vector<Animal> animals0;
        animals0.reserve(n);
        vector<Animal> animals1;
        animals1.reserve(n);
        for (size_t i_n = 0; i_n < n; i_n++)
        {
            int dst;
#if DEBUG
            inFile >> dst;
#else
            cin >> dst;
#endif
            tmp_animals[i_n].dst = dst;

            if (tmp_animals[i_n].src < tmp_animals[i_n].dst)
            {
                if ('E' == tmp_animals[i_n].type || 'C' == tmp_animals[i_n].type)
                {
                    animals0.push_back(tmp_animals[i_n]);
                }
                else
                {
                    animals1.push_back(tmp_animals[i_n]);
                }
            }
        }

        // sort
        sort(animals0.begin(), animals0.end(), comp);
        sort(animals1.begin(), animals1.end(), comp);

        map<int, vector<int> > map0;
        map<int, vector<int> > map1;

        for (int i = 0; i < animals0.size(); i ++)
        {
            Animal& v = animals0[i];
            if (map0.end() == map0.find(v.dst))
            {
                map0.insert(pair<int, vector<int> >(v.dst, vector<int>()));
            }

            vector<int>& vec = map0.find(v.dst)->second;
            vec.push_back(v.src);
        }

        for (int i = 0; i < animals1.size(); i ++)
        {
            Animal& v = animals1[i];
            if (map1.end() == map1.find(v.dst))
            {
                map1.insert(pair<int, vector<int> >(v.dst, vector<int>()));
            }

            vector<int>& vec = map1.find(v.dst)->second;
            vec.push_back(v.src);
        }

        int dp[MAX_MN];
        int sum0[MAX_MN];
        int sum1[MAX_MN];
        memset(dp, 0, MAX_MN * sizeof(int));
        memset(sum0, 0, MAX_MN * sizeof(int));
        memset(sum1, 0, MAX_MN * sizeof(int));

        for (int i = 1; i <= m; i ++)
        {
            int tmp = dp[i - 1];
            if (map0.end() != map0.find(i))
            {
                vector<int>& vec = map0.find(i)->second;
                for (int j = 1; j < i; j ++)
                {
                    vector<int>::iterator low = lower_bound(vec.begin(), vec.end(), j);
                    if (low != vec.end())
                    {
                        sum0[j] += vec.size() - (low - vec.begin());
                        if (dp[j] + sum0[j] > tmp)
                        {
                            tmp = dp[j] + sum0[j];
                        }
                    }
                }
            }

            if (map1.end() != map1.find(i))
            {
                vector<int>& vec = map1.find(i)->second;
                for (int j = 1; j < i; j ++)
                {
                    vector<int>::iterator low = lower_bound(vec.begin(), vec.end(), j);
                    if (low != vec.end())
                    {
                        sum1[j] += vec.size() - (low - vec.begin());
                        if (dp[j] + sum1[j] > tmp)
                        {
                            tmp = dp[j] + sum1[j];
                        }
                    }
                }
            }

            dp[i] = tmp;
        }

        int outed = 0;
        for (int i = 1; i <= m; i ++)
        {
            if (dp[i] != outed)
            {
                for (int j = outed; j < dp[i]; j ++)
                {
                    cout << i << " ";
                }

                outed = dp[i];
            }
        }

        for (int i = outed; i < n; i ++)
        {
            cout << "-1 ";
        }

        cout << endl;        
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
