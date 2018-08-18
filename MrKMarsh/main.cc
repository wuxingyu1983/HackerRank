//
//  main.cpp
//  test
//
//  Created by 吴星煜 on 2018/8/18.
//  Copyright © 2018年 吴星煜. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX         501

char points[MAX][MAX];
int perimeter[2][MAX][MAX];
char flags[MAX][MAX];    // 1 - have marsh

int main()
{
    int m, n;

    scanf("%d %d\n", &m, &n);

    for (size_t i = 0; i < m; i++) {
        scanf("%s", points[i]);
    }

    int max = 0;
    int index = 0;

    for (size_t row = 0; row < m; row++) {
        for (size_t step = 1; step < n; step++) {
            for (size_t i = 0; i < n && (i + step) < n; i++) {
                if (0 == row) {
                    if (1 == step) {
                        if ('x' == points[row][i] || 'x' == points[row][i + step]) {
                            perimeter[index][i][i + step] = 0;
                            flags[i][i + step] = 1;
                        }
                        else {
                            perimeter[index][i][i + step] = step;
                        }
                    }
                    else {
                        if ('x' == points[row][i + step] || 1 == flags[i][i + step - 1]) {
                            // have marsh
                            perimeter[index][i][i + step] = 0;
                            flags[i][i + step] = 1;
                        }
                        else {
                            perimeter[index][i][i + step] = step;
                        }
                    }
                }
                else {
                    if (0 == perimeter[1 - index][i][i + step]) {
                        // new border
                        if (1 == step) {
                            if ('x' == points[row][i] || 'x' == points[row][i + step]) {
                                perimeter[index][i][i + step] = 0;
                                flags[i][i + step] = 1;
                            }
                            else {
                                perimeter[index][i][i + step] = step;
                                flags[i][i + step] = 0;
                            }
                        }
                        else {
                            if ('x' == points[row][i + step] || 1 == flags[i][i + step - 1]) {
                                perimeter[index][i][i + step] = 0;
                                flags[i][i + step] = 1;
                            }
                            else {
                                perimeter[index][i][i + step] = step;
                                flags[i][i + step] = 0;
                            }
                        }
                    }
                    else {
                        if ('x' == points[row][i] || 'x' == points[row][i + step]) {
                            perimeter[index][i][i + step] = 0;
                            flags[i][i + step] = 1;
                        }
                        else {
                            flags[i][i + step] = flags[i][i + step - 1];
                            if (step == perimeter[1 - index][i][i + step]) {
                                perimeter[index][i][i + step] = 2 + 2 * step;
                            }
                            else {
                                perimeter[index][i][i + step] = 2 + perimeter[1 - index][i][i + step];
                            }

                            if (0 == flags[i][i + step]) {
                                if (max < perimeter[index][i][i + step]) {
                                    max = perimeter[index][i][i + step];
                                }
                            }
                        }
                    }
                }
            }
        }

        index = 1 - index;
    }

    if (0 < max) {
        printf("%d\n", max);
    }
    else {
        printf("impossible\n");
    }

    return 0;
}
