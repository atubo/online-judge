// https://www.luogu.com.cn/problem/P1971
// [NOI2011] 兔兔与蛋蛋游戏

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
 public:
  struct Edge {
    int next, to;
  };

  vector<int> head;
  int eidx;
  int N, M;

  Edge *E;

  Graph(int N_, int M_):N(N_), M(M_) {
    head.resize(N);
    eidx = 0;

    for (int i = 0; i < N; i++) {
      head[i] = -1;
    }

    E = new Edge[M]{};
  }

  ~Graph() {
    delete[] E;
  }

  // assume 0-indexed and no duplication
  void addEdge(int u, int v) {
    E[eidx].to = v;
    E[eidx].next = head[u];
    head[u] = eidx++;
  }
};

const int MAXN = 50;
int DX[4] = {0, 1, 0, -1};
int DY[4] = {1, 0, -1, 0};

class Solution {
 public:
  Solution(int n, int m): n_(n), m_(m), g_(n_*m_, 8*MAXN*MAXN) {
    memset(match_, -1, sizeof(match_));
    memset(ban_, 0, sizeof(ban_));
    memset(vis_, 0, sizeof(vis_));
    memset(mp_, 0, sizeof(mp_));
    memset(win_, 0, sizeof(win_));
  }

  int match(int u) {
    if (ban_[u]) return 0;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      if (vis_[v] == tim_ || ban_[v]) continue;
      vis_[v] = tim_;
      if (match_[v] == -1|| match(match_[v])) {
        match_[u] = v;
        match_[v] = u;
        return 1;
      }
    }
    return 0;
  }

  void init() {
    char s[50];
    for (int i = 0; i < n_; i++) {
      scanf("%s", s);
      for (int j = 0; j < m_; j++) {
        if (s[j] == 'O') mp_[i][j] = 0;
        else if (s[j] == 'X') mp_[i][j] = 1;
        else {
          mp_[i][j] = 1;
          bx_ = i;
          by_ = j;
        }
      }
    }
  }

  void build() {
    int t = 0;
    for (int i = 0; i < n_; i++) {
      for (int j = 0; j < m_; j++) {
        id_[i][j] = t++;
      }
    }
    for (int i = 0; i < n_; i++) {
      for (int j = 0; j < m_; j++) {
        if (!mp_[i][j]) continue;
        for (int d = 0; d < 4; d++) {
          int x = i + DX[d];
          int y = j + DY[d];
          if (!inRange(x, y) || mp_[x][y] == 1) continue;
          g_.addEdge(id_[i][j], id_[x][y]);
          g_.addEdge(id_[x][y], id_[i][j]);
        }
      }
    }
  }

  void solve() {
    for (int i = 0; i < n_; i++) {
      for (int j = 0; j < m_; j++) {
        if (mp_[i][j]) {
          ++tim_;
          match(id_[i][j]);
        }
      }
    }
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= 2*q; i++) {
      int x = id_[bx_][by_];
      ban_[x] = 1;
      if (match_[x] != -1) {
        int y = match_[x];
        match_[x] = match_[y] = -1;
        ++tim_;
        win_[i] = !match(y);
      }
      scanf("%d%d", &bx_, &by_);
      bx_--; by_--;
    }

    vector<int> ans;
    for (int i = 1; i <= q; i++) {
      if (win_[2*i-1] && win_[2*i]) {
        ans.push_back(i);
      }
    }
    printf("%d\n", (int)ans.size());
    for (int x : ans) {
      printf("%d\n", x);
    }
  }

 private:
  bool inRange(int x, int y) {
    return 0 <= x && x < n_ && 0 <= y && y < m_;
  }
  int n_;
  int m_;
  Graph g_;
  int match_[MAXN*MAXN];
  int ban_[MAXN*MAXN];
  int vis_[MAXN*MAXN];
  int mp_[MAXN][MAXN];
  int id_[MAXN][MAXN];
  bool win_[2010];
  int tim_ = 0;
  int bx_;
  int by_;
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  Solution solution(n, m);
  solution.init();
  solution.build();
  solution.solve();
  return 0;
}
