// https://www.luogu.com.cn/problem/P4495
// [HAOI2018]奇怪的背包

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
const int MOD = 1000000007;
int N, Q, P;
int V[MAXN], W[MAXN];

int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a%b);
}

int mul(int64_t a, int64_t b) {
  a = a % MOD;
  b = b % MOD;
  return (a * b) % MOD;
}

int add(int a, int b) {
  return (a + b) % MOD;
}

class Solution {
 public:
  void factorize(int p) {
    for (int i = 1; i*i <= p; i++) {
      if (p % i == 0) {
        d_.push_back(i);
        if (i * i != p) d_.push_back(p/i);
      }
    }
    sort(d_.begin(), d_.end());
    D_ = d_.size();
  }

  void build() {
    cnt_.resize(D_);
    int maxc = 0;
    for (int i = 0; i < N; i++) {
      int d = gcd(V[i], P);
      int idx = lower_bound(d_.begin(), d_.end(), d) - d_.begin();
      cnt_[idx]++;
      maxc = max(maxc, cnt_[idx]);
    }
    p2_.resize(maxc+1);
    p2_[0] = 1;
    for (int i = 1; i <= maxc; i++) {
      p2_[i] = add(p2_[i-1], p2_[i-1]);
    }
  }

  void solve() {
    vector<vector<int>> dp(D_+1, vector<int>(D_));
    dp[0][D_-1] = 1;
    for (int i = 1; i <= D_; i++) {
      int c = p2_[cnt_[i-1]] - 1;
      for (int j = 0; j < D_; j++) {
        dp[i][j] = add(dp[i][j], dp[i-1][j]);
        int d = gcd(d_[i-1], d_[j]);
        int k = lower_bound(d_.begin(), d_.end(), d) - d_.begin();
        dp[i][k] = add(dp[i][k], mul(dp[i-1][j], c));
      }
    }
    ans_.resize(D_);
    for (int i = 0; i < D_; i++) {
      for (int j = 0; j <= i; j++) {
        if (d_[i] % d_[j] == 0) {
          ans_[i] = add(ans_[i], dp[D_][j]);
        }
      }
    }
  }

  void output() const {
    for (int i = 0; i < Q; i++) {
      int w = gcd(W[i], P);
      int k = lower_bound(d_.begin(), d_.end(), w) - d_.begin();
      printf("%d\n", ans_[k]);
    }
  }
 private:
  vector<int> d_;
  int D_;
  vector<int> cnt_;
  vector<int> p2_;
  vector<int> ans_;
};

int main() {
  scanf("%d%d%d", &N, &Q, &P);
  for (int i = 0; i < N; i++) {
    scanf("%d", &V[i]);
  }
  for (int i = 0; i < Q; i++) {
    scanf("%d", &W[i]);
  }
  Solution solution;
  solution.factorize(P);
  solution.build();
  solution.solve();
  solution.output();
  return 0;
}
