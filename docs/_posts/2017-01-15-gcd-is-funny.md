---
layout: post
title: HDU 5902 GCD is funny
---

### [Problem](http://acm.hdu.edu.cn/showproblem.php?pid=5902)

### 解法
实际上就是要求 $A$ 的*真子集* 有哪些不同的 $\gcd$.
我们先计算所有大小为2的真子集的 $\gcd$ 集合，再由此出发计算
所有大小为3的真子集的新的 $\gcd$ 集合，直到 $N-1$ 为止。

奇怪的是用local vector 会WA, 用全局数组就AC了?!
