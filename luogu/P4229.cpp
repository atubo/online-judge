// https://www.luogu.com.cn/problem/P4229
// 某位歌姬的故事

#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXQ = 512;
const int inf = 0x3f3f3f3f;
struct Restriction {
  int l, r, m;
} R[MAXQ];

int qpow(int x, int n) {
  int ret = 1;
  while (n) {
    if (n & 1) ret = (1LL * ret * x) % MOD;
    x = (1LL * x * x) % MOD;
    n >>= 1;
  }
  return ret;
}

int Q, A;
int pos[2*MAXQ], val[MAXQ], v[2*MAXQ], w[2*MAXQ], sum[2*MAXQ];
int lim[2*MAXQ];
int dp[2*MAXQ][2*MAXQ];
int npos;

int solve(int x) {
  int k = 0;
  sum[0] = 0;
  for (int i = 1; i <= npos; i++) {
    if (v[i] == x) w[++k] = i;
    sum[i] = k;
  }
  memset(lim, 0, sizeof(lim));
  for (int i = 0; i < Q; i++) {
    if (R[i].m == x) {
      if (sum[R[i].r-1] - sum[R[i].l-1] == 0) {
        return -1;
      }
      int r = lower_bound(w+1, w+1+k, R[i].r) - w - 1;
      int l = lower_bound(w+1, w+1+k, R[i].l) - w;
      lim[r] = max(lim[r], l);
    }
  }
  for (int i = 1; i <= k; i++) {
    lim[i] = max(lim[i], lim[i-1]);
  }
  dp[0][0] = 1;
  for (int i = 1; i <= k; i++) {
    dp[i][i] = 0;
    int a = qpow(x-1, pos[w[i]+1] - pos[w[i]]);
    int b = qpow(x, pos[w[i]+1] - pos[w[i]]);
    for (int j = 0; j < i; j++) {
      if (j >= lim[i]) dp[i][j] = 1LL * dp[i-1][j] * a % MOD;
      else dp[i][j] = 0;
      dp[i][i] = (dp[i][i] + 1LL*dp[i-1][j]*((b-a+MOD)%MOD)%MOD) % MOD;
    }
  }
  int ans = 0;
  for (int i = 0; i <= k; i++) {
    ans = (ans + dp[k][i]) % MOD;
  }
  return ans;
}

void work() {
  int n;
  scanf("%d%d%d", &n, &Q, &A);
  pos[1] = 1, pos[2] = n+1;
  for (int i = 0; i < Q; i++) {
    int l, r, m;
    scanf("%d%d%d", &l, &r, &m);
    pos[2*i+3] = l;
    pos[2*i+4] = r+1;
    val[i] = m;
    R[i] = {l, r+1, m};
  }
  sort(pos+1, pos+2*Q+3);
  npos = unique(pos+1, pos+2*Q+3) - pos - 1;
  sort(val, val+Q);
  int nval = unique(val, val+Q) - val;
  memset(v, 0x3f, sizeof(v));
  for (int i = 0; i < Q; i++) {
    R[i].l = lower_bound(pos, pos+npos, R[i].l) - pos;
    R[i].r = lower_bound(pos, pos+npos, R[i].r) - pos;
    for (int j = R[i].l; j < R[i].r; j++) {
      v[j] = min(v[j], R[i].m);
    }
  }
  int ans = 1;
  for (int i = 0; i < nval; i++) {
    int x;
    if ((x = solve(val[i])) != -1) {
      ans = 1LL * ans * x % MOD;
    } else {
      printf("0\n");
      return;
    }
  }

  for (int i = 1; i < npos; i++) {
    if (v[i] == inf) {
      ans = 1LL * ans * qpow(A, pos[i+1] - pos[i]) % MOD;
    }
  }
  printf("%d\n", ans);
}

int T;

int main() {
  scanf("%d", &T);
  while (T--) {
    work();
  }
  return 0;
}
