// https://www.luogu.com.cn/problem/P4073
// [WC2013]平面图

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1);

class PlanarDualGraph {
  struct Point {
    Point(int xx = 0, int yy = 0) : x(xx), y(yy) {}
    int x, y;

    Point operator - (const Point& other) const {
      return Point(x - other.x, y - other.y);
    }

    friend double cross(const Point& a, const Point& b) {
      return 1.0 * a.x * b.y - 1.0 * a.y * b.x;
    }
  };

  struct Edge {
    int id;
    int u, v;
    double angle;
    int wt;
    Edge(int idd = -1, int uu = 0, int vv = 0, double agl = 0, int w = 0) :
      id(idd), u(uu), v(vv), angle(agl), wt(w) {
        if (angle < 0) {
          angle += 2.0 * PI;
        }
      }
  };

 public:
  PlanarDualGraph(int n, int m) : n_(n), m_(m) {
    alloc();
  }

  ~PlanarDualGraph() {
    dealloc();
  }

  void addEdge(int u, int v, int w) {
    Point z = points_[v] - points_[u];
    edges_[eid_] = Edge{eid_, u, v, atan2(z.y, z.x), w};
    eid_++;
    edges_[eid_] = Edge{eid_, v, u, atan2(-z.y, -z.x), w};
    eid_++;
  }

  void addPoint(int x, int y) {
    points_[pid_++] = {x, y};
  }

  void build() {
    vector<pair<double, int>> tmp;
    for (int i = 0; i < 2*m_; i++) {
      tmp.push_back(make_pair(edges_[i].angle, i));
    }
    sort(tmp.begin(), tmp.end());
    for (int i = 0; i < 2*m_; i++) {
      int eid = tmp[i].second;
      Edge e = edges_[eid];
      rank_[eid] = eout_[e.u].size();
      eout_[e.u].push_back(eid);
    }

    for (int i = 0; i < n_; i++) {
      for (int j = 0; j < (int)eout_[i].size(); j++) {
        findRegion(i, eout_[i][j]);
      }
    }
  }

 private:
  int n_, m_;
  Point* points_;
  int pid_ = 0;
  Edge* edges_;
  int eid_ = 0;
  bool* vis_;
  int* rank_;
  int* enclose_;  // edge -> region
  vector<int> *eout_;
  int rid_ = 0;
  int outerRegion_ = -1;
  double* areas_;

  void alloc() {
    points_ = new Point[n_]{};
    edges_ = new Edge[2*m_]{};
    vis_ = new bool[2*m_]{};
    rank_ = new int[2*m_]{};
    enclose_ = new int[2*m_]{};
    eout_ = new vector<int>[n_]{};
    areas_ = new double[m_]{};
  }

  void dealloc() {
    delete[] points_;
    delete[] edges_;
    delete[] vis_;
    delete[] rank_;
    delete[] enclose_;
    delete[] eout_;
    delete[] areas_;
  }

  void findRegion(int x, int eid) {
    if (vis_[eid]) return;
    double area = 0;
    while (!vis_[eid]) {
      area += cross(points_[x], points_[edges_[eid].v]);
      vis_[eid] = true;
      enclose_[eid] = rid_;
      x = edges_[eid].v;
      if (!rank_[eid ^ 1]) eid = eout_[x].back();
      else eid = eout_[x][rank_[eid ^ 1] - 1];
    }
    if (area < 0) outerRegion_ = rid_;
    areas_[rid_] = area;
    rid_++;
  }

  class Locator {
    int nowx;
    struct Query {
      int id;
      Point pt;
      bool operator < (const Query& other) const {
        return pt.x < other.pt.x;
      }
    };

    struct KeyPoint {
      int id;
      Point pt;
      bool operator < (const KeyPoint& other) const {
        if (pt.x == other.pt.x) {
          return id < other.id;
        }
        return pt.x < other.pt.x;
      }
    };

