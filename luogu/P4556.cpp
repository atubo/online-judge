// https://www.luogu.com.cn/problem/P4556
// [Vani有约会]雨天的尾巴 /【模板】线段树合并

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;

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
   public:
    struct Data {
      int x = 0;
      int f = 0;
    };

   private:
    int N;
    Data* data_;

   public:
    SegmentTree(int N_): N(N_) {
      data_ = new Data[4*N+1]{};
      build(1, 1, N);
    }

    ~SegmentTree() {
      delete[] data_;
    }

    void add(int t, int x) {
      add(1, 1, N, t, x);
    }

    Data query() {
      return data_[1];
    }

   private:
    void build(int k, int l, int r) {
      if (l == r) {
        data_[k].x = l;
        return;
      }
      int mid = (l + r) / 2;
      build(2*k, l, mid);
      build(2*k+1, mid+1, r);
      pushUp(k);
    }

    void add(int k, int l, int r, int t, int x) {
      if (l == r) {
        data_[k].f += t;
        return;
      }
      int mid = (l + r) / 2;
      if (x <= mid) add(2*k, l, mid, t, x);
      else add(2*k+1, mid+1, r, t, x);
      pushUp(k);
    }

    void pushUp(int k) {
      Data l = data_[2*k], r = data_[2*k+1];
      data_[k] = (r.f > l.f ? r : l);
    }
  };

 public:
  const int N;
  Graph g;
  vector<int> size;
  vector<int> dep;
  vector<int> rev;    // node to father-edge
  vector<int> heavy;
  vector<int> stIdx;    // node to segment tree index
  vector<int> fa; // father along heavy chain, -1 is father-edge isn't heavy
  vector<int> top;
  vector<vector<int>> events;
  int root;
  int Seg_size;

  HeavyLightDecomposition(int N_): N(N_), g(N_) {
    size.resize(N);
    dep.resize(N);
    rev.resize(N);
    heavy.resize(N);
    stIdx.resize(N, -1);
    fa.resize(N, -1);
    top.resize(N);
    events.resize(N+1);

    root = 0;
    Seg_size = 0;   // segment tree is 0-indexed
  }

  void addEdge(int u, int v) {
    g.addEdge(u, v);
    g.addEdge(v, u);
  }

  void decompose() {
    dfs1(root, root);
    top[root] = root;
    dfs2(root, root);
  }

  void updateNode(int u, int v, int d) {
    updateEdge(u, v, d);
    int p = lca(u, v);
    int r = stIdx[p];
    events[r].push_back(d);
    events[r+1].push_back(-d);
  }

  void updateEdge(int u, int v, int d) {
    int p = lca(u, v);;
    updateEdgeChain(u, p, d);
    updateEdgeChain(v, p, d);
  }

  void query() {
    SegmentTree st(MAXN);
    int t[N];
    for (int i = 0; i < N; i++) {
      for (int v : events[i]) {
        if (v > 0) st.add(1, v);
        else st.add(-1, -v);
      }
      SegmentTree::Data d = st.query();
      t[i] = (d.f == 0 ? 0 : d.x);
    }
    for (int i = 0; i < N; i++) {
      printf("%d\n", t[stIdx[i]]);
    }
  }

 private:
  void dfs1(int u, int f) {
    int mx = -1, e = -1;
    size[u] = 1;

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
    }
    heavy[u] = e;
    if (e != -1) fa[g.E[e].to] = u;
  }

  void dfs2(int u, int f) {
    stIdx[u] = Seg_size++;

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
    }
  }

  void updateEdgeChain(int u, int anc, int val) {
    while (u != anc) {
      if (top[u] != u) {
        int p = top[u];
        if (dep[p] < dep[anc]) p = anc;
        int l = stIdx[heavyChild(p)];
        int r = stIdx[u];
        events[l].push_back(val);
        events[r+1].push_back(-val);
        u = p;
      } else {
        int r = stIdx[u];
        events[r].push_back(val);
        events[r+1].push_back(-val);
        int fe = rev[u];
        u = g.E[fe].to;
      }
    }
  }

  int lca(int u, int v) {
    while (true) {
      int a = top[u], b = top[v];
      if (a == b) return dep[u] < dep[v] ? u : v;
      else if (dep[a] >= dep[b]) u = g.E[rev[a]].to;
      else v = g.E[rev[b]].to;
    }
  }

  int heavyChild(int u) const {
    int e = heavy[u];
    int ret = 0;
    if (e != -1) {
      ret = g.E[e].to;
    }
    return ret;
  }
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  HeavyLightDecomposition hld(n);
  for (int i = 0; i < n-1; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    a--; b--;
    hld.addEdge(a, b);
  }
  hld.decompose();
  for (int i = 0; i < m; i++) {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    x--; y--;
    hld.updateNode(x, y, z);
  }
  hld.query();
  return 0;
}
