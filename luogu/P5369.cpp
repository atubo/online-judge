// https://www.luogu.com.cn/problem/P5369
// [PKUSC2018]最大前缀和

#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
int sm[1<<20], f[2][1<<20], g[1<<20];
int N;
int A[20];

int add(int64_t a, int64_t b) {
  return (a + b) % MOD;
}

int mul(int64_t a, int64_t b) {
  return (a * b) % MOD;
}

int main() {
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    scanf("%d", &A[i]);
  }
  int ALL = (1 << N) - 1;
  for (int s = 0; s <= ALL; s++) {
    for (int j = 0; j < N; j++) {
      if ((s >> j) & 1) {
        sm[s] += A[j];
      }
    }
  }
  g[0] = 1;
  for (int s = 0; s <= ALL; s++) {
    for (int j = 0; j < N; j++) {
      if (((s >> j) & 1) == 0) {
        int s2 = s | (1<<j);
        if (sm[s2] < 0) {
          g[s2] = add(g[s2], g[s]);
        }
      }
    }
  }

  f[1][0] = 1;
  for (int s = 0; s <= ALL; s++) {
    for (int j = 0; j < N; j++) {
      if (((s >> j) & 1) == 0) {
        int s2 = s | (1<<j);
        if (sm[s2] < 0) {
          f[0][s2] = add(f[0][s2], f[1][s]);
        } else {
          f[1][s2] = add(f[1][s2], f[1][s]);
        }
      }
    }
  }

  int ans = 0;
  for (int s = 0; s <= ALL; s++) {
    ans = add(ans, mul(mul(add(f[0][s], f[1][s]), (sm[s]%MOD+MOD)%MOD), g[ALL^s]));
  }
  printf("%d\n", ans);

  return 0;
}
