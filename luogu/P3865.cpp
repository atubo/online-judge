// https://www.luogu.com.cn/problem/P3865
// 【模板】ST表

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int st[MAXN][17];
int R[MAXN];
int N, M;

int main() {
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N; i++) {
    scanf("%d", &st[i][0]);
  }
  for (int d = 1; d < 17; d++) {
    for (int i = 0; i < N; i++) {
      if (i + (1<<d) <= N) {
        st[i][d] = max(st[i][d-1], st[i+(1<<(d-1))][d-1]);
      }
    }
  }
  for (int d = 0; d <= 16; d++) {
    for (int i = (1<<d)+1; i <= min(N, (1 << (d+1))); i++) {
      R[i] = d;
    }
  }
  for (int i = 0; i < M; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    l--; r--;
    int w = r - l + 1;
    int d = R[w];
    printf("%d\n", max(st[l][d], st[r+1-(1<<d)][d]));
  }
  return 0;
}
