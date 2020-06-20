// https://www.luogu.com.cn/problem/P4494
// [HAOI2018]反色游戏

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

const int MAXN = 100010;
int P2[MAXN];

class Tarjan {
 public:
  Tarjan(int n, int m) : n_(n), m_(m), g_(n+1, 2*m) {
    alloc();
  }

  ~Tarjan() {
    dealloc();
  }

  void tarjan(int u, int fa) {
    group_[u] = cntmap_;
    cntBcut_[u] = (c_[u] == 1);
    dfn_[u] = low_[u] = ++cnt_;
    cntB_[u] = (c_[u] == 1);
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      if (!dfn_[v]) {
        tarjan(v, u);
        low_[u] = min(low_[u], low_[v]);
        cntB_[u] += cntB_[v];
        if (low_[v] >= dfn_[u]) {
          cntBcut_[u] += cntB_[v];
          cut_[u]++;
          unsol_[u] = (unsol_[u] || (cntB_[v] & 1));
        }
      } else if (v != fa) low_[u] = min(low_[u], dfn_[v]);
    }
    if (!fa) cut_[u]--;
  }

  void addEdge(int u, int v) {
    g_.addEdge(u, v);
    g_.addEdge(v, u);
    deg_[u]++;
    deg_[v]++;
  }

  void set(int i, bool b) {
    c_[i] = b;
  }

  void solve() {
    int cntunsol = 0;
    vector<int> cntBmap(n_+1, 0);
    vector<bool> isunsol(n_+1, false);
    for (int i = 1; i <= n_; i++) {
      if (!dfn_[i]) {
        ++cntmap_;
        tarjan(i, 0);
        cntunsol += (cntB_[i] & 1);
        cntBmap[cntmap_] = cntB_[i];
        isunsol[cntmap_] = (cntB_[i] & 1);
      }
    }
    int ans = m_ - n_ + cntmap_;
    printf("%d ", (!cntunsol) ? P2[ans] : 0);
    for (int i = 1; i <= n_; i++) {
      if (!deg_[i]) {
        printf("%d ", (cntunsol - cntB_[i] == 0 ? P2[ans] : 0));
      } else if (cut_[i] == 0) {
        if (isunsol[group_[i]] && cntunsol - c_[i] == 0) {
          printf("%d ", P2[ans-deg_[i]+1+cut_[i]]);
        } else if (!isunsol[group_[i]] && cntunsol == 0 && !c_[i]) {
          printf("%d ", P2[ans-deg_[i]+1+cut_[i]]);
        } else {
          printf("0 ");
        }
      } else {
        bool feasible =
            (!unsol_[i] && (cntBmap[group_[i]]-cntBcut_[i]) % 2 == 0);
        if (feasible && cntunsol - isunsol[group_[i]] == 0) {
          printf("%d ", P2[ans-deg_[i]+1+cut_[i]]);
        } else {
          printf("0 ");
        }
      }
    }
    printf("\n");
  }

 private:
  int n_, m_;
  Graph g_;
  int cntmap_ = 0;
  int cnt_ = 0;
  int* group_;
  int* cntBcut_;
  bool* c_;
  int* dfn_;
  int* low_;
  int* cntB_;
  int* cut_;
  bool* unsol_;
  int* deg_;

  void alloc() {
    group_ = new int[n_+1]{};
    cntBcut_ = new int[n_+1]{};
    c_ = new bool[n_+1]{};
    dfn_ = new int[n_+1]{};
    low_ = new int[n_+1]{};
    cntB_ = new int[n_+1]{};
    cut_ = new int[n_+1]{};
    unsol_ = new bool[n_+1]{};
    deg_ = new int[n_+1]{};
  }

  void dealloc() {
    delete[] group_;
    delete[] cntBcut_;
    delete[] c_;
    delete[] dfn_;
    delete[] low_;
    delete[] cntB_;
    delete[] cut_;
    delete[] unsol_;
    delete[] deg_;
  }
};

const int MOD = 1000000007;
void init() {
  P2[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    P2[i] = (P2[i-1] * 2) % MOD;
  }
}

int main() {
  init();
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, m;
    scanf("%d%d", &n, &m);
    Tarjan tarjan(n, m);
    for (int i = 0; i < m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      tarjan.addEdge(u, v);
    }
    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
      tarjan.set(i+1, s[i]-'0');
    }
    tarjan.solve();
  }

  return 0;
}
