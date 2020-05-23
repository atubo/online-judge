// https://www.luogu.com.cn/problem/P4939
// Agent2

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

const int MAXN = 10000000;
const int MAXM = 400010;
int N, M;

struct Query {
  int op, a, b;
} Q[MAXM];

int find1(const vector<int>& s, int x) {
  return lower_bound(s.begin(), s.end(), x) - s.begin() + 1;
}

int find2(const vector<int>& s, int x) {
  return upper_bound(s.begin(), s.end(), x) - s.begin();
}

int main() {
  scanf("%d%d", &N, &M);
  vector<int> S = {1, MAXN+1};
  for (int i = 0; i < M; i++) {
    int t, a, b=-1;
    scanf("%d%d", &t, &a);
    if (t == 0) {
      scanf("%d", &b);
    }
    Q[i] = {t, a, b};
    S.push_back(a);
    S.push_back(b);
  }
  sort(S.begin(), S.end());
  S.erase(unique(S.begin(), S.end()), S.end());
  const int n = S.size();
  FenwickTree ft(n);
  for (int i = 0; i < M; i++) {
    if (Q[i].op == 0) {
      int a = find1(S, Q[i].a);
      int b = find1(S, Q[i].b);
      ft.set(a, 1);
      ft.set(b+1, -1);
    } else {
      int a = find2(S, Q[i].a);
      printf("%ld\n", ft.get(a));
    }
  }

  return 0;
}
