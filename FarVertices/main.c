#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define DEBUG   1

int N, K, max;

struct vertice {
    int u, v;
};

struct vertice vertices[101];

// phd[point index][height][distance] = point count
int phd[101][101][101];

void rfn(int p, int pp) {
	// 初始化,如果只有该点自己,则 height 和 distance 都为0
	phd[p][0][0] = 1;

	for (size_t i = 1; i < N; i++) {
		// 遍历它的孩子
		if (vertices[i].u == p || vertices[i].v == p) {
			int child = vertices[i].u == p ? vertices[i].v : vertices[i].u;
			if (child != pp) {
				// 处理叶子child的 height 和 distance
				rfn(child, p);

				// 处理parent自己的 height 和 distance
				for (size_t h = 0; h <= K /*&& h <= child->max_height*/; h++) {
					for (size_t d = h; d <= h * 2 /*&& d <= child->max_distance*/ && d <= K; d++){
						if (phd[child][h][d]) {
							int cnt = phd[child][h][d];
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
							for (int ph = K /*parent->max_height*/; ph >= 0; ph --) {
								for (int pd = K /*parent->max_distance*/; pd >= 0; pd --) {
									if (phd[p][ph][pd]) {
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

										int new_cnt = cnt + phd[p][ph][pd];
										if (new_d <= K && phd[p][new_h][new_d] < new_cnt) {
											phd[p][new_h][new_d] = new_cnt;
#if DEBUG
											printf("pdh[%d][%d][%d] is %d\n", p, new_h, new_d, phd[p][new_h][new_d]);
#endif
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
							if (p_d <= K && cnt > phd[p][p_h][p_d]) {
								phd[p][p_h][p_d] = cnt;
#if DEBUG
								printf("pdh[%d][%d][%d] is %d\n", p, p_h, p_d, phd[p][p_h][p_d]);
#endif
								if (p_d <= K && cnt > max) {
									max = cnt;
								}
							}
							/*
							   if (max_h > parent->max_height) {
							   parent->max_height = max_h;
							   }

							   if (max_d > parent->max_distance) {
							   parent->max_distance = max_d;
							   }
							 */
						}
					}
				}
			}
		}
	}
}

int main() {
    scanf("%d %d", &N, &K);

    for (size_t i = 1; i < N; i++) {
        int ui, vi;
        scanf("%d %d", &ui, &vi);

        vertices[i].u = ui;
        vertices[i].v = vi;
    }

    max = 0;
    memset(phd, 0, sizeof(phd));

    rfn(1, 0);

    printf("%d\n", N - max);

    return 0;
}
