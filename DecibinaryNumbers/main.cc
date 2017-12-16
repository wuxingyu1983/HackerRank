//
//  main.cpp
//  DecibinaryNumbers
//
//  Created by 吴星煜 on 2017/12/16.
//  Copyright © 2017年 吴星煜. All rights reserved.
//
//
//  main.cpp
//  DecibinaryNumbers
//
//  Created by 吴星煜 on 2017/12/16.
//  Copyright © 2017年 吴星煜. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <math.h>

#define DEBUG       0

using namespace std;

class Cnt {
public:
    unsigned int            value;
    unsigned long long      count;
};

vector< vector<class Cnt> >     vec(54);

unsigned long long mins[] = {0,9,27,63,135,279,567,1143,2295,4599,9207,18423,36855,73719,147447,294903,589815,1179639,2359287,4718583,9437175,18874359,37748727,75497463,150994935,301989879,603979767,1207959543,2415919095,4831838199,9663676407,19327352823,38654705655,77309411319,154618822647,309237645303,618475290615,1236950581239,2473901162487,4947802324983,9895604649975,19791209299959,39582418599927,79164837199863,158329674399735,316659348799479,633318697598967,1266637395197943,2533274790395895,5066549580791799,10133099161583607};
vector<unsigned long long>  min_vec(mins, mins + 51);

unsigned long long maxs[] = {0,1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,1073741824,2147483648,4294967296,8589934592,17179869184,34359738368,68719476736,137438953472,274877906944,549755813888,1099511627776,2199023255552,4398046511104,8796093022208,17592186044416,35184372088832,70368744177664,140737488355328,281474976710656,562949953421312,1125899906842624,2251799813685248,4503599627370496,9007199254740992,18014398509481984};
vector<unsigned long long> max_vec(maxs, maxs + 56);

int getMinDigit(unsigned long long num) {
    int ret = 1;

    // >=
    vector<unsigned long long>::iterator loc = lower_bound(min_vec.begin(), min_vec.end(), num);
    ret = loc - min_vec.begin();

    return ret;
}

int getMaxDigit(unsigned long long num) {
    int ret = 1;

    // >
    vector<unsigned long long>::iterator loc = upper_bound(max_vec.begin(), max_vec.end(), num);
    ret = loc - max_vec.begin() - 1;

    return ret;
}

unsigned long long getCount(unsigned long long number, int digit) {
    unsigned long long ret = 0;

    unsigned long long power = maxs[digit];

    for (size_t i = 1; i <= 9; i++) {
        long long remain = number - power * i;
        if (0 > remain) {
            break;
        }

        for (size_t j = digit - 1; j >= 1; j--) {
            int vec_size = vec[j].size();
            if (0 < vec_size) {
                if (remain >= vec[j][0].value && remain <= vec[j][vec_size - 1].value) {
/*
                    if (remain != vec[j][remain - vec[j][0].value].value) {
                        ret += vec[j][remain - vec[j][0].value].count;
                    }
*/
                    ret += vec[j][remain - vec[j][0].value].count;
                }
            }
        }
    }

    return ret;
}

int main() {
#if DEBUG
    FILE * fp;
    fp = fopen("input.txt", "r");

    FILE * fp_out;
    fp_out = fopen("output.txt", "w");
#endif

    int q;
#if DEBUG
    fscanf(fp, "%d", &q);
#else
    scanf("%d", &q);
#endif


    vector<long long> input(q);
    vector<long long> sorted_input(q);
    vector<string> sorted_output(q);

    for (size_t i = 0; i < q; i++) {
        long long x;

#if DEBUG
        fscanf(fp, "%lld", &x);
#else
        scanf("%lld", &x);
#endif

        input[i] = x;
        sorted_input[i] = x;
    }

    // sort
    sort(sorted_input.begin(), sorted_input.end());

    int iIn = 0;
    unsigned long long xth = 0;
    unsigned long long number = 0;

    while (iIn < q) {
        int min_digit = getMinDigit(number);
        int max_digit = getMaxDigit(number);

        min_digit = min_digit > 0 ? min_digit : 1;
        max_digit = max_digit > 0 ? max_digit : 1;

        int now_digit = min_digit;
        while (now_digit <= max_digit) {
            class Cnt new_cnt;
            new_cnt.value = number;
            if (1 == now_digit) {
                new_cnt.count = 1;
            }
            else {
                new_cnt.count = getCount(number, now_digit);
            }

            while (xth + new_cnt.count >= sorted_input[iIn]) {
                // hit
                /*
                 if (1 == now_digit) {
                 sorted_output[iIn] += '0' + number;
                 }
                 else {
                 unsigned long long offset = sorted_input[iIn] - xth;

                 }
                 */
                sorted_output[iIn] = to_string(number);
                iIn ++;
                if (iIn >= q) {
                    break;
                }
            }

            if (iIn >= q) {
                break;
            }

            xth += new_cnt.count;

            vec[now_digit].push_back(new_cnt);

            now_digit ++;
        }
        number ++;
    }

    // output
    for (size_t i = 0; i < q; i++) {
        long long x = input[i];

        vector<long long>::iterator loc = lower_bound(sorted_input.begin(), sorted_input.end(), x);
        int pos = loc - sorted_input.begin();
#if DEBUG
        fprintf(fp_out, "%s\n", sorted_output[pos].c_str());
#else
        printf("%s\n", sorted_output[pos].c_str());
#endif
    }

#if DEBUG
    fclose(fp);
    fclose(fp_out);
#endif

    return 0;
}
