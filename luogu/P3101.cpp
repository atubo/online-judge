// https://www.luogu.com.cn/problem/P3101
// [USACO14JAN]Ski Course Rating G

#include <bits/stdc++.h>
using namespace std;

// Node is 0-indexed
class KruskalReconstructionTree {
 public:
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

  struct Edge {
    int u, v, w;
    bool operator < (const Edge& other) const {
      return w < other.w;
    }
  };

 private:
  int n_;
  Graph g_;
  int* fa_; // for union-find
  int* val_; // weight of internal nodes
  vector<Edge> e_;

  void alloc() {
    const int lim = 2*n_;
    fa_ = new int[lim]{};
    val_ = new int[lim]{};
    for (int i = 0; i < lim; i++) {
      fa_[i] = i;
    }
  }

  void dealloc() {
    delete[] fa_;
    delete[] val_;
  }

  void addTreeEdge(int u, int v) {
    g_.addEdge(u, v);
  }

  int find(int x) {
    return fa_[x] == x ? x : fa_[x] = find(fa_[x]);
  }

 public:
  KruskalReconstructionTree(int n): n_(n), g_(2*n-1, 2*n-2) {
    alloc();
  }

  ~KruskalReconstructionTree() {
    dealloc();
  }

  void kruskal() {
    sort(e_.begin(), e_.end());
    for (int idx=n_-1, i=0; i < (int)e_.size(); i++) {
      int fu = find(e_[i].u), fv = find(e_[i].v);
      if (fu == fv) continue;
      fa_[fu] = fa_[fv] = ++idx;
      val_[idx] = e_[i].w;
      addTreeEdge(idx, fu);
      addTreeEdge(idx, fv);
      if (idx == 2*n_-2) break;
    }
  }

  void addEdge(int u, int v, int w) {
    e_.push_back({u, v, w});
  }

  const Graph& getTree() const {
    return g_;
  }

  int* getVal() const {
    return val_;
  }
};

const int MAXN = 505;
const int DX[4] = {0, 1, 0, -1};
const int DY[4] = {1, 0, -1, 0};
int H[MAXN][MAXN];
int S[2*MAXN*MAXN];
int D[2*MAXN*MAXN];
int M, N, T;

int encode(int i, int j) {
  return i*N + j;
}

bool inRange(int i, int j) {
  return 0 <= i && i < M && 0 <= j && j < N;
}

using Graph = KruskalReconstructionTree::Graph;

void dfs1(const Graph& g, int u) {
  S[u] = (u < M*N ? 1 : 0);
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    dfs1(g, v);
    S[u] += S[v];
  }
}

void dfs2(const Graph& g, const int* val, int u, int last) {
  if (u < M*N) {
    D[u] = last;
    return;
  }
  if (S[u] >= T) {
    last = val[u];
  }
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    dfs2(g, val, v, last);
  }
}

int main() {
  scanf("%d%d%d", &M, &N, &T);
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      scanf("%d", &H[i][j]);
    }
  }
  vector<int> sp;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      int x;
      scanf("%d", &x);
      if (x) {
        sp.push_back(encode(i, j));
      }
    }
  }
  KruskalReconstructionTree krt(M*N);
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      int u = encode(i, j);
      for (int d = 0; d < 4; d++) {
        int i2 = i + DX[d];
        int j2 = j + DY[d];
        if (inRange(i2, j2)) {
          int v = encode(i2, j2);
          krt.addEdge(u, v, abs(H[i][j] - H[i2][j2]));
        }
      }
    }
  }

  krt.kruskal();
  
  const auto& g = krt.getTree();
  const int* val = krt.getVal();
  const int root = 2*M*N-2;
  dfs1(g, root);
  dfs2(g, val, root, INT_MAX);
  int64_t ans = 0;
  for (int x: sp) {
    ans += D[x];
  }
  printf("%ld\n", ans);
  return 0;
}
