// https://www.luogu.com.cn/problem/P3646
// [APIO2015]巴厘岛的雕塑

#include <bits/stdc++.h>
using namespace std;

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
            tree_[x] += v;
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int64_t get(int x) const {
        int64_t res = 0;
        while(x) {
            res += tree_[x];
            x -= (x & -x);
        }
        return res;
    }

    // get result for [x, y]
    int64_t get(int x, int y) const {
        return get(y) - (x > 1 ? get(x-1) : 0);
    }

    // index of first element with cumulative sum >= x
    int lowerBound(int64_t x) {
        int clz = __builtin_clz(n_);
        int idx = 0, mask = 1 << (31 - clz);     // first power of 2 <= n_
        while (mask) {
            int t = idx + mask;
            if (t <= n_ && x > tree_[t]) {
                idx = t;
                x -= tree_[t];
            }
            mask >>= 1;
        }
        return idx+1;
    }

    int upperBound(int64_t x) {
        int p = lowerBound(x);
        if (p <= n_ && get(p) == x) p = lowerBound(x+1);
        return p;
    }

private:
    int64_t* tree_;
    const int n_;
};

const int MAXN = 2048;
int N, A, B;
int Y[MAXN];
int64_t S[MAXN];
typedef bitset<101> BS101;

bool feasible1(int64_t mask, int d) {
  const int64_t m2 = ~((1LL<<d)-1);
  vector<BS101> dp(N+1);
  dp[0].set(0);
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j <= N; j++) {
      if ((((S[j]-S[i]) & m2) & (~mask)) == 0) {
        dp[j] |= (dp[i] << 1);
      }
    }
  }
  for (int i = A; i <= B; i++) {
    if (dp[N][i]) return true;
  }
  return false;
}

void solve1() {
  int d = 63 - __builtin_clzl(S[N]);
  int64_t mask = 0;
  for (int i = d; i >= 0; i--) {
    if (!feasible1(mask, i)) mask |= (1LL<<i);
  }
  printf("%ld", mask);
}

vector<FenwickTree*> ft;

void buildFt() {
  for (int i = 0; i <= N; i++) {
    ft.push_back(new FenwickTree(B));
  }
}

void resetFt() {
  for (int i = 0; i <= N; i++) {
    ft[i]->clear();
  }
}

bool feasible2(int64_t mask, int d) {
  resetFt();
  const int64_t m2 = ~((1LL<<d)-1);
  for (int i = 1; i <= N; i++) {
    if (((S[i] & m2) & (~mask)) == 0) {
      ft[i]->set(1, 1);
    }
  }

  for (int i = 1; i < N; i++) {
    if (ft[i]->get(B) == 0) continue;
    int k = ft[i]->lowerBound(1);
    if (k == B) continue;
    for (int j = i+1; j <= N; j++) {
      if ((((S[j]-S[i]) & m2) & (~mask)) == 0) {
        ft[j]->set(k+1, 1);
      }
    }
  }
  return ft[N]->get(B) > 0;
}

void solve2() {
  assert(A == 1);
  buildFt();
  int d = 63 - __builtin_clzl(S[N]);
  int64_t mask = 0;
  for (int i = d; i >= 0; i--) {
    if (!feasible2(mask, i)) mask |= (1LL<<i);
  }
  printf("%ld", mask);
}

int main() {
  scanf("%d%d%d", &N, &A, &B);
  for (int i = 1; i <= N; i++) {
    scanf("%d", &Y[i]);
    S[i] = S[i-1] + Y[i];
  }
  if (S[N] == 0) {
    printf("0\n");
    return 0;
  }

  if (N <= 100) solve1();
  else solve2();
  return 0;
}
