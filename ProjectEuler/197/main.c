#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

bool equal(double a, double b) {
    bool ret = false;

    if ((a - b) < 0.0000000001 && (a - b) > (0 - 0.0000000001)) {
        ret = true;
    }

    return ret;
}

int main() {
    double u0, b;

    scanf("%lf %lf", &u0, &b);

//    printf("u0 is %.9lf, b is %.9lf\n", u0, b);

    double u[3];
    u[0] = u0;
    u[1] = -1;
    u[2] = -1;
    int index = 0;

    while (!equal(u[index], u[(index + 1) % 3])) {
        double u_new = (int)pow(2, b - u[index] * u[index]);
        u_new /= (double)1000000000;
        index = (index + 1) % 3;
        u[index] = u_new;
//        printf("u_new is %.9lf\n", u_new);
    }

    printf("%.9lf\n", u[index] + u[(index - 1) % 3]);

    return 0;
}
