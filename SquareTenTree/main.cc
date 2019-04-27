#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#define DEBUG 0

string proc_output(string str, int level)
{
    int len = str.length();
    string ret;
    
    for (int i = len - 1; i >= 0; i--)
    {
        if ('0' == str[i])
        {
            str.erase(i);
        }
        else
        {
            break;
        }
        
    }
    
    if (0 != str.length())
    {
        reverse(str.begin(), str.end());
        stringstream ss;
        ss << level << " " << str;
        ret = ss.str();
    }
    
    return ret;
}

int main()
{
    string L, R;
    
    cin >> L;
    cin >> R;
    
    reverse(L.begin(), L.end());
    reverse(R.begin(), R.end());
    
    if (L.length() != R.length())
    {
        int tmp = R.length() - L.length();
        for (size_t i = 0; i < tmp; i++)
        {
            L.append("0");
        }
    }
    
    int end_idx;
    for (end_idx = (R.length() - 1); end_idx >= 0; end_idx--)
    {
        if (L[end_idx] != R[end_idx])
        {
            break;
        }
    }
    
    vector<string> ret;
    if (0 <= end_idx)
    {
        int level = 0;
        
        // round 1
        for (level = 0; pow(2, level - 1) <= end_idx; level++)
        {
            if (0 == level && '1' == L[0])
            {
                int i;
                for (i = 1; i < pow(2, level); i++)
                {
                    if ('0' != L[i])
                    {
                        break;
                    }
                }
                
                if (i == pow(2, level))
                {
                    continue;
                }
            }
            
            if (end_idx < pow(2, level))
            {
                // 本次循环内结束
                int carry = 0;
                stringstream ss;
                for (int i = (0 == level) ? 0 : pow(2, level - 1); i <= end_idx; i++)
                {
                    if (R[i] + carry >= L[i])
                    {
                        if (i == end_idx)
                        {
                            if (R[i] + carry - L[i])
                            {
                                ss << (R[i] + carry - L[i]);
                            }
                        }
                        else
                        {
                            ss << (R[i] + carry - L[i]);
                        }
                        carry = 0;
                    }
                    else
                    {
                        ss << (10 + R[i] - L[i] + carry);
                        carry = -1;
                    }
                    L[i] = R[i];
                }
                string str = proc_output(ss.str(), level);
                if (0 < str.length())
                {
                    ret.push_back(str);
                }
                
                break;
            }
            else
            {
                // 之后循环内结束
                if ('0' == L[0] && 0 == level)
                {
                    ret.push_back("0 1");
                    L[0] = '1';
                    level --;
                    continue;
                }
                
                int i;
                for (i = (0 == level) ? 0 : pow(2, level - 1); i < pow(2, level); i++)
                {
                    if (('0' != L[i] && 0 < i) || ((0 == i) && '1' != L[i]))
                    {
                        break;
                    }
                }
                
                if (i == pow(2, level))
                {
                    // all 0, next level
                    continue;
                }
                
                int carry = 0;
                stringstream ss;
                for (i = (0 == level) ? 0 : pow(2, level - 1); i < pow(2, level); i++)
                {
                    if (0 == level)
                    {
                        ss << 11 - (L[i] - '0');
                    }
                    else
                    {
                        if (10 == (10 + carry - (L[i] - '0')))
                        {
                            ss << 0;
                        }
                        else
                        {
                            ss << 10 + carry - (L[i] - '0');
                            carry = -1;
                        }
                    }

                    L[i] = '0';
                }
                
                string str = proc_output(ss.str(), level);
                if (0 < str.length())
                {
                    ret.push_back(str);
                }
                
                for (i = pow(2, level); i <= end_idx; i++)
                {
                    if ('9' == L[i])
                    {
                        L[i] = '0';
                    }
                    else
                    {
                        L[i]++;
                        break;
                    }
                }
            }
        }
        
        // round 2
        if (0 < level)
        {
            level--;
            
            for (; 0 <= level; level--)
            {
                stringstream ss;
                for (int i = (0 == level) ? 0 : pow(2, level - 1); i < pow(2, level); i++)
                {
                    ss << R[i];
                }
                
                string str = proc_output(ss.str(), level);
                if (0 < str.length())
                {
                    ret.push_back(str);
                }
            }
        }
    }
    else
    {
        ret.push_back("0 1");
    }
    
    cout << ret.size() << endl;
    for (size_t i = 0; i < ret.size(); i++)
    {
        cout << ret[i] << endl;
    }
    
    return 0;
}
