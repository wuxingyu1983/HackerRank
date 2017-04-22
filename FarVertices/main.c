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
    int max_height;         // 以该点为root的树的最大高度
    int max_distance;         // 以该点为root的树的最大距离
};

// phd[point index][height][distance] = point count
int phd[101][101][101];

void rfn(struct point * parent) {
    if (parent) {
        // 初始化,如果只有该点自己,则 height 和 distance 都为0
        phd[parent->index][0][0] = 1;

        struct point * child = parent->child;
        while (child) {
            // 处理叶子child的 height 和 distance
            rfn(child);

            // 处理parent自己的 height 和 distance
            for (size_t h = 0; h <= K && h <= child->max_height; h++) {
                for (size_t d = h; d <= h * 2 && d <= child->max_distance && d <= K; d++){
                    if (phd[child->index][h][d]) {
                        int cnt = phd[child->index][h][d];
                        int p_h, p_d;  // 该 child 加入到 parent 后对应的 height 和 distance
                        p_h = h + 1;
                        if (h + 1 > d) {
                            p_d = h + 1;
                        }
                        else {
                            p_d = d;
                        }

                        // 遍历 parent 已经有的情况,计算新的
                        int max_h = p_h, max_d = p_d;
                        for (int ph = parent->max_height; ph >= 0; ph --) {
                            for (int pd = parent->max_distance; pd >= 0; pd --) {
                                if (phd[parent->index][ph][pd]) {
                                    int new_h, new_d;

                                    if (p_h > ph) {
                                        new_h = p_h;
                                    }
                                    else {
                                        new_h = ph;
                                    }

                                    new_d = p_h + ph;
                                    if (new_d > p_d && new_d > ph) {
                                    }
                                    else if (p_d > pd) {
                                        new_d = p_d;
                                    }
                                    else {
                                        new_d = pd;
                                    }

                                    int new_cnt = cnt + phd[parent->index][ph][pd];
                                    if (phd[parent->index][new_h][new_d] < new_cnt) {
                                        phd[parent->index][new_h][new_d] = new_cnt;
                                        if (new_d <= K && new_cnt > max) {
                                            max = new_cnt;
                                        }
                                    }

                                    if (new_h > max_h) {
                                        max_h = new_h;
                                    }

                                    if (new_d > max_d) {
                                        max_d = new_d;
                                    }
                                }
                            }
                        }

                        // 处理 自己
                        if (cnt > phd[parent->index][p_h][p_d]) {
                            phd[parent->index][p_h][p_d] = cnt;
                            if (p_d <= K && cnt > max) {
                                max = cnt;
                            }
                        }

                        if (max_h > parent->max_height) {
                            parent->max_height = max_h;
                        }

                        if (max_d > parent->max_distance) {
                            parent->max_distance = max_d;
                        }
                    }
                }
            }

            // 处理下一个child
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
