// https://www.luogu.com.cn/problem/P4180
// [BJWC2010]严格次小生成树

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
    const int N;
    vector<int> rank;
    vector<int> parent;
    vector<int> size;

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parent[k] = k;
        rank[k] = 0;
        size[k] = 1;
    }

    int link(int u, int v) {
        if (u == v) return u;
        if (rank[u] > rank[v]) {
            parent[v] = u;
            size[u] += size[v];
            return u;
        } else {
            parent[u] = v;
            size[v] += size[u];
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
            return v;
        }
    }

public:
    UnionFind(int n): N(n) {
        rank.resize(N);
        parent.resize(N);
        size.resize(N);

        reset();
    }

    void reset() {
        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    int find(int k) {
        if (parent[k] == k) return k;
        int root = find(parent[k]);
        return parent[k] = root;
    }

    int join(int u, int v) {
        return link(find(u), find(v));
    }
};

class Kruskal {
    using TIII = tuple<int, int, int>;  // (weight, u, v)
    struct Edge {
      int w, u, v, id;
      bool operator < (const Edge& other) const {
        return w < other.w;
      }
    };
public:
    static vector<int> mst(const vector<TIII>& oedges, int N) {
      vector<Edge> edges;
      for (int i = 0; i < (int)oedges.size(); i++) {
        const auto& e = oedges[i];
        int w, u, v;
        tie(w, u, v) = e;
        edges.push_back({w, u, v, i});
      }
      vector<int> ret;
      UnionFind uf(N);
      sort(edges.begin(), edges.end());
      for (int i = 0; i < (int)edges.size(); i++) {
        auto e = edges[i];
        int u = e.u;
        int v = e.v;
        int id = e.id;
        if (uf.find(u) == uf.find(v)) continue;
        ret.push_back(id);
        uf.join(u, v);
      }
      return ret;
    }
};

class BinaryLiftLCA {
  // Note graph node is 0-indexed
  class Graph {
   public:
    struct Edge {
      int next, to, wt;
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
    void addEdge(int u, int v, int w) {
      E[eidx].to = v;
      E[eidx].next = head[u];
      E[eidx].wt = w;
      head[u] = eidx++;
    }
  };

  int N_, root_;
  int MAXB_;
  Graph g_;
 public:
  struct MaxTwo {
    MaxTwo() : a(-1), b(-1) {}
    MaxTwo(int aa, int bb) : a(aa), b(bb) {}
    int a, b;
    MaxTwo& mergeFrom(const MaxTwo& other) {
      if (a == other.a) {
        b = max(b, other.b);
      } else if (a > other.a) {
        b = max(b, other.a);
      } else {
        b = max(a, other.b);
        a = other.a;
      }
      return *this;
    }

    static MaxTwo merge(const MaxTwo& m1, const MaxTwo& m2) {
      if (m1.a == m2.a) {
        return MaxTwo{m1.a, max(m1.b, m2.b)};
      } else if (m1.a > m2.a) {
        return MaxTwo{m1.a, max(m1.b, m2.a)};
      } else {
        return MaxTwo{m2.a, max(m2.b, m1.a)};
      }
    }
  };

  int* depth;
  int** father;
  MaxTwo** maxv;

 public:
  BinaryLiftLCA(int N, int root)
      : N_(N), root_(root), MAXB_(log2(N)+1), g_(N, 2*(N-1)) {
        alloc();
      }

  ~BinaryLiftLCA() {
    dealloc();
  }

  void addEdge(int u, int v, int w) {
    g_.addEdge(u, v, w);
    g_.addEdge(v, u, w);
  }

  void build() {
    dfs(root_, -1, 0, -1);

    binaryLift();
  }

  MaxTwo findLCA(int u, int v) const {
    assert(u != v);
    if (depth[u] < depth[v]) swap(u, v);
    MaxTwo ans;
    for (int b = MAXB_-1; b >= 0; b--) {
      if (father[u][b] == -1) continue;
      if (depth[father[u][b]] >= depth[v]) {
        ans.mergeFrom(maxv[u][b]);
        u = father[u][b];
      }
    }

    if (u == v) return ans;

    for (int b = MAXB_-1; b >= 0; b--) {
      if (father[u][b] == -1) continue;
      if (father[u][b] != father[v][b]) {
        ans.mergeFrom(MaxTwo::merge(maxv[u][b], maxv[v][b]));
        u = father[u][b];
        v = father[v][b];
      }
    }
    return ans.mergeFrom(MaxTwo::merge(maxv[u][0], maxv[v][0]));
  }

 private:
  void alloc() {
    depth = new int[N_]{};
    father = new int*[N_]{};
    maxv = new MaxTwo*[N_]{};
    for (int i = 0; i < N_; i++) {
      father[i] = new int[MAXB_]{};
      memset(father[i], -1, MAXB_*sizeof(int));
      maxv[i] = new MaxTwo[MAXB_]{};
    }
  }

  void dealloc() {
    delete[] depth;
    for (int i = 0; i < N_; i++) {
      delete[] father[i];
      delete[] maxv[i];
    }
    delete[] father;
    delete[] maxv;
  }

  void dfs(int x, int f, int d, int w) {
    depth[x] = d;
    father[x][0] = f;
    maxv[x][0] = MaxTwo{w, -1};
    for (int eidx = g_.head[x]; ~eidx; eidx = g_.E[eidx].next) {
      int u = g_.E[eidx].to;
      if (u != f) dfs(u, x, d+1, g_.E[eidx].wt);
    }
  }

  void binaryLift() {
    for (int j = 1; j < MAXB_; j++) {
      for (int i = 0; i < N_; i++) {
        if (father[i][j-1] != -1) {
          father[i][j] = father[father[i][j-1]][j-1];
          maxv[i][j] = MaxTwo::merge(maxv[i][j-1], maxv[father[i][j-1]][j-1]);
        }
      }
    }
  }
};

const int MAXM = 300010;
int N, M;
bool vis[MAXM];

int main() {
  scanf("%d%d", &N, &M);
  vector<tuple<int, int, int>> e;
  for (int i = 0; i < M; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    u--; v--;
    e.push_back({w, u, v});
  }
  auto mst = Kruskal::mst(e, N);
  BinaryLiftLCA bl(N, 0);
  int64_t tot = 0;
  for (int x : mst) {
    int w, u, v;
    tie(w, u, v) = e[x];
    vis[x] = true;
    bl.addEdge(u, v, w);
    tot += w;
  }
  bl.build();

  int delta = INT_MAX;
  for (int i = 0; i < M; i++) {
    int w, u, v;
    tie(w, u, v) = e[i];
    if (u == v || vis[i]) continue;
    auto mt = bl.findLCA(u, v);
    if (w > mt.a) delta = min(delta, w - mt.a);
    else delta = min(delta, w - mt.b);
  }
  printf("%ld\n", tot + delta);

  return 0;
}
