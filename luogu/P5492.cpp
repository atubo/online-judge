// https://www.luogu.com.cn/problem/P5492
// [PKUWC2018]随机算法

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const int P = 998244353;
int N, M;
int incident[MAXN];
int inv[MAXN+1];
bool ok[1<<MAXN];
int cnt[1<<MAXN], sz[1<<MAXN], maxs;
int f[1<<MAXN];

int main() {
  scanf("%d%d", &N, &M);
  for (int i = 0; i < M; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--; y--;
    incident[x] |= (1 << y);
    incident[y] |= (1 << x);
  }
  const int ALL = (1<<N) - 1;
  ok[0] = true;
  for (int s = 1; s <= ALL; s++) {
    int v = __builtin_ctz(s);
    int s2 = s ^ (1<<v);
    if (ok[s2]) ok[s] = !(s2 & incident[v]);
    cnt[s] = sz[s] = __builtin_popcount(s);
    if (ok[s]) maxs = max(maxs, sz[s]);
    for (int i = 0; i < N; i++) {
      if (s & incident[i]) cnt[s]++;
    }
  }

  f[0] = inv[1] = 1;
  for (int i = 2; i <= N; i++) {
    inv[i] = 1LL * (P - P/i) * inv[P%i] % P;
  }

  int ans = 0;
  for (int s = 1; s <= ALL; s++) {
    if (!ok[s]) continue;
    int t = s;
    while (t > 0) {
      int v = __builtin_ctz(t);
      int s2 = s ^ (1<<v);
      f[s] = (1LL * f[s2] * inv[N-cnt[s2]] + f[s]) % P;
      t = t ^ (1<<v);
    }
    if (sz[s] == maxs) ans = (ans + f[s]) % P;
  }
  printf("%d\n", ans);
  return 0;
}
