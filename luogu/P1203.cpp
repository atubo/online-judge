// https://www.luogu.com.cn/problem/P1203
// [USACO1.1]坏掉的项链Broken Necklace

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 710;
int last[MAXN][2], nxt[MAXN][2];

int N;
int A[MAXN];
int ans1[MAXN], ans2[MAXN];

int main() {
  scanf("%d", &N);
  string s;
  cin >> s;
  for (int i = 0; i < N; i++) {
    if (s[i] == 'b') A[i+1] = A[N+i+1] = 0;
    else if (s[i] == 'r') A[i+1] = A[N+i+1] = 1;
    else A[i+1] = A[N+i+1] = 2;
  }
  memset(last, 0, sizeof(last));
  memset(nxt, 0x7F, sizeof(nxt));
  for (int i = 2*N; i > 0; i--) {
    if (A[i] < 2) {
      nxt[i][A[i]] = i;
      nxt[i][1^A[i]] = nxt[i+1][1^A[i]];
    } else {
      nxt[i][0] = nxt[i+1][0];
      nxt[i][1] = nxt[i+1][1];
    }
  }
  for (int i = 1; i <= 2*N; i++) {
    if (A[i] < 2) {
      last[i][A[i]] = i;
      last[i][1^A[i]] = last[i-1][1^A[i]];
    } else {
      last[i][0] = last[i-1][0];
      last[i][1] = last[i-1][1];
    }
  }
  for (int i = 1; i <= N; i++) {
    int q = (A[i] == 2 ? max(nxt[i][0], nxt[i][1]) : nxt[i][1^A[i]]);
    ans1[i] = min(N, q-i);
  }

  for (int i = N+1; i <= 2*N; i++) {
    int q = (A[i] == 2 ? min(last[i][0], last[i][1]) : last[i][1^A[i]]);
    ans2[i] = min(N, i-q);
  }

  int ans = 0;
  for (int i = 1; i <= N; i++) {
    int x = ans1[i];
    int y = (i==1 ? ans2[2*N] : ans2[N+i-1]);
    ans = max(ans, min(N, x+y));
  }
  printf("%d\n", ans);

  return 0;
}
