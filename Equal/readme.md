# 思路

* 每一轮分配1、2、5个给全部的人员除了其中的一员，相当于针对该人员减少1、2、5，其余的都不变；
* 所以该题目转变为：求最少的轮次，使得所有人员的巧克力数目减少到同一个数目，分两种情况：
  * 所有人员的巧克力数都减少到最初状态中最小的数目；
  * 所有人员的巧克力数都减少到最初状态中最小的数目 - 1 或者 - 2，例如：
    > 初始状态：[1 5 5]
    > round1 : 第1个减小1 -> [0 5 5]
    > round2 : 后两个减少5 -> [0 0 0]