    struct Info {
      const Locator& locator;
      int id;
      double k;
      int x, y;
      Info(const Locator& loc, int id0,
          const Point& a, const Point& b)
          : locator(loc), id(id0), x(a.x), y(a.y) {
        k = 1.0 * (a.y - b.y) / (a.x - b.x);
      }

      bool operator < (const Info& other) const {
        constexpr double EPS = 1e-8;
        double y0 = k * (locator.nowx - x) + y;
        double y1 = other.k * (locator.nowx - other.x) + other.y;
        if (fabs(y1 - y0) > EPS) return y0 < y1;
        return k < other.k;
      }
    };

    const PlanarDualGraph& pdg_;
    using Iter = set<Info>::iterator;
    Query* queries_;
    KeyPoint* keyPoints_;
    set<Info> s_;
    Iter* it_;
    int* region_;
    int m_, q_;
    int kptid_ = 0;
    int qid_ = 0;

    void alloc() {
      queries_ = new Query[q_]{};
      keyPoints_ = new KeyPoint[2*m_]{};
      it_ = new Iter[2*m_]{};
      region_ = new int[q_]{};
    }

    void dealloc() {
      delete[] queries_;
      delete[] keyPoints_;
      delete[] it_;
      delete[] region_;
    }

   public:
    Locator(const PlanarDualGraph& pdg, int q) : pdg_(pdg), q_(q) {
      m_ = pdg_.m_;
      alloc();
    }

    ~Locator() {
      dealloc();
    }

    void addQuery(int x, int y) {
      queries_[qid_] = Query{qid_, Point(x, y)};
      qid_++;
    }

    void build() {
      for (int i = 0; i < m_; i++) {
        int eid = 2*i;
        int u = pdg_.edges_[eid].u;
        int v = pdg_.edges_[eid].v;
        if (pdg_.points_[u].x > pdg_.points_[v].x) {
          eid |= 1;
          swap(u, v);
        }

        if (pdg_.points_[u].x != pdg_.points_[v].x) {
          keyPoints_[kptid_].id = eid + 1;
          keyPoints_[kptid_++].pt = pdg_.points_[u];
          keyPoints_[kptid_].id = -(eid + 1);
          keyPoints_[kptid_++].pt = pdg_.points_[v];
        }
      }

      sort(keyPoints_, keyPoints_ + kptid_);
      sort(queries_, queries_ + q_);

      for (int i = 0, j = 0; i < q_; i++) {
        for (; j < kptid_ && keyPoints_[j].pt.x <= queries_[i].pt.x; j++) {
          nowx = keyPoints_[j].pt.x;
          int id = keyPoints_[j].id;
          if (id < 0) {
            s_.erase(it_[-id-1]);
          } else {
            id--;
            int u = pdg_.edges_[id].u;
            int v = pdg_.edges_[id].v;
            it_[id] = s_.insert(
                Info(*this, id, pdg_.points_[u], pdg_.points_[v])).first;
          }
        }
        nowx = queries_[i].pt.x;
        Point a = queries_[i].pt, b = a;
        b.x += 1;
        Iter pos = s_.lower_bound(Info(*this, 0, a, b));
        if (pos == s_.end()) region_[queries_[i].id] = pdg_.outerRegion_;
        else region_[queries_[i].id] = pdg_.enclose_[pos->id ^ 1];
      }
    }
    friend class Solver;
  };

  friend class Solver;
};

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

    Graph(const Graph& g) = delete;

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

  friend class Solver;
};

// Online algorithm, pre-computing O(N log N)
// Each query O(log N)

class BinaryLiftLCA {
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

  int N_, root_;
  int MAXB_;
  Graph g_;
 public:
  int* depth;
  int** father;

 public:
  BinaryLiftLCA(int N, int root)
      : N_(N), root_(root), MAXB_(log2(N)+1), g_(N, 2*(N-1)) {
        alloc();
      }

  ~BinaryLiftLCA() {
    dealloc();
  }

  void addEdge(int u, int v) {
    g_.addEdge(u, v);
    g_.addEdge(v, u);
  }

  void build() {
    dfs(root_, -1, 0);

    binaryLift();
  }

