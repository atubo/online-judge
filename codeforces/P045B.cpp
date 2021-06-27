// https://codeforces.com/problemset/problem/45/B
// School

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N, M;
int G[MAXN], V[MAXN], B[MAXN], C[MAXN];

int main() {
  scanf("%d%d", &N, &M);
  for (int i = 1; i <= N; i++) scanf("%d", &G[i]);
  for (int i = 1; i <= M; i++) scanf("%d", &V[i]);
  for (int i = 1; i <= M; i++) scanf("%d", &B[i]);
  int last = 0;
  for (int i = 1; i <= M; i++) {
    int ans = 0;
    for (int j = (V[i] + last - 1) % N + 1; C[j] < B[i]; j = G[j]) {
      ans += !C[j];
      C[j] = B[i];
      B[i]--;
    }
    printf("%d\n", ans);
    last = ans;
  }
  return 0;
}
