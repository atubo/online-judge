// https://www.luogu.com.cn/problem/P4620
// [SDOI2018]荣誉称号

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10000005;
int a[MAXN], b[MAXN], id[MAXN];
int N, K, M;
int64_t f[1<<11][200], v[1<<11][200], cost[1<<11][200];

class Generator {
  unsigned int SA, SB, SC;int p, A, B;
  unsigned int rng61(){
    SA ^= SA << 16;
    SA ^= SA >> 5;
    SA ^= SA << 1;
    unsigned int t = SA;
    SA = SB;
    SB = SC;
    SC ^= t ^ SA;
    return SC;
  }

 public:
  void gen(){
    scanf("%d%d%d%d%u%u%u%d%d", &N, &K, &M, &p, &SA, &SB, &SC, &A, &B);
    K++;
    for(int i = 1; i <= p; i++) {
      scanf("%d%d", &a[i], &b[i]);
      a[i] = a[i] % M;
    }
    for(int i = p + 1; i <= N; i++){
      a[i] = (rng61() % A + 1) % M;
      b[i] = rng61() % B + 1;
    }
  }
};

int T;

void solve() {
  Generator generator;
  generator.gen();
  memset(v, 0, sizeof(v));
  memset(cost, 0, sizeof(cost));
  memset(f, 0x3F, sizeof(f));
  for (int i = 1; i < 1<<K; i++) {
    cost[id[i]=i][a[i]] = b[i];
  }
  for (int i = 1<<K; i <= N; i++) {
    cost[id[i]=id[i>>K]][a[i]] += b[i];
  }
  for (int i = 1; i < 1<<K; i++) {
    for (int j = 0; j < M; j++) {
      for (int k = 0; k < j; k++) {
        v[i][j] += cost[i][k]*(j-k);
      }
      for (int k = j+1; k < M; k++) {
        v[i][j] += cost[i][k] * (j+M-k);
      }
    }
  }
  for (int i = 1<<(K-1); i < 1<<K; i++) {
    for (int j = 0; j < M; j++) {
      f[i][j] = v[i][j];
    }
  }
  for (int i = (1<<(K-1))-1; i > 0; i--) {
    for (int j = 0; j < M; j++) {
      for (int k = 0; k < M; k++) {
        f[i][j] = min(f[i][j], f[i<<1][k]+f[i<<1|1][k]+v[i][(j-k+M)%M]);
      }
    }
  }
  printf("%ld\n", f[1][0]);
  for (int i = 1; i <= N; i++) {
    a[i] = b[i] = 0;
  }
}

int main() {
  scanf("%d", &T);
  while (T--) {
    solve();
  }
  return 0;
}
