// https://www.luogu.com.cn/problem/P3947
// 肝活动

#include <bits/stdc++.h>
using namespace std;

struct Song {
  char s[51];
  int t, m;
} S[23];

int dp[1<<22];
int P[1<<22];
int SM[1<<22];

int N, M, T;
int ALL;

void init() {
  memset(dp, -1, sizeof(dp));
  SM[0] = 0;
  for (int s = 1; s <= ALL; s++) {
    int i = 31 - __builtin_clz(s);
    SM[s] = S[i].t + SM[s^(1<<i)];
  }
}

int main() {
  scanf("%d%d%d", &N, &M, &T);
  ALL = (1 << N) - 1;
  int tot = 0;
  for (int i = 0; i < N; i++) {
    scanf("%s%d%d", S[i].s, &S[i].t, &S[i].m);
    tot += S[i].t;
  }
  if (tot > T) {
    printf("No Answer\n");
    return 0;
  }
  init();
  dp[0] = 0;
  for (int s = 0; s < ALL; s++) {
    for (int i = 0; i < N; i++) {
      if ((s >> i) & 1) continue;
      int s2 = s | (1 << i);
      int v = dp[s] + (S[i].m > SM[s2] ? S[i].m - SM[s2] : 0);
      if (dp[s2] == -1 || dp[s2] < v || (dp[s2] == v && P[s2] < i)) {
        dp[s2] = v;
        P[s2] = i;
      }
    }
  }

  if (dp[ALL] < M) {
    printf("No Answer\n");
    return 0;
  }
  printf("%d\n", dp[ALL]);
  int s = ALL;
  vector<int> ret;
  while (s != 0) {
    int i = P[s];
    ret.push_back(i);
    s = s ^ (1 << i);
  }
  for (int i = ret.size()-1; i >= 0; i--) {
    printf("%s\n", S[ret[i]].s);
  }
  return 0;
}
