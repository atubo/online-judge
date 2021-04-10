// https://codeforces.com/problemset/problem/15/E
// E. Triangles

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000009;
const int MAXN = 2000010;
int G[MAXN];
int N;

void build() {
  G[0] = 1;
  for (int i = 1; i <= N/2; i++) {
    G[i] = (2LL * G[i-1] + 3) % MOD;
  }
}

int add(int64_t a, int64_t b) {
  return (a + b) % MOD;
}

int mul(int64_t a, int64_t b) {
  return (a * b) % MOD;
}

int main() {
  scanf("%d", &N);
  build();
  int s = 2;
  int p = 1;
  for (int i = 3; i <= N; i++) {
    if (i <= 4) {
      s = add(s, 2);
      continue;
    }
    int k = (i-3) / 2;
    if (i & 1) {
      p = mul(p, G[k]);
    }
    s = add(s, 2*p);
  }
  printf("%d\n", add(mul(mul(s, s), 2), 2));

  return 0;
}
