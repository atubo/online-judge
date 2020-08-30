// https://www.luogu.com.cn/problem/P1232
// [NOI2013]树的计数

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200010;
int n, dfs[MAXN], f[MAXN], pos[MAXN], fix[MAXN], s[MAXN];
bool x[MAXN];

void lock(int l, int r) {
  // fix range [l, r)
  fix[l]++;
  fix[r]--;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &dfs[i]);
  }
  for (int i = 0; i < n; i++) {
    int t;
    scanf("%d", &t);
    f[t] = i;
  }
  for (int i = 0; i < n; i++) {
    dfs[i] = f[dfs[i]];
    pos[dfs[i]] = i;
  }
  x[0] = 1;
  lock(0, 1);
  for (int i = 0; i < n-1; i++) {
    if (pos[i] > pos[i+1]) x[i] = true;
  }
  s[0] = 1;
  for (int i = 1; i < n-1; i++) {
    s[i] = s[i-1] + x[i];
  }
  for (int i = 0; i < n-1; i++) {
    if (dfs[i] < dfs[i+1]) {
      int sum = s[dfs[i+1]-1] - (dfs[i] == 0 ? 0 : s[dfs[i]-1]);
      if (sum) lock(dfs[i], dfs[i+1]);
    }
  }
  int ps = 0;
  double ans = 0;
  for (int i = 0; i < n-1; i++) {
    ps += fix[i];
    if (ps) ans += x[i];
    else ans += 0.5;
  }
  ans++;
  printf("%.3f\n", floor(ans * 100 + 0.5) / 100);

  return 0;
}
