假设n个队伍，每个队伍分数分别为 s[1]、s[2] .... s[n]

可能的分数分布要满足以下的2个条件
（1）$$\sum_{x=1}^n s[x] = n\times(n - 1)/2$$
（2）$$\sum_{x_i}^l s[x_i] \geq l\times(l - 1)/2$$，其中$$x_i$$是 1、2、3 ... n 的子串，也就是说长度为l的任一子串的和不小于 $$l\times(l - 1)/2$$

***如何证明？—— TBD***

##解题思路
将s[i]序列分为2部分，not erased 的a[i] 和 erased 的b[i]。条件(2)转换为：

$$\sum_{i=1}^l a[i] + \sum_{i=i}^k b[i] \geq (k + l)\times(k + l - 1)/2$$

=>
$$\sum_{i=1}^l (a[i] - (k + i - 1)) + \sum_{i=1}^k b[i] \geq k\times(k - 1)/2$$

针对特定的k，可以求出最小的$$\sum_{i=1}^l (a[i] - (k + i - 1))$$，表示为exceed[k]。

###STEP 1
针对not erased a[i]排序，检验是否满足条件(2)，计算出所有的exceed[k]。

###STEP 2
针对erased b[i]，引入dp[k][score][sum]数组，表示的是b[i]（排序后的）中前k个元素，都不大于score分数，总和为sum的情况的可能排列数量。具有以下:

(1)前k个中没有出现score分数：dp[k][score][sum] += dp[k][score - 1][sum]
(2)前k个中有出现score分数，又分为出现1个、2个...k个这几种情况。
对于出现i个这种情况：
$$dp[k][score][sum] += C_{m - (k - i)}^i \times dp[k - i][score - 1][sum - i \times score]$$
其中，m是erased b[i]的个数。过程中sum的选择也要满足条件(2)。

所以，最终结果是$$\sum_{score=0}^{n - 1} dp[m][score][sum_{erased}]$$
