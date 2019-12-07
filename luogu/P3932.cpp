// https://www.luogu.com.cn/problem/P3932
// 浮游大陆的68号岛

#include <bits/stdc++.h>
using namespace std;

const int MOD = 19260817;

class FenwickTree {
public:
    // 1-indexed
    FenwickTree(int size): n_(size) {
        tree_ = new int64_t[n_+1]{};
    }

    ~FenwickTree() {
        delete[] tree_;
    }

    void clear() {
        memset(tree_, 0, (n_+1) * sizeof(int64_t));
    }

    // add v to value at x
    void set(int x, int v) {
        while(x <= n_) {
            (tree_[x] += v) %= MOD;
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int64_t get(int x) const {
        int64_t res = 0;
        while(x) {
            (res += tree_[x]) %= MOD;
            x -= (x & -x);
        }
        return res;
    }

    // get result for [x, y]
    int64_t get(int x, int y) const {
      if (x == 0) return get(y);
      return (get(y) + MOD - get(x-1)) % MOD;
    }

private:
    int64_t* tree_;
    const int n_;
};

const int MAXN = 200010;
int N, M;
int X[MAXN];
int A[MAXN];

int64_t mul(int64_t a, int64_t b) {
  return (a * b) % MOD;
}

int64_t sub(int64_t a, int64_t b) {
  return (a + MOD - b) % MOD;
}

int64_t calcLeft(const FenwickTree& ft1, const FenwickTree& ft2,
    int x, int l, int r) {
  return sub(ft1.get(l, r), mul(X[x], ft2.get(l, r)));
}

int64_t calcRight(const FenwickTree& ft1, const FenwickTree& ft2,
    int x, int l, int r) {
  return sub(mul(X[x], ft2.get(l, r)), ft1.get(l, r));
}

int main() {
  scanf("%d%d", &N, &M);
  for (int i = 2; i <= N; i++) {
    int x;
    scanf("%d", &x);
    X[i] = (X[i-1] + x) % MOD;
  }
  for (int i = 1; i <= N; i++) {
    scanf("%d", &A[i]);
    A[i] %= MOD;
  }
  FenwickTree ft1(N), ft2(N);
  for (int i = 1; i <= N; i++) {
    ft1.set(i, (1LL*A[i]*X[i]) % MOD);
    ft2.set(i, A[i]);
  }

  for (int i = 0; i < M; i++) {
    int x, l, r;
    scanf("%d%d%d", &x, &l, &r);
    int64_t ans;
    if (x <= l) {
      ans = calcLeft(ft1, ft2, x, l, r);
    } else if (x >= r) {
      ans = calcRight(ft1, ft2, x, l, r);
    } else {
      ans = (calcRight(ft1, ft2, x, l, x) + calcLeft(ft1, ft2, x, x, r)) % MOD;
    }
    printf("%ld\n", ans);
  }

  return 0;
}
