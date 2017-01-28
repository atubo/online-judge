---
layout: post
title: HDU 3530 Subsequence
---

### [Problem](http://acm.hdu.edu.cn/showproblem.php?pid=3530)

### Solution
Keep to monotonous queues $\textrm{maxq}$ and $\textrm{minq}$ of positions,
where $A[\textrm{maxq}(0)] > A[\textrm{maxq}(1)] > ...$.  At each position $i$,
we keep checking the heads of the queues and popping the leftmost position of
the two if the gap is larger than $k$ because we know when we go to $i+1$, $i+2$, the gap will be even larger.  Then we check the lower bound and update
the answer if necessary.
