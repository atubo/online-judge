// https://www.luogu.com.cn/problem/P1783
// 海滩防御

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
    int u, v;
    int64_t w;
    bool operator < (const Edge& other) const {
      return w < other.w;
    }
  };

 private:
  int n_;
  Graph g_;
  int* fa_; // for union-find
 public:
  int64_t* val_; // weight of internal nodes
 private:
  vector<Edge> e_;

  void alloc() {
    const int lim = 2*n_;
    fa_ = new int[lim]{};
    val_ = new int64_t[lim]{};
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

  void addEdge(int u, int v, int64_t w) {
    e_.push_back({u, v, w});
  }

  const Graph& getTree() const {
    return g_;
  }
};

const int MAXN = 1010;
const int MAXH = 12;
int N, M;
int X[MAXN], Y[MAXN];

int F[2*MAXN][MAXH];
int D[2*MAXN];

using Graph = KruskalReconstructionTree::Graph;

void dfs(const Graph&g, int u, int fa, int dep) {
  D[u] = dep;
  memset(F[u], -1, MAXH*sizeof(int));
  F[u][0] = fa;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    dfs(g, v, u, dep+1);
  }
}

void binaryLift() {
  for (int j = 1; j < MAXH; j++) {
    for (int u = 0; u < 2*M+3; u++) {
      if (F[u][j-1] != -1) {
        F[u][j] = F[F[u][j-1]][j-1];
      }
    }
  }
}

int findLCA(int u, int v) {
  if (D[u] < D[v]) swap(u, v);
  for (int b = MAXH-1; b >= 0; b--) {
    if (F[u][b] == -1) continue;
    if (D[F[u][b]] >= D[v]) {
      u = F[u][b];
    }
  }

  if (u == v) return u;

  for (int b = MAXH-1; b >= 0; b--) {
    if (F[u][b] == -1) continue;
    if (F[u][b] != F[v][b]) {
      u = F[u][b];
      v = F[v][b];
    }
  }
  return F[u][0];
}

int main() {
  scanf("%d%d", &N, &M);
  for (int i = 1; i <= M; i++) {
    scanf("%d%d", &X[i], &Y[i]);
  }
  KruskalReconstructionTree krt(M+2);
  for (int i = 1; i <= M; i++) {
    for (int j = i+1; j <= M; j++) {
      int64_t d = 1LL*(X[i]-X[j])*(X[i]-X[j]) + 1LL*(Y[i]-Y[j])*(Y[i]-Y[j]);
      krt.addEdge(i, j, d);
    }
    krt.addEdge(0, i, 4LL*X[i]*X[i]);
    krt.addEdge(M+1, i, 4LL*(N-X[i])*(N-X[i]));
  }
  krt.addEdge(0, M+1, 4LL*N*N);
  krt.kruskal();

  const auto& g = krt.getTree();
  dfs(g, 2*M+2, -1, 0);
  binaryLift();
  int lca = findLCA(0, M+1);
  printf("%.2f\n", sqrt(krt.val_[lca])/2);
  return 0;
}
