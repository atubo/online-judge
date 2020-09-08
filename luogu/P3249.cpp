// https://www.luogu.com.cn/problem/P3249
// [HNOI2016]矿区

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

    friend int64_t cross(const Point& a, const Point& b) {
      return 1LL * a.x * b.y - 1LL * a.y * b.x;
    }
  };

  struct Edge {
    int id;
    int u, v;
    double angle;
    Edge(int idd = -1, int uu = 0, int vv = 0, double agl = 0) :
      id(idd), u(uu), v(vv), angle(agl) {
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

  void addEdge(int u, int v) {
    Point z = points_[v] - points_[u];
    edges_[eid_] = Edge{eid_, u, v, atan2(z.y, z.x)};
    eid_++;
    edges_[eid_] = Edge{eid_, v, u, atan2(-z.y, -z.x)};
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
  int64_t* areas_;

  void alloc() {
    points_ = new Point[n_]{};
    edges_ = new Edge[2*m_]{};
    vis_ = new bool[2*m_]{};
    rank_ = new int[2*m_]{};
    enclose_ = new int[2*m_]{};
    eout_ = new vector<int>[n_]{};
    areas_ = new int64_t[m_]{};
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
    int64_t area = 0;
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

  friend class Solution;
};

// Note graph node is 0-indexed
class Graph {
 public:
  struct Edge {
    int id;
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
  void addEdge(int u, int v, int id) {
    E[eidx].to = v;
    E[eidx].next = head[u];
    E[eidx].id = id;
    head[u] = eidx++;
  }
};

int N;

int64_t gcd(int64_t a, int64_t b) {
  if (b == 0) return a;
  return gcd(b, a%b);
}

class Solution {
 public:
  Solution(const PlanarDualGraph& pdg,
           const vector<unordered_map<int, int>>& nodesToEid) :
    pdg_(pdg), nodesToEid_(nodesToEid) {
    n_ = pdg_.rid_, m_ = pdg_.m_;
    alloc();
    build();
  }

  ~Solution() {
    dealloc();
  }

  void solve() {
    int64_t prev = 0;
    int c;
    while (scanf("%d", &c) > 0) {
      int d = (c + prev) % N + 1;
      vector<int> poly(d);
      for (int i = 0; i < d; i++) {
        int u;
        scanf("%d", &u);
        u = (u + prev) % N;
        poly[i] = u;
      }
      int64_t x1 = 0, x2 = 0;
      for (int i = 0; i < d; i++) {
        int u = poly[i];
        int v = poly[(i+1)%d];
        int eid = nodesToEid_[u].at(v);
        if (!intree_[eid/2]) {
          continue;
        }
        int p = pdg_.enclose_[eid];
        int q = pdg_.enclose_[eid ^ 1];
        assert(father_[p] == q || father_[q] == p);
        if (father_[p] == q) {
          x1 += val1_[p];
          x2 += val2_[p];
        } else {
          x1 -= val1_[q];
          x2 -= val2_[q];
        }
      }
      int64_t g = gcd(x2, 2*x1);
      printf("%ld %ld\n", x2/g, 2*x1/g);
      prev = x2/g;
    }
  }

 private:
  int n_, m_;
  Graph* g_;
  int64_t* val1_;
  int64_t* val2_;
  int* father_;
  bool* intree_;
  bool* vis_;
  const PlanarDualGraph& pdg_;
  const vector<unordered_map<int, int>>& nodesToEid_;

  void alloc() {
    g_ = new Graph(n_, 2*m_);
    val1_ = new int64_t[n_]{};
    val2_ = new int64_t[n_]{};
    father_ = new int[n_]{};
    intree_ = new bool[m_]{};
    vis_ = new bool[n_]{};
  }

  void dealloc() {
    delete g_;
    delete[] val1_;
    delete[] val2_;
    delete[] father_;
    delete[] intree_;
    delete[] vis_;
  }

  void build() {
    for (int i = 0; i < m_; i++) {
      int u = pdg_.enclose_[2*i];
      int v = pdg_.enclose_[2*i+1];
      g_->addEdge(u, v, i);
      g_->addEdge(v, u, i);
    }
    dfs(pdg_.outerRegion_, -1);
  }

  void dfs(int u, int fa) {
    vis_[u] = true;
    father_[u] = fa;
    val1_[u] = pdg_.areas_[u];
    val2_[u] = val1_[u] * val1_[u];
    for (int eidx = g_->head[u]; ~eidx; eidx = g_->E[eidx].next) {
      int v = g_->E[eidx].to;
      int id = g_->E[eidx].id;
      if (!vis_[v] && v != fa) {
        dfs(v, u);
        val1_[u] += val1_[v];
        val2_[u] += val2_[v];
        intree_[id] = true;
      }
    }
  }
};

int main() {
  int m, k;
  scanf("%d%d%d", &N, &m, &k);
  PlanarDualGraph pdg(N, m);
  for (int i = 0; i < N; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    pdg.addPoint(x, y);
  }
  vector<unordered_map<int, int>> nodesToEid(N);
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    a--; b--;
    pdg.addEdge(a, b);
    nodesToEid[a][b] = 2*i;
    nodesToEid[b][a] = 2*i+1;
  }
  pdg.build();

  Solution solution(pdg, nodesToEid);
  solution.solve();

  return 0;
}
