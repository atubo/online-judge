// https://www.luogu.com.cn/problem/P3737
// [HAOI2014]遥感监测

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
int N, R;
int dp[MAXN];
struct Range {
  Range(double l, double r) : x1(l), x2(r) {}
  double x1, x2;
  bool operator < (const Range& other) const {
    if (x1 != other.x1) return x1 < other.x1;
    return x2 < other.x2;
  }
};

int main() {
  scanf("%d%d", &N, &R);
  vector<Range> ranges;
  for (int i = 0; i < N; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    if (y == R) ranges.push_back(Range{1.0*x, 1.0*x});
    else {
      double dx = sqrt(R*R - y*y);
      ranges.push_back(Range{x-dx, x+dx});
    }
  }
  sort(ranges.begin(), ranges.end());
  for (int i = N-1; i >= 0; i--) {
    int mx = 0;
    for (int j = i+1; j < N; j++) {
      if (ranges[i].x2 < ranges[j].x1) {
        mx = max(mx, dp[j]);
      }
    }
    dp[i] = 1 + mx;
  }
  int ans = 0;
  for (int i = 0; i < N; i++) {
    ans = max(ans, dp[i]);
  }
  printf("%d\n", ans);
  return 0;
}
