// https://www.luogu.com.cn/problem/P4005
// 小 Y 和地铁

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
const int MAXN = 50;
int A[MAXN];
int N;

struct Route {
  int l, r;
  bool operator < (const Route& other) const {
    if (l != other.l) return l < other.l;
    return r < other.r;
  }
};

int L[MAXN], R[MAXN];
FenwickTree ftup(44), ftdown(44);
vector<Route> routes;
int ans;

int query(const FenwickTree& ft1, const FenwickTree& ft2, int x, int y) {
  return min(ft1.get(x, y), ft1.get(y, N)+ft2.get(x, N));
}

void dfs(int n, int s) {
  if (n == (int)routes.size()) {
    ans = min(ans, s);
    return;
  }

  if (s >= ans) return;
  int x = routes[n].l, y = routes[n].r;
  int s1 = query(ftup, ftdown, x, y);
  ftup.set(y, 1);
  dfs(n+1, s+s1);
  ftup.set(y, -1);

  int s2 = query(ftdown, ftup, x, y);
  ftdown.set(y, 1);
  dfs(n+1, s+s2);
  ftdown.set(y, -1);
}

void solve() {
  memset(L, 0, sizeof(L));
  memset(R, 0, sizeof(R));
  ftup.clear();
  ftdown.clear();
  routes.clear();
  ans = INT_MAX;

  scanf("%d", &N);
  for (int i = 1; i <= N; i++) {
    scanf("%d", &A[i]);
    A[i]--;
  }
  for (int i = 1; i <= N; i++) {
    int a = A[i];
    if (L[a] == 0) L[a] = i;
    else R[a] = i;
  }

  for (int i = 1; i <= N; i++) {
    int a = A[i];
    if (R[a] != 0 && R[a] != i) routes.push_back(Route{L[a], R[a]});
  }
  sort(routes.begin(), routes.end());

  dfs(0, 0);
  printf("%d\n", ans);
}

int T;

int main() {
  scanf("%d", &T);
  while (T--) {
    solve();
  }
  return 0;
}
