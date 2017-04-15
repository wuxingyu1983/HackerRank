# 思路

定义 l[i][j][a] 为经过变化后从i到j位置全部都是字符'a'的最短长度，如不存在全部为'a'的可能则为0.  
那么 l[i][j][] = min(l[i][k][] + l[k + 1][j][])，其中 i <= k < j.  
l[i][j][a] = min(l[i][k][a] + l[k + 1][j][a])，其中 l[i][k][a]、l[k + 1][j][a]都必须大于0  
除了上面的，还有以下可能:  
如果 l[i][k][a]、l[k + 1][j][b]都大于0，我们约定前面者的数目为a[n],后者为b[m]，那么根据规则：  
a[n]b[m] => a[n-1]cb[m-1]  
1.  如果 n > 1, m > 1, a[n]b[m] => a[n-1]cb[m-1] => a[n-2]b[m] 或者 a[n]b[m - 2]  
2.  如果 n = 1, m - 1为奇数时 cb[m-1] => a，m - 1 为偶数时 cb[m-1] => c  
3.  如果 m = 1, n - 1为奇数时 a[n - 1]c => b，n - 1 为偶数时 a[n - 1]c => c  

以上几点综合考虑就能依次算出所有的 i,j 组合的值了，我们最终只关心 0， len - 1 第一个和最后一个的数值。