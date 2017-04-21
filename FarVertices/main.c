#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int N, K, max;

struct point {
    int index;
    struct point * child;
    struct point * brother;
    struct point * parent;
};

// phd[point index][height][distance] = point count
int phd[101][101][101];

void rfn(struct point * parent) {
    if (parent) {
        struct point * child = parent->child;
        while (child) {
            rfn(child);

            child = child->brother;
        }
    }
}

int main() {
    scanf("%d %d", &N, &K);

    struct point * * points = malloc(sizeof(struct point *) * (N + 1));
    memset(points, 0, sizeof(struct point *) * (N + 1));

    for (size_t i = 1; i < N; i++) {
        int ui, vi;
        scanf("%d %d", &ui, &vi);

        struct point * up = points[ui];
        if (!up) {
            up = malloc(sizeof(struct point));
            memset(up, 0, sizeof(struct point));
            up->index = ui;
            points[ui] = up;
        }

        struct point * vp = points[vi];
        if (!vp) {
            vp = malloc(sizeof(struct point));
            memset(vp, 0, sizeof(struct point));
            vp->index = vi;
            points[vi] = vp;
        }

        vp->brother = up->child;
        up->child = vp;
        vp->parent = up;
    }

    // find root
    struct point * root = points[1];
    while (root->parent) {
        root = root->parent;
    }

    max = 0;
    memset(phd, 0, sizeof(phd));

    rfn(root);

    printf("%d\n", N - max);

    for (size_t i = 1; i <= N; i++) {
        free(points[i]);
    }
    free(points);

    return 0;
}
