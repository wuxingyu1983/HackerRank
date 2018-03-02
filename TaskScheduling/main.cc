#include <cmath>
#include <cstdio>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define DEBUG       1

#define maxsize 100001
#define minvalue -100000001

struct Task {
    int d;
    int m;
};

bool cmp(const Task &t1, const Task &t2)
{
    return t1.d < t2.d;
}

int t;
int treeNode[4*maxsize];
int lazy[4*maxsize];
int arr[maxsize];
vector<int> index_in_sorted;
int curr_min = minvalue;

void initializeTreeNode(int nodeNumber,int start,int end){

    int mid,left,right;
    if(start==end){
        treeNode[nodeNumber] = arr[start]; // intialize leaf treeNode to the array value.
        return ;
    }

    mid = (start + end) / 2;
    left = 2*nodeNumber;
    right = 2*nodeNumber + 1;

    initializeTreeNode(left,start,mid);
    initializeTreeNode(right,mid+1,end);

    treeNode[nodeNumber] = max(treeNode[left], treeNode[right] );  // for finding minimum value

    return ;
}

void update(int nodeNumber, int start, int end, int l, int r, int value){

    int mid,left,right;
    if(lazy[nodeNumber]!=0){
        treeNode[nodeNumber] += lazy[nodeNumber];
        if(start!=end){
            lazy[nodeNumber*2] += lazy[nodeNumber];
            lazy[nodeNumber*2 + 1] += lazy[nodeNumber];
        }
        lazy[nodeNumber] = 0;
    }
    if(end<l || start > r)
        return ;
    if( start >=l && end <= r ){
        treeNode[nodeNumber] += value;
        if(start!=end){
            lazy[nodeNumber*2] += value;
            lazy[nodeNumber*2 + 1] += value;
        }
        return;
    }

    mid = (start + end) / 2;
    left = nodeNumber*2;
    right = nodeNumber*2 + 1;

    update(left,start,mid,l,r,value);
    update(right,mid+1,end,l,r,value);

    treeNode[nodeNumber] = max(treeNode[left], treeNode[right] );
    return;
}

int query(int nodeNumber, int start, int end, int l, int r){

    int mid,left,right,q1,q2;
    if(end<l || start > r)
        return curr_min;
    if(lazy[nodeNumber]!=0){

        treeNode[nodeNumber] +=  lazy[nodeNumber];

        if(start!=end){
            lazy[nodeNumber*2] += lazy[nodeNumber];
            lazy[nodeNumber *2 +1] += lazy[nodeNumber];
        }
        lazy[nodeNumber] = 0;
    }
    if( start >=l && end <= r )
        return treeNode[nodeNumber];

    mid = (start + end) / 2;
    left = nodeNumber*2;
    right = nodeNumber*2 + 1;

    q1 = query(left,start,mid,l,r);
    q2 = query(right,mid+1,end,l,r);
    return max(q1,q2);
}

// get pre lateness
int getPreLatenessIndex(int l, int r) {
    int ret = 0;
    int pre = curr_min;

    pre = query(1, 1, t, l, r);
    if (curr_min < pre) {
        while (true) {
            if (l == r) {
                ret = l;
                break;
            }
            else if (1 == (r - l)) {
                pre = query(1, 1, t, r, r);
                if (curr_min < pre) {
                    ret = r;
                }
                else {
                    ret = l;
                }
                break;
            }
            else {
                pre = query(1, 1, t, l + (r - l) / 2, r);
                if (curr_min < pre) {
                    l += (r - l) / 2;
                }
                else {
                    r = l + (r - l) / 2 - 1;
                }
            }
        }
    }

    return ret;
}

int main() {
#if DEBUG
    FILE * fp = fopen("input.txt", "r");
    FILE * fp_out = fopen("output.txt", "w");
#endif

    int d, m;
#if DEBUG
    fscanf(fp, "%d", &t);
#else
    scanf("%d", &t);
#endif

    // init segment tree
    for (size_t i = 0; i <= t; i++) {
        arr[i] = curr_min;
    }
    initializeTreeNode(1,1,t);

    vector<Task> tasks, sorted_tasks;
    tasks.resize(t);
    sorted_tasks.resize(t);
    for (size_t i = 0; i < t; i++) {
#if DEBUG
        fscanf(fp, "%d %d", &d, &m);
#else
        scanf("%d %d", &d, &m);
#endif

        tasks[i].d = d;
        tasks[i].m = m;

        sorted_tasks[i].d = d;
        sorted_tasks[i].m = m;
    }

    // sort sorted_tasks
    sort(sorted_tasks.begin(), sorted_tasks.end(), cmp);

    // get sorted index
    index_in_sorted.resize(t, 0);
    vector<int> flags;
    flags.resize(t, 0);
    for (size_t i = 0; i < t; i++) {
        vector<Task>::iterator find = lower_bound(sorted_tasks.begin(), sorted_tasks.end(), tasks[i], cmp);
        if (0 == flags[find - sorted_tasks.begin()]) {
            index_in_sorted[i] = find - sorted_tasks.begin();
            flags[find - sorted_tasks.begin()] = find - sorted_tasks.begin() + 1;
        }
        else {
            index_in_sorted[i] = flags[find - sorted_tasks.begin()];
            flags[find - sorted_tasks.begin()] ++;
        }
    }

    for (size_t i = 0; i < t; i++) {
        // start from 1
        int index_in_stree = index_in_sorted[i] + 1;

        // get pre lateness
        int pre_index = getPreLatenessIndex(1, index_in_stree - 1);

        // calc current sorted task lateness
        int curr = query(1, 1, t, index_in_stree, index_in_stree);
        int new_value;
        if (0 == pre_index) {
            new_value = tasks[i].m - tasks[i].d - curr;
        }
        else {
            new_value = query(1, 1, t, pre_index, pre_index) + sorted_tasks[pre_index - 1].d + tasks[i].m - tasks[i].d - curr;
        }
//        int max = query(1, 1, t, 1, t);
        update(1, 1, t, index_in_stree, t, new_value);

//        max = query(1, 1, t, 1, t);
        // update after current sorted task lantenss + m
        update(1, 1, t, index_in_stree + 1, t, tasks[i].m - new_value);
        int now = query(1, 1, t, index_in_stree, index_in_stree);

        if (index_in_stree + 1 < t) {
            curr_min += tasks[i].m;
        }

        // get max lateness
        int max = query(1, 1, t, 1, t);
        max = max > 0 ? max : 0;

#if DEBUG
        fprintf(fp_out, "%d\n", max);
#else
        printf("%d\n", max);
#endif
    }

#if DEBUG
    fclose(fp);
    fclose(fp_out);
#endif

    return 0;
}
