// https://www.luogu.com.cn/problem/P4719
// 【模板】"动态 DP"&动态树分治

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
const int INF = 0x3f3f3f3f;

struct Matrix {
  int g[2][2];
  Matrix() { memset(g, 0, sizeof(g)); }
  Matrix operator* (const Matrix& b) const {
    Matrix ret;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        ret.g[i][j] = INT_MIN;
        for (int k = 0; k < 2; k++) {
          ret.g[i][j] = max(ret.g[i][j], g[i][k] + b.g[k][j]);
        }
      }
    }
    return ret;
  }
  void print() const {
    printf("(%d %d %d %d)\n", g[0][0], g[0][1], g[1][0], g[1][1]);
  }
} G[MAXN];

int A[MAXN], ID[MAXN];
int F[MAXN][2];
int FA[MAXN];

class HeavyLightDecomposition {
 private:
  // Note graph node is 0-indexed
  class Graph {
   public:
    struct Edge {
      int next, to;
    };

    vector<int> head;
    int eidx;
    int N;

    Edge *E;

    Graph(int N_):N(N_) {
      head.resize(N);
      eidx = 0;

      for (int i = 0; i < N; i++) {
        head[i] = -1;
      }

      // since this should be a tree
      E = new Edge[2*N-2]{};
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

  // 0-indexed
  class SegmentTree {
    int N;
    Matrix *tree;

   public:
    SegmentTree(int N_): N(N_) {
      tree = new Matrix[4*N]{};
    }

   ~SegmentTree() {
     delete[] tree;
   }

   void build(int k, int l, int r) {
     if (l == r) {
       tree[k] = G[ID[l]];
       return;
     }
     int mid = (l + r) / 2;
     build(2*k, l, mid);
     build(2*k+1, mid+1, r);
     pushUp(k);
   }

   // query range [a, b], current node [l, r]
   Matrix query(int k, int a, int b, int l, int r) const {
     if (a <= l && r <= b) return tree[k];
     int mid = (l + r) / 2;
     if (b <= mid) return query(2*k, a, b, l, mid);
     if (mid < a) return query(2*k+1, a, b, mid+1, r);
     return query(2*k, a, b, l, mid) * query(2*k+1, a, b, mid+1, r);
   }

   void modify(int k, int l, int r, int a) {
     if (l == r) {
       tree[k] = G[ID[l]];
       return;
     }
     int mid = (l + r) / 2;
     if (a <= mid) modify(2*k, l, mid, a);
     else modify(2*k+1, mid+1, r, a);
     pushUp(k);
   }

   private:
   void pushUp(int k) {
     tree[k] = tree[2*k] * tree[2*k+1];
   }
  };

 public:
  const int N;
  Graph g;
  SegmentTree st;
  vector<int> size;
  vector<int> dep;
  vector<int> rev;    // node to father-edge
  vector<int> heavy;
  vector<int> stIdx;    // node to segment tree index
  vector<int> fa; // father along heavy chain, -1 is father-edge isn't heavy
  vector<int> top;
  vector<int> bot; // node to st index of tail on heavy chain
  int root;
  int Seg_size;

  HeavyLightDecomposition(int N_): N(N_), g(N_), st(N_) {
    size.resize(N);
    dep.resize(N);
    rev.resize(N);
    heavy.resize(N);
    stIdx.resize(N, -1);
    fa.resize(N, -1);
    top.resize(N);
    bot.resize(N, -1);

    root = 0;
    Seg_size = 0;   // segment tree is 0-indexed
  }

  void addEdge(int u, int v) {
    g.addEdge(u, v);
    g.addEdge(v, u);
  }

  void decompose() {
    dfs1(root, -1);
    top[root] = root;
    dfs2(root, root);
    st.build(1, 0, N-1);
  }

  void update(int x, int val) {
    G[x].g[1][0] += val - A[x];
    A[x] = val;
    while (true) {
      Matrix last = st.query(1, stIdx[top[x]], bot[top[x]], 0, N-1);
      st.modify(1, 0, N-1, stIdx[x]);
      Matrix now = st.query(1, stIdx[top[x]], bot[top[x]], 0, N-1);
      x = FA[top[x]];
      if (x < 0) break;
      G[x].g[0][0] +=
          max(now.g[0][0], now.g[1][0]) - max(last.g[0][0], last.g[1][0]);
      G[x].g[0][1] = G[x].g[0][0];
      G[x].g[1][0] += now.g[0][0] - last.g[0][0];
    }
  }

  Matrix query() const {
    return st.query(1, 0, bot[0], 0, N-1);
  }

 private:
  void dfs1(int u, int f) {
    int mx = -1, e = -1;
    size[u] = 1;
    F[u][1] = A[u];
    FA[u] = f;

    for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
      int v = g.E[eidx].to;
      if (v == f) continue;
      dep[v] = dep[u] + 1;
      rev[v] = eidx ^ 1;
      dfs1(v, u);
      size[u] += size[v];
      if (size[v] > mx) {
        mx = size[v];
        e = eidx;
      }
      F[u][1] += F[v][0];
      F[u][0] += max(F[v][0], F[v][1]);
    }
    heavy[u] = e;
    if (e != -1) fa[g.E[e].to] = u;
  }

  void dfs2(int u, int f) {
    stIdx[u] = Seg_size++;
    ID[stIdx[u]] = u;
    G[u].g[1][0] = A[u];
    G[u].g[1][1] = -INF;
    bot[top[u]] = stIdx[u];

    if (heavy[u] != -1) {
      int t = heavy[u];
      int v = g.E[t].to;
      top[v] = top[u];
      dfs2(v, u);
    }

    for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
      int v = g.E[eidx].to;
      if (v == f || eidx == heavy[u]) continue;
      top[v] = v;
      dfs2(v, u);
      G[u].g[0][0] += max(F[v][0], F[v][1]);
      G[u].g[1][0] += F[v][0];
    }
    G[u].g[0][1] = G[u].g[0][0];
  }
};

int N, M;

int main() {
  scanf("%d%d", &N, &M);
  HeavyLightDecomposition hld(N);
  for (int i = 0; i < N; i++) {
    scanf("%d", &A[i]);
  }
  for (int i = 0; i < N-1; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    hld.addEdge(x-1, y-1);
  }
  hld.decompose();

  for (int i = 0; i < M; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--;
    hld.update(x, y);
    Matrix ans = hld.query();
    printf("%d\n", max(ans.g[0][0], ans.g[1][0]));
  }

  return 0;
}
