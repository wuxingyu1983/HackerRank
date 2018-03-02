#include <cmath>
#include <cstdio>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define DEBUG       0

#define maxsize 100001

struct Task {
    int d;
    int m;
};

bool cmp(const Task &t1, const Task &t2)
{
    return t1.d < t2.d;
}

int treeNode[4*maxsize];
int lazy[4*maxsize];
int arr[maxsize];
vector<int> index_in_sorted;

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
        return INT_MIN;
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

int main() {
    int t, d, m;

    scanf("%d", &t);

    // init segment tree
    for (size_t i = 0; i < t; i++) {
        arr[i] = INT_MIN;
    }
    initializeTreeNode(1,1,t);

    vector<Task> tasks, sorted_tasks;
    tasks.resize(t);
    sorted_tasks.resize(t);
    for (size_t i = 0; i < t; i++) {
        scanf("%d %d", &d, &m);

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



    return 0;
}
