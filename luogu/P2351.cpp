// https://www.luogu.com.cn/problem/P2351
// [SDOI2012]吊灯

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1200010;
int N;
vector<int> P; // factors
int F[MAXN];
int C[MAXN]; // count
int S[MAXN]; // size

void init() {
  for (int i = 1; i <= N; i++) {
    if (N % i == 0) P.push_back(i);
  }
}

void solve(int i) {
  printf("Case #%d:\n", i);
  memset(C, 0, sizeof(C));
  memset(S, 0, sizeof(S));
  for (int u = N; u > 0; u--) {
    int v = F[u];
    S[u]++;
    C[S[u]]++;
    S[v] += S[u];
  }
  for (int s : P) {
    int cnt = 0;
    for (int k = 1; k*s <= N; k++) {
      cnt += C[s*k];
    }
    if (cnt == N/s) {
      printf("%d\n", s);
    }
  }
  for (int u = 2; u <= N; u++) {
    F[u] = (F[u] + 19940105) % (u-1) + 1;
  }
}

int main() {
  scanf("%d", &N);
  init();
  for (int i = 1; i <= N-1; i++) {
    char c;
    scanf("%d%c", &F[i+1], &c);
  }
  for (int i = 1; i <= 10; i++) {
    solve(i);
  }
  return 0;
}
