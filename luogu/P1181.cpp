// https://www.luogu.com.cn/problem/P1181
// 数列分段Section I

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N, M;
int A[MAXN];

int main() {
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N; i++) {
    scanf("%d", &A[i]);
  }
  int ans = 0;
  int s = 0;
  for (int i = 0; i < N; i++) {
    if (s + A[i] > M) {
      ans++;
      s = A[i];
      continue;
    }
    s += A[i];
  }
  printf("%d\n", ans+1);

  return 0;
}
