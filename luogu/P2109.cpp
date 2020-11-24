// https://www.luogu.com.cn/problem/P2109
// [NOI2007]生成树计数

#include <bits/stdc++.h>
using namespace std;

const int MAXK = 5;
const int WK = 52;
const int MOD = 65521;
int K;

struct State {
  int A[MAXK];
  State() { std::fill(A, A+K, 0); }
  State(int *a) { std::copy(a, a + K, A); }

  void toStd() {
    static int B[MAXK * 2];
    std::fill(B, B + K * 2, -1);
    for (int i = 0, j = 0; i < K; i++) {
      A[i] = (B[A[i]] == -1 ? B[A[i]] = j++ : B[A[i]]);
    }
  }

  int getAns() {
    toStd();
    static bool vis[MAXK];
    std::fill(vis, vis + MAXK, false);
    int ans = 1;
    for (int i = 0; i < K; i++) {
      if (!vis[i]) {
        int sz = 0;
        for (int j = i; j < K; j++) {
          if (A[i] == A[j]) {
            vis[j] = true;
            sz++;
          }
        }
        for (int j = 0; j < sz-2; j++) {
          ans *= sz;
        }
      }
    }
    return ans;
  }

  int& getId() {
    static int id[15625];

    toStd();
    int ans = 0;
    for (int i = 0; i < K; i++) {
      ans = ans * K + A[i];
    }
    return id[ans];
  }

  int nextState(int linkState) {
    static bool linkK[MAXK];
    static int nextA[MAXK];

    for (int i = 0; i < K; i++) {
      linkK[i] = (linkState >> i) & 1;
    }

    bool link0 = false;
    for (int i = 1; i < K; i++) {
      if (A[i] == 0) link0 = true;
    }
    if (!link0 && !linkK[0]) return -1;
    // check if there is a cycle
    for (int i = 0; i < K; i++) {
      if (linkK[i]) {
        for (int j = i+1; j < K; j++) {
          if (linkK[j] && A[i] == A[j]) {
            return -1;
          }
        }
      }
    }

    std::copy(A + 1, A + K, nextA);
    nextA[K-1] = K;
    for (int i = 0; i < K; i++) {
      if (linkK[i]) {
        for (int j = 1; j < K; j++) {
          if (A[i] == A[j]) {
            nextA[j-1] = K;
          }
        }
      }
    }

    State s(nextA);
    return s.getId();
  }
} states[WK];

int cnt;

void dfs(int x, int lim) {
  static int _t[MAXK];
  if (x == K) {
    (states[cnt] = State(_t)).getId() = cnt;
     cnt++;
     return;
  }
  for (_t[x] = 0; _t[x] <= lim; _t[x]++) {
    dfs(x + 1, max(lim, _t[x] + 1));
  }
}

// square matrix fast power
class Matrix {
 public:
  int **m_;
  int n_;

 public:
  Matrix(int n): n_(n) {
    alloc();
  }

  Matrix(const Matrix &other) {
    n_ = other.n_;
    alloc();
    for (int i = 0; i < n_; i++) {
      memcpy(m_[i], other.m_[i], n_ * sizeof(int));
    }
  }


  ~Matrix() {
    for (int i = 0; i < n_; i++) {
      delete[] m_[i];
    }
    delete[] m_;
  }

  static Matrix power(Matrix x, int64_t n) {
    Matrix ret(x.n_), tmp(x.n_);
    for (int i = 0; i < x.n_; i++) ret.m_[i][i] = 1;
    while (n) {
      if (n & 1) ret.mul(x, tmp);
      x.mul(x, tmp);
      n >>= 1;
    }
    return ret;
  }

 private:
  void alloc() {
    m_ = new int*[n_]{};
    for (int i = 0; i < n_; i++) {
      m_[i] = new int[n_]{};
    }
  }

  void mul(const Matrix &rhs, Matrix &tmp) {
    for (int i = 0; i < n_; i++) {
      memset(tmp.m_[i], 0, n_ * sizeof(int));
      for (int k = 0; k < n_; k++) {
        if (!m_[i][k]) continue;
        for (int j = 0; j < n_; j++) {
          (tmp.m_[i][j] += (1LL * m_[i][k] * rhs.m_[k][j] % MOD)) %= MOD;
        }
      }
    }
    swap(tmp);
  }

  void swap(Matrix &other) {
    std::swap(m_, other.m_);
  }
};

int64_t N;

int main() {
  scanf("%d%ld", &K, &N);
  if (N < K) K = N;
  dfs(0, 0);
  Matrix A(cnt);
  for (int i = 0; i < cnt; i++) {
    for (int s = 0; s < (1 << K); s++) {
      int v = states[i].nextState(s);
      if (v != -1) A.m_[i][v]++;
    }
  }
  Matrix mp = Matrix::power(A, N-K);
  int64_t ans = 0;
  for (int i = 0 ; i < cnt; i++) {
    (ans += 1LL * mp.m_[i][0] * states[i].getAns() % MOD) %= MOD;
  }
  printf("%ld\n", ans);
  return 0;
}
