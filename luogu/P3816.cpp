// https://www.luogu.com.cn/problem/P3816
// [FJOI2017]树的平均路长问题

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30010;
const int MAXH = 16;
int N = 30000;
// dp1 - max node number, dp2 - min node number
// 0 - red, 1 - black
int dp1[2][MAXH], dp2[2][MAXH];
// dp3 - max length
int dp3[2][MAXN][MAXH];
int ans[MAXN];

void solve(int n, int c) {
  for (int h = 0; h < MAXH; h++) {
    if (dp1[c][h] < n) continue;
    if (dp2[c][h] > n) break;
    int& ret = dp3[c][n][h];
    if (c == 0) {
      int n2 = max(dp2[1][h], n-1-dp1[1][h]);
      int n1 = n-1-n2;
      if (dp3[1][n1][h] >= 0 && dp3[1][n2][h] >= 0) {
        ret = max(ret, dp3[1][n1][h] + dp3[1][n2][h] + n);
      }
    } else {
      for (int c1 = 0; c1 < 2; c1++) {
        for (int c2 = 0; c2 < 2; c2++) {
          if (dp2[c1][h-1] + dp2[c2][h-1] > n-1) continue;
          if (dp1[c1][h-1] + dp1[c2][h-1] < n-1) continue;
          int n2 = max(dp2[c2][h-1], n-1-dp1[c1][h-1]);
          int n1 = n-1-n2;
          if (dp3[c1][h-1] >= 0 && dp3[c2][n2][h-1] >= 0) {
            ret = max(ret, dp3[c1][n1][h-1] + dp3[c2][n2][h-1] + n);
          }
        }
      }
    }
    ans[n] = max(ans[n], ret);
  }
}

void build() {
  dp1[0][0] = 1;
  dp1[1][0] = 0;
  for (int h = 1; h < MAXH; h++) {
    dp1[1][h] = 1 + dp1[0][h-1]*2;
    dp1[0][h] = 1 + dp1[1][h]*2;
  }


  dp2[0][0] = 1;
  dp2[1][0] = 0;
  for (int h = 1; h < MAXH; h++) {
    dp2[1][h] = 1 + dp2[1][h-1]*2;
    dp2[0][h] = 1 + dp2[1][h]*2;
  }

  memset(dp3, 0xFF, sizeof(dp3));
  dp3[0][0][0] = dp3[1][0][0] = 0;
  for (int n = 1; n <= N; n++) {
    solve(n, 1);
    solve(n, 0);
  }

  while (true) {
    int n;
    scanf("%d", &n);
    if (n > 0) {
      printf("%d\n", ans[n]);
    } else {
      printf("0");
      break;
    }
  }
}

int main() {
  build();
  return 0;
}
