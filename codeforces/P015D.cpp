// http://codeforces.com/problemset/problem/15/D
// D. Map

#include <bits/stdc++.h>
using namespace std;

struct Data {
  int x, v;
};

struct Data2 {
  int x, y;
  int64_t v;
  bool operator < (const Data2& other) const {
    if (v != other.v) return v < other.v;
    if (x != other.x) return x < other.x;
    return y < other.y;
  }
};

class Solution {
 public:
  Solution(int n, int m, int a, int b)
      : n_(n), m_(m), a_(a), b_(b), qc_(m_+1) {
    alloc();
    for (int i = 1; i <= n_; i++) {
      for (int j = 1; j <= m_; j++) {
        scanf("%d", &h_[i][j]);
      }
    }
    build();
  }

  ~Solution() {
    dealloc();
  }

  void solve() {
    vector<Data2> res;
    for (const auto& d : candidates_) {
      if (used_[d.x][d.y]) continue;
      res.push_back(d);
      for (int i = max(1, d.x-a_+1); i <= min(n_, d.x+a_-1); i++) {
        for (int j = max(1, d.y-b_+1); j <= min(m_, d.y+b_-1); j++) {
          used_[i][j] = true;
        }
      }
    }
    printf("%d\n", (int)res.size());
    for (const auto d : res) {
      printf("%d %d %I64d\n", d.x, d.y, d.v);
      //cout << d.x << " " << d.y << " " << d.v << endl;
    }
  }

 private:
  void build() {
    for (int j = 1; j <= m_; j++) {
      for (int i = 1; i <= a_; i++) {
        while (!qc_[j].empty() && qc_[j].back().v >= h_[i][j]) {
          qc_[j].pop_back();
        }
        qc_[j].push_back(Data{i, h_[i][j]});
      }
    }
    buildRow(1);

    for (int i = 2; i <= n_-a_+1; i++) {
      for (int j = 1; j <= m_; j++) {
        while (!qc_[j].empty() && qc_[j].front().x < i) qc_[j].pop_front();
        while (!qc_[j].empty() && qc_[j].back().v >= h_[i+a_-1][j]) {
          qc_[j].pop_back();
        }
        qc_[j].push_back(Data{i+a_-1, h_[i+a_-1][j]});
      }
      buildRow(i);
    }

    for (int i = 1; i <= n_; i++) {
      for (int j = 1; j <= m_; j++) {
        ps_[i][j] = ps_[i-1][j] + ps_[i][j-1] - ps_[i-1][j-1] + h_[i][j];
      }
    }
    for (int i = 1; i <= n_-a_+1; i++) {
      for (int j = 1; j <= m_-b_+1; j++) {
        int i2 = i + a_ - 1;
        int j2 = j + b_ - 1;
        int64_t v = ps_[i2][j2] - ps_[i-1][j2] - ps_[i2][j-1] +
            ps_[i-1][j-1] - 1LL * a_ * b_ * mn_[i][j];
        candidates_.push_back(Data2{i, j, v});
      }
    }
    sort(candidates_.begin(), candidates_.end());
  }

  void buildRow(int i) {
    deque<Data> q;
    for (int j = 1; j <= b_; j++) {
      while (!q.empty() && q.back().v >= qc_[j].front().v) q.pop_back();
      q.push_back(Data{j, qc_[j].front().v});
    }
    mn_[i][1] = q.front().v;
    for (int j = 2; j <= m_-b_+1; j++) {
      while (!q.empty() && q.front().x < j) q.pop_front();
      while (!q.empty() && q.back().v >= qc_[j+b_-1].front().v) q.pop_back();
      q.push_back(Data{j+b_-1, qc_[j+b_-1].front().v});
      mn_[i][j] = q.front().v;
    }
  }

  void alloc() {
    ps_ = new int64_t*[n_+1]{};
    mn_ = new int*[n_+1]{};
    h_ = new int*[n_+1]{};
    used_ = new bool*[n_+1]{};
    for (int i = 0; i <= n_; i++) {
      ps_[i] = new int64_t[m_+1]{};
      mn_[i] = new int[m_+1]{};
      h_[i] = new int[m_+1]{};
      used_[i] = new bool[m_+1]{};
    }
  }

  void dealloc() {
    for (int i = 0; i <= n_; i++) {
      delete[] ps_[i];
      delete[] mn_[i];
      delete[] h_[i];
      delete[] used_[i];
    }
    delete[] ps_;
    delete[] mn_;
    delete[] h_;
    delete[] used_;
  }

  int n_, m_;
  int a_, b_;
  vector<deque<Data>> qc_;
  int** h_;
  int** mn_;
  int64_t** ps_;
  bool** used_;
  vector<Data2> candidates_;
};

int main() {
  int n, m, a, b;
  scanf("%d%d%d%d", &n, &m, &a, &b);
  Solution solution(n, m, a, b);
  solution.solve();
  return 0;
}
