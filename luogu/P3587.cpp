// https://www.luogu.com.cn/problem/P3587
// [POI2015]POD

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010, P1 = 200019, P2 = 200010, mod1 = 1e9+7, mod2 = 1e9+9;
struct Node {
  int id;
  int64_t hash1, hash2;
  bool operator < (const Node& other) const {
    if (hash1 != other.hash1) return hash1 < other.hash1;
    if (hash2 != other.hash2) return hash2 < other.hash2;
    return id < other.id;
  }
} T[MAXN];;

int A[MAXN], L[MAXN], C[MAXN];
int64_t S1[MAXN], S2[MAXN];

int N, K;

int main() {
  scanf("%d%d", &N, &K);
  for (int i = 1; i <= N; i++) {
    scanf("%d", &A[i]);
  }
  S1[0] = S2[0] = 1;
  for (int i = 1; i <= N; i++) {
    S1[i] = S1[i-1] * P1 % mod1;
    S2[i] = S2[i-1] * P2 % mod2;
  }
  for (int i = 1; i <= N; i++) {
    L[A[i]] = i;
  }

  int64_t h1 = 0, h2 = 0;
  for (int i = 1; i <= N; i++) {
    int x = A[i];
    C[x]++;
    h1 = (h1 + S1[x]) % mod1;
    h2 = (h2 + S2[x]) % mod2;
    if (L[x] == i) {
      h1 = (h1 - S1[x]*C[x]%mod1 + mod1) % mod1;
      h2 = (h2 - S2[x]*C[x]%mod2 + mod2) % mod2;
    }
    T[i] = Node{i, h1, h2};
  }
  sort(T+1, T+N+1);

  int64_t cnt = 0;
  int mid = (N + 1) / 2;
  int ans = INT_MAX;

  int p = 1;
  while (p <= N) {
    int q = p + 1;
    while (q <= N && T[q].hash1 == T[p].hash1 && T[q].hash2 == T[p].hash2) {
      q++;
    }
    cnt += 1LL * (q - p) * (q - p -1 ) / 2;
    for (int l = p, r = p; r < q; r++) {
      while (l < r && T[r].id - T[l].id >= mid) l++;
      int t = abs(N - 2*(T[r].id - T[l].id));
      if (l > p) {
        t = min(t, abs(N - 2*(T[r].id - T[l-1].id)));
      }
      ans = min(ans, t);
    }

    p = q;
  }
  printf("%ld %d\n", cnt, ans);

  return 0;
}
