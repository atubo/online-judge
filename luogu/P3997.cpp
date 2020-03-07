// https://www.luogu.com.cn/problem/P3997
// [SHOI2013]扇形面积并

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

struct Sector {
  int r, a1, a2;
};

struct Event {
  Event(int rr, int aa, int tt): r(rr), a(aa), t(tt) {}
  int r, a, t;
  bool operator < (const Event& other) const {
    if (a != other.a) return a < other.a;
    if (t != other.t) return t < other.t;
    return r < other.r;
  }
};

int N, M, K;

int main() {
  scanf("%d%d%d", &N, &M, &K);
  vector<Sector> sectors;
  for (int i = 0; i < N; i++) {
    int r, a1, a2;
    scanf("%d%d%d", &r, &a1, &a2);
    if (a1 <= a2) {
      sectors.emplace_back(Sector{r, a1+M, a2+M});
    } else {
      sectors.emplace_back(Sector{r, a1+M, 2*M});
      sectors.emplace_back(Sector{r, 0, a2+M});
    }
  }
  vector<int> R;
  set<int> A;
  for (const auto& s : sectors) {
    R.push_back(s.r);
    A.insert(s.a1);
    A.insert(s.a2);
  }
  sort(R.begin(), R.end());
  R.erase(unique(R.begin(), R.end()), R.end());

  vector<Event> E;
  for (auto& s : sectors) {
    s.r = lower_bound(R.begin(), R.end(), s.r) - R.begin() + 1;
    E.emplace_back(s.r, s.a1, 0);
    E.emplace_back(s.r, s.a2, 1);
  }
  for (int a : A) {
    E.emplace_back(0, a, -1);
  }

  sort(E.begin(), E.end());
  FenwickTree ft(R.size());

  int last = 0;
  int64_t ans = 0;
  for (const auto& e : E) {
    if (e.t == -1) {
      int m = ft.get(R.size());
      if (K <= m) {
        int x = ft.lowerBound(m-K+1);
        assert(x > 0);
        ans += 1LL * R[x-1] * R[x-1] * (e.a - last);
      }
      last = e.a;
    } else if (e.t == 0) {
      ft.set(e.r, 1);
    } else if (e.t == 1) {
      ft.set(e.r, -1);
    }
  }
  printf("%ld\n", ans);

  return 0;
}
