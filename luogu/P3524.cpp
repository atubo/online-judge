// https://www.luogu.com.cn/problem/P3524
// [POI2011]IMP-Party

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3010;
int N, M;

bool A[MAXN][MAXN];
bool B[MAXN];

int main() {
  scanf("%d%d", &N, &M);
  for (int i = 0; i < M; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    a--; b--;
    A[a][b] = true;
  }

  for (int i = 0; i < N; i++) {
    if (B[i]) continue;
    for (int j = i+1; j < N; j++) {
      if (!B[j] && !A[i][j]) {
        B[i] = B[j] = true;
        break;
      }
    }
  }

  for (int cnt = 0, i = 0; i < N; i++) {
    if (!B[i]) {
      printf("%d ", i+1);
      if (++cnt == N/3) break;
    }
  }

  return 0;
}
