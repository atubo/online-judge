// https://www.luogu.com.cn/problem/P1208
// [USACO1.3]混合牛奶 Mixing Milk

#include <bits/stdc++.h>
using namespace std;

int P[1024];
int N, M;

int main() {
  scanf("%d%d", &N, &M);
  for (int i = 0; i < M; i++) {
    int p, a;
    scanf("%d%d", &p, &a);
    P[p] += a;
  }
  int cost = 0;
  for (int i = 0; i <= 1000; i++) {
    int m = min(P[i], N);
    cost += i * m;
    N -= m;
    if (N == 0) break;
  }
  printf("%d\n", cost);
  return 0;
}
