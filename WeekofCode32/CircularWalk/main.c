#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

bool inRange(int n, int s, int t, int min, int max) {
    bool ret = false;

    if (t > s) {
        if (t <= (s + max)) {
            return true;
        }

        if (t >= (s + n + min)) {
            return true;
        }
    }
    else {
        // t < s
        if (t >= (s + min)) {
            return true;
        }

        if (t <= (s - n + max)) {
            return true;
        }
    }

    return ret;
}

int main() {
    int n;
    int s;
    int t;
    scanf("%d %d %d", &n, &s, &t);
    int r_0;
    int g;
    int seed;
    int p;
    scanf("%d %d %d %d", &r_0, &g, &seed, &p);

    int * r = malloc(sizeof(int) * n);
    r[0] = r_0;
    for (size_t i = 1; i < n; i++) {
        unsigned long long tmp = r[i - 1];
        tmp *= (unsigned long long)g;
        tmp += (unsigned long long)seed;
        r[i] = tmp % p;
    }

    int ret = 0;

    if (s != t) {
        int min, old_min, max, old_max;
        min = -1 * r[s];
        old_min = 0;
        max = r[s];
        old_max = 0;

        ret ++;

//        printf("the min is %d, old_min is %d, max is %d, old_max is %d\n", min, old_min, max, old_max);

        if (false == inRange(n, s, t, min, max)) {
            bool go_on = true;
            while (go_on) {
                ret ++;
                int new_min, new_max;
                new_min = min;
                new_max = max;
                for (int i = min; i < old_min; i++) {
                    int index = i + s;
                    if (0 > index) {
                        index += n;
                    }

                    if ((i - r[index]) < new_min) {
                        new_min = i - r[index];
                        if (true == inRange(n, s, t,  new_min, new_max)) {
                            go_on = false;
                            break;
                        }
                    }

                    if ((i + r[index]) > new_max) {
                        new_max = i + r[index];
                        if (true == inRange(n, s, t, new_min, new_max)) {
                            go_on = false;
                            break;
                        }
                    }
                }

                for (int i = max; i > old_max; i--) {
                    int index = i + s;
                    if (n <= index) {
                        index -= n;
                    }

                    if ((i - r[index]) < new_min) {
                        new_min = i - r[index];
                        if (true == inRange(n, s, t,  new_min, new_max)) {
                            go_on = false;
                            break;
                        }
                    }

                    if ((i + r[index]) > new_max) {
                        new_max = i + r[index];
                        if (true == inRange(n, s, t, new_min, new_max)) {
                            go_on = false;
                            break;
                        }
                    }
                }

                if (new_max == max && new_min == min) {
                    ret = -1;
                    go_on = false;
                }
                else {
                    old_min = min;
                    old_max = max;

                    min = new_min;
                    max = new_max;
                }

//                printf("the min is %d, old_min is %d, max is %d, old_max is %d\n", min, old_min, max, old_max);
            }
        }
    }

    printf("%d\n", ret);

    free(r);

    return 0;
}
