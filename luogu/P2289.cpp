// https://www.luogu.com.cn/problem/P2289
// [HNOI2004]邮递员

#include <bits/stdc++.h>
using namespace std;

class Plug {
 public:
  Plug(int n, int m) : n_(n), m_(m) {}

  static int find(int state, int id) {
    return (state >> (id << 1)) & 3;
  }

  static void set(int& state, int bit, int val) {
    bit = bit << 1;
    state |= 3 << bit;
    state ^= 3 << bit;
    state |= val << bit;
  }

  int link(int state, int pos) {
    int cnt = 0;
    int delta = (find(state, pos) == 1 ? 1 : -1);
    for (int i = pos; 0 <= i && i <= m_; i += delta) {
      int p = find(state, i);
      if (p == 1) cnt++;
      else if (p == 2) cnt--;
      if (cnt == 0) return i;
    }
    return -1;
  }

  void execute(int x, int y) {
    int now = (x * m_ + y) & 1;
    int last = now ^ 1;
    f_[now].clear();
    for (const auto& [s, val] : f_[last]) {
      int state = s;
      int p1 = find(state, y);
      int p2 = find(state, y+1);
      if (!p1 && !p2) {
        if (x != n_-1 && y != m_-1) {
          set(state, y, 1);
          set(state, y+1, 2);
          f_[now][state] += val;
        }
      } else if (p1 && !p2) {
        if (x != n_-1) {
          f_[now][state] += val;
        }
        if (y != m_-1) {
          set(state, y, 0);
          set(state, y+1, p1);
          f_[now][state] += val;
        }
      } else if (!p1 && p2) {
        if (y != m_-1) f_[now][state] += val;
        if (x != n_-1) {
          set(state, y, p2);
          set(state, y+1, 0);
          f_[now][state] += val;
        }
      } else if (p1 == 1 && p2 == 1) {
        set(state, link(state, y+1), 1);
        set(state, y, 0);
        set(state, y+1, 0);
        f_[now][state] += val;
      } else if (p1 == 1 && p2 == 2) {
        if (x == n_-1 && y == m_-1) ans_ += val;
      } else if (p1 == 2 && p2 == 1) {
        set(state, y, 0);
        set(state, y+1, 0);
        f_[now][state] += val;
      } else if (p1 == 2 && p2 == 2) {
        set(state, link(state, y), 2);
        set(state, y, 0);
        set(state, y+1, 0);
        f_[now][state] += val;
      }
    }
  }

  void solve() {
    if (n_ == 1 || m_ == 1) {
      printf("1\n");
      return;
    }
    f_[1][0] = 1;
    for (int i = 0; i < n_; i++) {
      for (int j = 0; j < m_; j++) {
        execute(i, j);
      }
      if (i != n_-1) {
        unordered_map<int, __int128> t;
        int now = ((i+1) * m_ - 1) & 1;
        for (const auto& [s, val] : f_[now]) {
          int state = (s << 2);
          t[state] = val;
        }
        f_[now] = std::move(t);
      }
    }
    write(ans_*2);
    printf("\n");
  }

  void write(__int128 x) {
    if (x > 9) write(x / 10);
    putchar(x%10 + '0');
  }

 private:
  int n_, m_;
  unordered_map<int, __int128> f_[2];
  __int128 ans_ = 0;
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  if (m > n) swap(n, m);
  Plug plug(n, m);
  plug.solve();
  return 0;
}
