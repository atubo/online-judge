// https://www.luogu.com.cn/problem/P5108
// 仰望半月的夜空

#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)

// lcp(i) = LCP(i, i+1)
class SuffixArray {
 public:
  SuffixArray(const int* s, int n) : n_(n), s_(s) {
    assert(n_ > 0);
    alloc();
  }

  ~SuffixArray() {
    dealloc();
  }

 private:
  int n_;
  int kmax_;
  const int *s_;
  int *sa_, *pos_, *lcp_;
  int **p_, **height_;

  void alloc() {
    sa_ = new int[n_]{};
    pos_ = new int[n_]{};
    lcp_ = new int[n_]{};

    kmax_ = 32 - __builtin_clz(n_-1);
    p_ = new int*[kmax_+1]{};
    height_ = new int*[kmax_+1]{};
    for (int i = 0; i <= kmax_; i++) {
      p_[i] = new int[n_]{};
      height_[i] = new int[n_]{};
    }
  }

  void dealloc() {
    delete[] sa_;
    delete[] pos_;
    delete[] lcp_;

    for (int i = 0; i <= kmax_; i++) {
      delete[] p_[i];
      delete[] height_[i];
    }
    delete[] p_;
    delete[] height_;
  }

  void buildSA() {
    int gap = 0;
    auto sufCmp = [pos = pos_, &gap, n = n_] (int i, int j) {
        if (pos[i] != pos[j])
          return pos[i] < pos[j];
        i += gap;
        j += gap;
        return (i < n && j < n) ? pos[i] < pos[j] : i > j;
      };
    int tmp[n_] = {0};
    REP(i, n_) sa_[i] = i, pos_[i] = s_[i];
    sort(sa_, sa_ + n_, sufCmp);
    REP(i, n_-1) tmp[i+1] = tmp[i] + sufCmp(sa_[i], sa_[i+1]);
    REP(i, n_) p_[0][sa_[i]] = tmp[i];
    for (int k = 1; k <= kmax_; k++) {
      gap = 1 << (k-1);
      sort(sa_, sa_ + n_, sufCmp);
      REP(i, n_ - 1) tmp[i + 1] = tmp[i] + sufCmp(sa_[i], sa_[i + 1]);
      REP(i, n_) pos_[sa_[i]] = tmp[i];
      REP(i, n_) p_[k][sa_[i]] = tmp[i];
    }
  }

  void buildLCP() {
    for (int i = 0, k = 0; i < n_; ++i) if (pos_[i] != n_ - 1) {
      for (int j = sa_[pos_[i] + 1]; s_[i + k] == s_[j + k];) {
        ++k;
      }
      lcp_[pos_[i]] = k;
      if (k) {
        --k;
      }
    }
  }

  void buildRMQ() {
    for (int i = 0; i < n_; i++) {
      height_[0][i] = lcp_[i];
    }
    for (int j = 1; (1<<j) < n_; j++) {
      for (int i = 0; i < n_; i++) {
        if (i + (1<<j) > n_) break;
        height_[j][i] = min(height_[j-1][i], height_[j-1][i+(1<<(j-1))]);
      }
    }
  }

  int calcLCP(int x, int y) const {
    x = pos_[x]; y = pos_[y];
    if (x > y) swap(x, y);
    int k = 0;
    while ((1<<(k+1)) < (y-x)) k++;
    return min(height_[k][x], height_[k][y-(1<<k)]);
  }

  friend class Solution;
};

class SegmentTree {
  int N;
  int *val_, *lazy_;

 public:
  SegmentTree(int N_): N(N_) {
    val_ = new int[4*N+1]{};
    lazy_ = new int[4*N+1]{};
    memset(lazy_, -1, (4*N+1)*sizeof(int));
  }

  ~SegmentTree() {
    delete[] val_;
    delete[] lazy_;
  }

  void modify(int t, int a, int b) {
    if (a > b) return;
    modify(1, t, 1, N, a, b);
  }

  void query(int *ans) {
    query(ans, 1, 1, N);
  }

 private:
  void modify(int k, int t, int l, int r, int a, int b) {
    pushDown(k, l, r);
    if (a <= l && r <= b) {
      val_[k] = lazy_[k] = t;
      return;
    }
    int mid = (l + r) / 2;
    if (a <= mid) modify(2*k, t, l, mid, a, b);
    if (mid < b) modify(2*k+1, t, mid+1, r, a, b);
  }

  void pushDown(int k, int l, int r) {
    if (lazy_[k] == -1 || l == r) return;
    val_[2*k] = val_[2*k+1] = lazy_[2*k] = lazy_[2*k+1] = lazy_[k];
    lazy_[k] = -1;
  }
  
  void query(int* ans, int k, int l, int r) {
    pushDown(k, l, r);
    if (l == r) {
      ans[l] = val_[k];
      return;
    }
    int mid = (l + r) / 2;
    query(ans, 2*k, l, mid);
    query(ans, 2*k+1, mid+1, r);
  }
};

class Solution {
 public:
  Solution() {
    int s;
    scanf("%d%d", &s, &n_);
    alloc();
    if (s == 26) inputStr();
    else inputInt();
  }

  ~Solution() {
    dealloc();
  }

  void solve() {
    SuffixArray sa(a_, n_);
    sa.buildSA();
    sa.buildLCP();
    sa.buildRMQ();
    vector<int> stk;
    for (int i = 0; i < n_; i++) {
      if (stk.empty() || sa.sa_[i] < stk.back()) {
        stk.push_back(sa.sa_[i]);
      }
    }
    const int sz = stk.size();
    SegmentTree st(n_);
    for (int i = sz-1; i >= 0; i--) {
      int x = stk[i];
      if (i == sz-1) {
        st.modify(x, 1, n_);
      } else {
        int lcp = sa.calcLCP(x, stk[i+1]);
        st.modify(x, lcp+1, n_-x);
      }
    }
    int ans[n_+1] = {0};
    st.query(ans);
    for (int i = 1; i <= n_; i++) {
      printf("%d ", ans[i]+1);
    }
    printf("\n");
  }
 private:
  int n_;
  int *a_;

  void alloc() {
    a_ = new int[n_]{};
  }

  void dealloc() {
    delete[] a_;
  }

  void inputStr() {
    string s;
    cin >> s;
    assert((int)s.length() == n_);
    for (int i = 0; i < n_; i++) {
      a_[i] = s[i] - 'a';
    }
  }

  void inputInt() {
    for (int i = 0; i < n_; i++) {
      scanf("%d", &a_[i]);
    }
  }
};

int main() {
  Solution solution;
  solution.solve();
  return 0;
}
