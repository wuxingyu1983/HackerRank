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

// pdh[point index][distance][height] = point count
int pdh[101][101][101];

void rfn(struct point * parent) {
    if (parent) {
        pdh[parent->index][0][0] = 1;
        struct point * child = parent->child;
        while (child) {
            rfn(child);

            for (size_t d = 0; d <= K; d++) {
                for (size_t h = 0; h < 101; h++) {
                    if (pdh[child->index][d][h]) {
                        if (d < h + 1) {
                            if (0 == pdh[parent->index][h + 1][h + 1]) {
                                pdh[parent->index][h + 1][h + 1] = pdh[child->index][d][h] + 1;
                            }
                            else {
                                pdh[parent->index][h + 1][h + 1] += pdh[child->index][d][h];
                            }

                            if (h + 1 <= K) {
                                if (max < pdh[parent->index][h + 1][h + 1]) {
                                    max = pdh[parent->index][h + 1][h + 1];
                                }
                            }
                        }
                        else {
                            if (0 == pdh[parent->index][d][h + 1]) {
                                pdh[parent->index][d][h + 1] = pdh[child->index][d][h] + 1;
                            }
                            else {
                                pdh[parent->index][d][h + 1] += pdh[child->index][d][h];
                            }

                            if (max < pdh[parent->index][d][h + 1]) {
                                max = pdh[parent->index][d][h + 1];
                            }
                        }
                    }
                }
            }

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
    memset(pdh, 0, sizeof(pdh));

    rfn(root);

    for (size_t i = 1; i <= N; i++) {
        free(points[i]);
    }
    free(points);

    return 0;
}
