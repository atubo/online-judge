// https://www.luogu.com.cn/problem/P3628
// [APIO2010]特别行动队

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;

namespace ConvexHullTrick {

    int64_t dp[MAXN];
    int64_t P[MAXN];
    int buf[MAXN];
    int N;
    int A, B, C;

    int64_t Y(int i) {
      return dp[i] - 1LL * B * P[i] + 1LL * A * P[i] * P[i];
    }

    int64_t X(int i) {
      return 2LL * P[i];
    }

    int64_t numer(int k, int j) {
        return Y(j) - Y(k);
    }

    int64_t denom(int k, int j) {
        return X(j) - X(k);
    }

    bool isConvex(int a, int b, int c) {
        return numer(a, b) * denom(b, c) > numer(b, c) * denom(a, b);
    }

    int64_t getDp(int i, int j) {
        return dp[j] + 1LL * A * (P[i] - P[j]) * (P[i] - P[j])
            + 1LL * B * (P[i] - P[j]) + C;
    }

    void runDp() {
        dp[0] = 0;
        int p = 0, q = 0;
        buf[q++] = 0;
        for (int i = 1; i <= N; i++) {
            while (q-p > 1 &&
                numer(buf[p], buf[p+1]) >
                denom(buf[p], buf[p+1]) * A * P[i]) {
              p++;
            }
            dp[i] = getDp(i, buf[p]);
            while (q-p > 1 && !isConvex(buf[q-2], buf[q-1], i)) {
              q--;
            }
            buf[q++] = i;
        }
    }
}

int main() {
  using namespace ConvexHullTrick;
  scanf("%d", &N);
  scanf("%d%d%d", &A, &B, &C);
  for (int i = 1; i <= N; i++) {
    int x;
    scanf("%d", &x);
    P[i] = P[i-1] + x;
  }
  runDp();
  printf("%ld\n", dp[N]);
  return 0;
}
