---
layout: post
title: 数位DP模板
---

### 模板

```c++
// a, b, etc. are prefix determined variables
int dfs(int a, int b, ..., int pos, int d, bool bounded) {
  int& dpEntry = dp[key]; // save because we will update a, b, ...
  bounded = bounded && d == digits[pos];
  if (!bounded && dp[key] != -1) {
    return dp[key];
  }
  // update a, b, etc here
  if (pos == 0) {
    // should be easy to write
  }

  int maxd = (bounded ? digits[pos-1]: 9);
  int ret = 0;
  for (int nextd = 0; nextd <= maxd; nextd++) {
    ret += dfs(a, b, ..., pos-1, nextd, bounded);
  }

  if (!bounded) dpEntry = ret;
  return ret;
}

int main() {
  memset(dp, -1, sizeof(dp));
  // setup digits
  int ans = 0;
  for (int d = 0; d <= digits[n-1]; d++) {
    ans += dfs(a, b, ..., n-1, d, true);
  }
}
```
