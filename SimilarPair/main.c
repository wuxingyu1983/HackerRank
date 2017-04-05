#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

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
        if (start == end) {
            t[end] = p->val;
            pos = end ++;
            flag = 1;
        }
        else {
            // start < end
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

            }
        }

        // 还原
        
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
