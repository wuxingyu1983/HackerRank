#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define DEBUG   0

struct node {
    int val;
    struct node * parent;
    struct node * children;
    struct node * brother;
};

unsigned long long  func(int * t, int start, int end, struct node * p, int k) {
    unsigned long long ret = 0;
    int pos = 0;        // 插入的位置
    int flag = 0;       // 0 - 向左侧延伸，1 - 向右侧延伸

    do {
#if DEBUG
        printf("处理子node, p->val = %d, start = %d, end = %d the t[] is ", p->val, start, end);
#endif
        if (start == end) {
            t[end] = p->val;
            pos = end ++;
            flag = 1;
#if DEBUG
            printf("null\n");
#endif
        }
        else {
            // start < end
            // 计算有几个满足条件的 pair,再插入
#if DEBUG
            for (int i = start; i < end; i ++) {
                printf("%d ", t[i]);
            }
            printf("\n");
#endif
            int min = p->val - k;
            int max = p->val + k;

            int lt;     // 小于 min 最大数的位置
            {
                int llt = start;
                int rlt = end - 1;
                while (llt <= rlt) {
                    int middle = (llt + rlt) / 2;
                    if (t[middle] >= min) {
                        rlt = middle - 1;
                        lt = rlt;
                    }
                    else {
                        llt = middle + 1;
                        lt = llt;
                    }
                }

                while (lt < end && lt >= start && t[lt] >= min) {
                    lt --;
                }
            }

            int bg;     // 大于 max 最小数的位置
            {
                int lbg = start;
                int rbg = end - 1;
                while (lbg <= rbg) {
                    int middle = (lbg + rbg) / 2;
                    if (t[middle] > max) {
                        rbg = middle - 1;
                        bg = rbg;
                    }
                    else {
                        lbg = middle + 1;
                        bg = lbg;
                    }
                }

                while (bg >= start && bg <= (end - 1) && t[bg] <= max) {
                    bg ++;
                }
            }

            if (lt == bg) {
                ret += 0;
#if DEBUG
                printf("lt is %d, bg is %d, add ret is 0\n", lt, bg);
#endif
            }
            else {
                ret += bg - lt - 1;
#if DEBUG
                printf("lt is %d, bg is %d, add ret is %d\n", lt, bg, bg - lt - 1);
#endif
            }

            if (p->val <= t[start]) {
                t[-- start] = p->val;
                pos = start;
                flag = 0;
            }
            else if (p->val > t[end - 1]) {
                t[end] = p->val;
                pos = end ++;
                flag = 1;
            }
            else {
                //  计算 pos
                int left = start;
                int right = end - 1;
                while (left <= right) {
                    int middle = (left + right) / 2;
                    if (t[middle] >= p->val) {
                        right = middle - 1;
                    }
                    else {
                        left = middle + 1;
                    }
                }

                for (pos = right - 1; pos < left && t[pos] < p->val; pos ++) {
                }

                // 移动
                if ((pos - start) < (end - pos)) {
                    // 左移
                    for (int i = start; i < pos; i ++) {
                        t[i - 1] = t[i];
                    }
                    t[pos - 1] = p->val;
                    start --;
                    flag = 0;
                }
                else {
                    // 右移
                    for (int i = end - 1; i >= pos; i --) {
                        t[i + 1] = t[i];
                    }
                    t[pos] = p->val;
                    end ++;
                    flag = 1;
                }
            }
        }
#if DEBUG
        printf("移动后 : ");
        for (int i = start; i < end; i ++) {
            printf("%d ", t[i]);
        }
        printf("\n");
#endif
        // 计算子 node
        if (p->children) {
            ret += func(t, start, end, p->children, k);
        }

        // 还原
        if (0 == flag) {
            for (int i = pos - 1; i > start; i --) {
                t[i] = t[i - 1];
            }
            start ++;
        }
        else {
            for (int i = pos; i < end - 1; i ++) {
                t[i] = t[i + 1];
            }
            end --;
        }
    } while (NULL != (p = p->brother));

    return ret;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    struct node * root = NULL;
    struct node * * nodes = malloc(sizeof(struct node *) * (n + 1));
    memset(nodes, 0, sizeof(struct node *) * (n + 1));

    for (int i = 0; i < n - 1; i ++) {
        int p, c;
        scanf("%d %d", &p, &c);

        struct node * prt = nodes[p];
        if (NULL == prt) {
            prt = malloc(sizeof(struct node));
            memset(prt, 0, sizeof(struct node));
            prt->val = p;
            nodes[p] = prt;
        }

        struct node * cur = nodes[c];
        if (NULL == cur) {
            cur = malloc(sizeof(struct node));
            memset(cur, 0, sizeof(struct node));
            cur->val = c;
            nodes[c] = cur;
        }

        cur->parent = prt;
        cur->brother = prt->children;
        prt->children = cur;

        root = prt;
    }

    // find root
    while (root->parent) {
        root = root->parent;
    }

    unsigned long long ret = 0;
    int * t = malloc(sizeof(int) * 2 * (n + 1));
    memset(t, 0, sizeof(int) * 2 * (n + 1));

    ret = func(t, n, n, root, k);

    printf("%llu\n", ret);

    for (int i = 0; i < n - 1; i ++) {
        if (nodes[i]) {
            free(nodes[i]);
        }
    }
    free(nodes);
    free(t);

    return 0;
}
