---
layout: page
title: Journal
---

<p class="message">
Journal of the problems I have worked on
</p>

### 01/19
* [洛谷P2597]  [ZJOI2012]灾难： 由无环有向图求出“灭绝树”，
见[这里](http://fanhq666.blog.163.com/blog/static/8194342620124274154996/).

### 01/18
* [Codeforces 609E] 与[洛谷P1967]类似，求最小生成树两结点间路径
的边权最大值。
* [POJ 1330] LCA模板题。
* [POJ 3368] 可将 $(a, a, a, b, b, c, c...)$ 转化成    $(1,2,3,1,2,1,2...)$ 的形式,再用RMQ解。注意左端点需要特殊处理。
* [BZOJ 1787] 紧急集合 容易证明集合点必为其中两点的LCA，
可枚举求解。

### 01/17
* [洛谷P1967] 货车运输： 先求出最大生成树，再用倍增LCA的方法求出
任意两结点间路径的边权最小值。

### 01/16
* [HDU 5902] [GCD is funny]({{ site.baseurl }}{% post_url  2017-01-15-gcd-is-funny %})
* [51nod 1290] Counting diff pairs: 莫队算法，直接用pb_ds tree
会TLE，离散化后用BIT解。
