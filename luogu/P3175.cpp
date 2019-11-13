// https://www.luogu.org/problem/P3175
// [HAOI2015]按位或

#include <bits/stdc++.h>
using namespace std;

const int MAXN = (1<<20)+10;
int N;
double P[MAXN];

int main() {
  scanf("%d", &N);
  const int U = (1<<N);
  const int ALL = U - 1;
  for (int i = 0; i < U; i++) {
    scanf("%lf", &P[i]);
  }
  for (int i = 0; i < N; i++) {
    for (int s = 0; s < U; s++) {
      if (s >> i & 1) P[s] += P[s ^ (1<<i)];
    }
  }

  double ans = 0;
  for (int s = 1; s < U; s++) {
    if (1-P[ALL^s] < 1e-8) {
      printf("INF\n");
      return 0;
    }
    int f = __builtin_popcount(s) & 1 ? 1 : -1;
    ans += 1/(1 - P[ALL^s]) * f;
  }
  printf("%.10lf\n", ans);
  
  return 0;
}
