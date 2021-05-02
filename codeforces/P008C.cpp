// https://codeforces.com/problemset/problem/8/C
// Looking for Order

#include <bits/stdc++.h>
using namespace std;

int dp[1<<24];
int next[1<<24];

const int MAXN = 25;
int N;
struct Point {
  int x, y;
} P[MAXN];
int D[MAXN];
int D2[MAXN][MAXN];

int search(int s) {
  if (s == 0) return 0;
  if (dp[s] != -1) return dp[s];
  int& ret = dp[s];
  int& nxt = ::next[s];
  int p = __builtin_ctz(s);
  int s2 = s ^ (1<<p);
  ret = 2*D[p] + search(s2);
  nxt = s2;
  if (s2 != 0) {
    for (int q = p+1; q < N; q++) {
      if ((s2 >> q) & 1) {
        int s3 = s2 ^ (1 << q);
        int t = D[p] + D[q] + D2[p][q] + search(s3);
        if (t < ret) {
          ret = t;
          nxt = s3;
        }
      }
    }
  }
  return ret;
}

void printPath(int s) {
  if (s == 0) return;
  int t = s ^ ::next[s];
  for (int i = 0; i < N; i++) {
    if ((t >> i) & 1) printf("%d ", i+1);
  }
  printf("0 ");
  printPath(::next[s]);
}

int main() {
  memset(dp, -1, sizeof(dp));
  memset(::next, -1, sizeof(::next));
  int xs, ys;
  scanf("%d%d", &xs, &ys);
  scanf("%d", &N);
  const int ALL = (1<<N) - 1;
  for (int i = 0; i < N; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x -= xs;
    y -= ys;
    P[i] = {x, y};
    D[i] = x*x + y*y;
  }
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      int dx = P[i].x - P[j].x;
      int dy = P[i].y - P[j].y;
      D2[i][j] = dx*dx + dy*dy;
    }
  }
  search(ALL);
  printf("%d\n", dp[ALL]);
  printf("0 ");
  printPath(ALL);
  printf("\n");
  return 0;
}
