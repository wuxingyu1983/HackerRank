###条件

战士数目n和查询次数q
$$1\leq n,q \leq 2 \times 10^5$$
极端请的情况，2支队伍，查询中一半是 1 p x 操作，另一半是 2 x y 操作，按照规则，时间复杂度是 $O(10^{10})$，失败！

###思路
2支队伍按照 strength 倒序排序，假如某一轮次：
team1：第$index_1$个战士，他的$strength_1$
team2：第$index_2$个战士，他的$strength_2$

只要能够知道 team1 $index_1$后面还有几个$strength_1$的战士，team2 $index_2$后面还有几个$strength_2$的战士，就可以在该轮次后得到新的$index_1^{'}, strength_1^{'}$和$index_2^{'}, strength_2^{'}$
其中，$$strength_1 > strength_1^{'}或strength_2 > strength_2^{'}$$
所以对于一次比赛来说，某支队伍每一轮的战士为$s_1,s_2,...s_l$,每一个战士的s都不一样，$\sum_{i=1}^l {s_i} \approx 10^5$,所以每次比赛只需要 $O(10^2)$轮次就能见分晓，整个比赛的复杂度降为了$O(10^7)$。

接下来就是如何高效的找到index对应的战士的strength以及后面还有几个该strength的战士。
对于战士按照strength降序排序，利用平衡二叉树，底层叶子记录了战士的strength以及具有该strength的个数，其父节点记录左右子节点的战士个数和。这样子求第index个战士的相关信息就是一个从顶点到叶子节点查找的过程，时间复杂度为$\log_2 10^5$。

