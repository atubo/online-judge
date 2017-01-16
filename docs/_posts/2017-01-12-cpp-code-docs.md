---
layout: post
title: C++ code documentation
---

## Suffix Array

### Code
[SuffixArray.h](https://github.com/atubo/code-snippets/blob/master/cpp/SuffixArray.h)

### Usage:
Let $s(x)$ be the suffix starting at position $x$ and $S_{i, j}$ be the substring of $S$ from $i$ to $j$.

* To build the suffix array

```cpp
    SuffixArray::S = s;
    SuffixArray::buildSA();
    SuffixArray::buildLCP();
```

* `calcLCP(x, y)` returns the length of the longest common prefix of $s(x)$ and $s(y)$.
* `sa[i]`: the starting position of the `i`th suffix in the suffix array.
* `pos[x]`: the rank of $s(x)$ in the suffix array.
* `P[k][i]`: the rank of $S_{i,i+2^k}$