  int findLCA(int u, int v) const {
    if (depth[u] < depth[v]) swap(u, v);
    for (int b = MAXB_-1; b >= 0; b--) {
      if (father[u][b] == -1) continue;
      if (depth[father[u][b]] >= depth[v]) {
        u = father[u][b];
      }
    }

    if (u == v) return u;

    for (int b = MAXB_-1; b >= 0; b--) {
      if (father[u][b] == -1) continue;
      if (father[u][b] != father[v][b]) {
        u = father[u][b];
        v = father[v][b];
      }
    }
    return father[u][0];
  }

 private:
  void alloc() {
    depth = new int[N_]{};
    father = new int*[N_]{};
    for (int i = 0; i < N_; i++) {
      father[i] = new int[MAXB_]{};
      memset(father[i], -1, MAXB_*sizeof(int));
    }
  }

  void dealloc() {
    delete[] depth;
    for (int i = 0; i < N_; i++) {
      delete[] father[i];
    }
    delete[] father;
  }

  void dfs(int x, int f, int d) {
    depth[x] = d;
    father[x][0] = f;
    for (int eidx = g_.head[x]; ~eidx; eidx = g_.E[eidx].next) {
      int u = g_.E[eidx].to;
      if (u != f) dfs(u, x, d+1);
    }
  }

  void binaryLift() {
    for (int j = 1; j < MAXB_; j++) {
      for (int i = 0; i < N_; i++) {
        if (father[i][j-1] != -1) {
          father[i][j] = father[father[i][j-1]][j-1];
        }
      }
    }
  }
};
class Solver {
  int n_, m_, q_;
  constexpr static int INF = 2e9;

 public:
  void solve() {
    scanf("%d%d", &n_, &m_);
    PlanarDualGraph pdg(n_, m_);
    for (int i = 0; i < n_; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      pdg.addPoint(2*x, 2*y);
    }
    for (int i = 0; i < m_; i++) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      u--; v--;
      pdg.addEdge(u, v, w);
    }
    pdg.build();
#if 0
    for (int i = 0; i < m_; i++) {
      printf("%d %d\n", pdg.enclose_[2*i], pdg.enclose_[2*i+1]);
    }
#endif

    KruskalReconstructionTree krt(pdg.rid_);
    for (int i = 0; i < pdg.m_; i++) {
      int u = pdg.enclose_[2*i];
      int v = pdg.enclose_[2*i+1];
      int w = pdg.edges_[2*i].wt;
      if (u == pdg.outerRegion_ || v == pdg.outerRegion_) {
        w = INF;
      }
      krt.addEdge(u, v, w);
      krt.addEdge(v, u, w);
    }
    krt.kruskal();
    const auto& g = krt.getTree();
#if 0
    for (int u = 0; u < g.N; u++) {
      printf("node %d value %d: ", u, krt.val_[u]);
      for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        printf("%d ", v);
      }
      printf("\n");
    }
#endif

    BinaryLiftLCA lca(g.N, g.N-1);
    for (int u = 0; u < g.N; u++) {
      for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        lca.addEdge(u, v);
      }
    }
    lca.build();

    scanf("%d", &q_);
    PlanarDualGraph::Locator locator(pdg, 2*q_);
    for (int i = 0; i < 2*q_; i++) {
      double x, y;
      scanf("%lf%lf", &x, &y);
      locator.addQuery(int(2*x+0.001), int(2*y+0.001));
    }
    locator.build();
    for (int i = 0; i < q_; i++) {
      int u = locator.region_[2*i];
      int v = locator.region_[2*i+1];
#if 0
      printf("query %d %d\n", u, v);
#endif
      if (u == pdg.outerRegion_ || v == pdg.outerRegion_) {
        printf("-1\n");
        continue;
      }
      if (u == v) {
        printf("0\n");
        continue;
      }
      int p = lca.findLCA(u, v);
      int w = krt.val_[p];
      if (w == INF) w = -1;
      printf("%d\n", w);
    }
  }
};

int main() {
  Solver solver;
  solver.solve();
  return 0;
}
