#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

#define  E 0.00001

#define DEBUG   0

struct line {
    int u, v, a, b;
    double d;
};

int max_a, max_b;
double max = 0;

bool fequal(double a, double b) {
    if (fabs(a - b) < E) {
        return true;
    }
    else {
        return false;
    }
}

void quick_sort(struct line * s, int l, int r) {
    if (l < r)
    {
        int i = l, j = r;
        struct line x;
        memcpy(&x, &s[l], sizeof(struct line));
        while (i < j)
        {
            while(i < j && s[j].d <= x.d)
            j--;
            if(i < j)
            //        s[i++] = s[j];
            memcpy(&s[i++], &s[j], sizeof(struct line));

            while(i < j && s[i].d > x.d)
            i++;
            if(i < j)
            //        s[j--] = s[i];
            memcpy(&s[j--], &s[i], sizeof(struct line));
        }
        //      s[i] = x;
        memcpy(&s[i], &x, sizeof(struct line));
        quick_sort(s, l, i - 1);
        quick_sort(s, i + 1, r);
    }
}

int find(int x, int * p) {
    return x == p[x] ? x : (p[x] = find(p[x], p));
}

void funion(int x, int y, int * p) {
    p[find(x, p)] = find(y, p);
}

double kruskal(int n, int m, struct line * l, double r) {
    double ret;

#if DEBUG
    printf("r = %f\n", r);
#endif

    // init
    int * points = malloc(sizeof(int) * n);
    for (size_t i = 0; i < n; i++) {
        points[i] = i;
    }
    for (size_t i = 0; i < m; i++) {
        l[i].d = (double)l[i].a - r * ((double)l[i].b);
    }

    // sort
    quick_sort(l, 0, m - 1);

#if DEBUG
    for (int i = 0; i < m; i++) {
        printf("l[%d] is u = %d, v = %d, a = %d, b = %d, d = %f\n", i, l[i].u, l[i].v, l[i].a, l[i].b, l[i].d);
    }
#endif

    max_a = 0;
    max_b = 0;

    for (int i = 0, j = 0; i < n - 1 && j < m; ++i)
    {
        while (find(l[j].u, points) == find(l[j].v, points)) j++;

        funion(l[j].u, l[j].v, points);
        max_a += l[j].a;
        max_b += l[j].b;

        j++;
    }

    ret = (double)max_a / (double)max_b;

    free(points);

    return ret;
}

int main(){
    int n;
    int m;
    scanf("%d %d",&n,&m);

    struct line * lines = malloc(sizeof(struct line) * m);
    double start_r = 0.0;

    for(int a0 = 0; a0 < m; a0++){
        int u;
        int v;
        int a;
        int b;
        scanf("%d %d %d %d",&u,&v,&a,&b);
        // Write Your Code Here

        if (u <= v) {
            lines[a0].u = u;
            lines[a0].v = v;
        }
        else {
            lines[a0].u = v;
            lines[a0].v = u;
        }
        lines[a0].a = a;
        lines[a0].b = b;

        if (start_r < (double)a/(double)b) {
            start_r = (double)a/(double)b;
            max_a = a;
            max_b = b;
        }
    }

    double ratio = start_r;
    do {
        start_r = ratio;
        ratio = kruskal(n, m, lines, start_r);
    } while(false == fequal(ratio, start_r));

    int step = 2;
    while (step <= max_a && step <= max_b) {
        if (0 == (max_a % step) && (0 == (max_b % step))) {
            max_a /= step;
            max_b /= step;
            step = 2;
        }
        else {
            step ++;
        }
    }

    printf("%d/%d\n", max_a, max_b);

    free(lines);

    return 0;
}
