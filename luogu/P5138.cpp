// https://www.luogu.com.cn/problem/P5138
// fibonacci

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;

struct Node {
  int x, y;
  Node(int x0 = 0, int y0 = 0): x(x0), y(y0) {}
  Node operator + (const Node& other) const {
    return Node((x + other.x) % MOD, (y + other.y) % MOD);
  }
  int operator * (const Node& other) {
    return (1LL*x*other.x + 1LL*y*other.y) % MOD;
  }
};

struct Matrix {
  int a[2][2];
  Matrix() {memset(a, 0, sizeof(a));}
  void init() {
    a[0][0] = a[1][1] = 1;
  }
  Matrix operator* (const Matrix& other) const {
    Matrix ans;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
          ans.a[i][k] = (1LL*ans.a[i][k] + 1LL*a[i][j]*other.a[j][k]) % MOD;
        }
      }
    }
    return ans;
  }
} tr;

Matrix qpow(Matrix a, int64_t n) {
  Matrix ans;
  ans.init();
  while (n > 0) {
    if (n & 1) {
      ans = ans * a;
    }
    a = a * a;
    n >>= 1;
  }
  return ans;
}

Node fib(int64_t x) {
  Matrix ans;
  ans.a[0][1] = 1;
  ans = ans * qpow(tr, x < 0 ? -x-1 : x);
  if (x >= 0) return Node(ans.a[0][0], ans.a[0][1]);
  ans.a[0][(x+1)&1] = -ans.a[0][(x+1)&1];
  return Node(ans.a[0][1], ans.a[0][0]);
}


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
    int64_t *val;
    Node* v;
    Node* tag;

   public:
    SegmentTree(int N_): N(N_) {
      val = new int64_t[4*N]{};
      v = new Node[4*N]{};
      tag = new Node[4*N]{};
    }

    ~SegmentTree() {
      delete[] val;
      delete[] v;
      delete[] tag;
    }
    // add t to range [a, b]
    void update(Node c, int a, int b) {
      update(1, c, 0, N-1, a, b);
    }

    // query range sum in [a, b]
    int query(int a, int b) {
      return query(1, 0, N-1, a, b);
    }

    void build(const vector<int>& idx, const vector<int>& dep) {
      build(1, 0, N-1, idx, dep);
    }

   private:
    void pushUp(int k) {
      v[k] = v[2*k] + v[2*k+1];
      val[k] = (val[2*k] + val[2*k+1]) % MOD;
    }

    void build(int k, int l, int r, const vector<int>& idx,
        const vector<int>& dep) {
      if (l == r) {
        v[k] = fib(dep[idx[l]]);
        return;
      }
      int mid = (l + r) / 2;
      build(2*k, l, mid, idx, dep);
      build(2*k+1, mid+1, r, idx, dep);
      pushUp(k);
    }

    void pushDown(int k, int l, int r) {
      if (l == r) return;
      if (tag[k].x || tag[k].y) {
        tag[2*k] = tag[2*k] + tag[k];
        tag[2*k+1] = tag[2*k+1] + tag[k];
        val[2*k] = (val[2*k] + v[2*k]*tag[k]) % MOD;
        val[2*k+1] = (val[2*k+1] + v[2*k+1]*tag[k]) % MOD;
        tag[k] = Node();
      }
    }

    void update(int k, Node c, int l, int r, int a, int b) {
      pushDown(k, l, r);
      if (a <= l && r <= b) {
        val[k] = (val[k] + v[k]*c) % MOD;
        tag[k] = tag[k] + c;
        return;
      }
      if (l == r) return;
      int mid = (l + r) / 2;
      if (a <= mid) update(2*k,   c, l, mid, a, b);
      if (mid < b)  update(2*k+1, c, mid+1, r, a, b);
      pushUp(k);
    }

    int query(int k, int l, int r, int a, int b) {
      pushDown(k, l, r);
      if (a <= l && r <= b) return val[k];
      int sum = 0;
      int mid = (l + r) / 2;
      if (a <= mid) sum = query(2*k, l, mid, a, b) % MOD;
      if (mid < b)  sum = (sum + query(2*k+1, mid+1, r, a, b)) % MOD;
      return sum;
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
  vector<int> stIdxToNode; // segment tree index to node
  int root;
  int Seg_size;

  HeavyLightDecomposition(int N_): N(N_), g(N_), st(N_) {
    size.resize(N);
    dep.resize(N);
    rev.resize(N);
    heavy.resize(N);
    stIdx.resize(N, -1);
    stIdxToNode.resize(N, -1);
    fa.resize(N, -1);
    top.resize(N);

    root = 0;
    Seg_size = 0;   // segment tree is 0-indexed
    dep[root] = 1;
  }

  void addEdge(int u, int v) {
    g.addEdge(u, v);
    g.addEdge(v, u);
  }

  void decompose() {
    dfs1(root, root);
    top[root] = root;
    dfs2(root, root);
    st.build(stIdxToNode, dep);
  }

  void update(int u, const Node& c) {
    int l = stIdx[u];
    int r = stIdx[u] + size[u] - 1;
    st.update(c, l, r);
  }

  int query(int u, int v) {
    int ret = queryEdge(u, v);
    int p = lca(u, v);
    int r = stIdx[p];
    ret = (ret + st.query(r, r)) % MOD;
    return ret;
  }

  int queryEdge(int u, int v) {
    int ret = 0;
    int p = lca(u, v);
    ret = (ret + queryEdgeChain(p, u)) % MOD;
    ret = (ret + queryEdgeChain(p, v)) % MOD;
    return ret;
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
    stIdxToNode[Seg_size-1] = u;

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

  int queryEdgeChain(int anc, int u) {
    int ret = 0;
    while (u != anc) {
      if (top[u] != u) {
        int p = top[u];
        if (dep[p] < dep[anc]) p = anc;
        int l = stIdx[heavyChild(p)];
        int r = stIdx[u];
        ret = (ret + st.query(l, r)) % MOD;
        u = p;
      } else {
        int r = stIdx[u];
        ret = (ret + st.query(r, r)) % MOD;
        int fe = rev[u];
        u = g.E[fe].to;
      }
    }
    return ret;
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

int N, M;

int main() {
  tr.a[0][1] = tr.a[1][0] = tr.a[1][1] = 1;
  scanf("%d%d", &N, &M);
  HeavyLightDecomposition hld(N);
  for (int i = 0; i < N-1; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--; y--;
    hld.addEdge(x, y);
  }
  hld.decompose();
  char cmd[10];
  for (int i = 0; i < M; i++) {
    int x, y;
    int64_t k;
    scanf("%s", cmd);
    if (cmd[0] == 'U') {
      scanf("%d%ld", &x, &k);
      x--;
      k -= hld.dep[x] + 1;
      hld.update(x, fib(k));
    } else {
      scanf("%d%d", &x, &y);
      x--; y--;
      printf("%d\n", hld.query(x, y));
    }
  }

  return 0;
}
