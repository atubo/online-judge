// https://codeforces.com/problemset/problem/97/C
// Winning Strategy

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
int N;
double P[MAXN];

int main() {
  scanf("%d", &N);
  for (int i = 0; i <= N; i++) {
    scanf("%lf", &P[i]);
  }
  double ans = 0;
  if ((N & 1) == 0) {
    ans = P[N/2];
  }
  for (int p = 0; p <= (N-1)/2; p++) {
    int x = N - 2*p;
    for (int q = N/2+1; q <= N; q++) {
      int y = 2*q - N;
      ans = max(ans, (y * P[p] + x * P[q]) / (x + y));
    }
  }
  printf("%.10lf\n", ans);

  return 0;
}
