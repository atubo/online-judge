// https://www.luogu.com.cn/problem/P4768
// [NOI2018]归程

#include <bits/stdc++.h>
using namespace std;

class FastDijkstra {
public:
    static const int64_t INF;

    typedef pair<int64_t,int> PII;  // pair = (dist, vertex)

    FastDijkstra(int N_): N(N_), edges(N), dist(N, INF), dad(N, -1) {}

    void addEdge(int u, int v, int64_t wt) {
        edges[u].push_back(make_pair(wt, v));
    }

    const vector<int64_t>& getDist() const {
        return dist;
    }

    const vector<int>& getDad() const {
        return dad;
    }

    void solve(int s) {
        // use priority queue in which top element has the "smallest" priority
        priority_queue<PII, vector<PII>, greater<PII> > Q;
        Q.push (make_pair (0, s));
        dist[s] = 0;
        while (!Q.empty()){
            PII p = Q.top();
            // break here if we want to stop when we find a target node
            Q.pop();

            int here = p.second;
            for (vector<PII>::const_iterator it=edges[here].begin();
                 it!=edges[here].end(); it++){
                if (dist[here] + it->first < dist[it->second]){
                    dist[it->second] = dist[here] + it->first;
                    dad[it->second] = here;
                    Q.push (make_pair (dist[it->second], it->second));
                }
            }
        }
    }

    void reset() {
        dist.assign(N, INF);
        dad.assign(N, -1);
    }

private:
    const int N;
    vector<vector<PII>> edges;
    vector<int64_t> dist;
    vector<int> dad;
};

const int64_t FastDijkstra::INF = 0x7FFFFFFFFFFFFFFF;

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
      return w > other.w;
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

  const int* getVal() const {
    return val_;
  }
};

struct Road {
  int u, v, l, a;
};

const int MAXN = 200010;
const int MAXH = 20;
int lastans = 0;
int N, M;
int T;
int Q, K, S;
int D[2*MAXN];
int F[2*MAXN][MAXH];
int depth[2*MAXN];

void dfs(const KruskalReconstructionTree::Graph& g,
    const vector<int64_t>& d, int u, int fa, int dep) {
  D[u] = (u < N ? d[u] : INT_MAX);
  memset(F[u], -1, MAXH*sizeof(int));
  F[u][0] = fa;
  depth[u] = dep;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    dfs(g, d, v, u, dep+1);
    D[u] = min(D[u], D[v]);
  }
}

void binaryLift() {
  for (int h = 1; h < MAXH; h++) {
    for (int u = 0; u < 2*N-1; u++) {
      int v = F[u][h-1];
      if (v != -1) {
        F[u][h] = F[v][h-1];
      }
    }
  }
}

int search(int u, int p, const int *w) {
  for (int h = MAXH-1; h >= 0; h--) {
    int v = F[u][h];
    if (v >= 0 && w[v] > p) {
      u = v;
    }
  }
  return u;
}

void solve() {
  lastans = 0;
  scanf("%d%d", &N, &M);
  vector<Road> roads;
  FastDijkstra dij(N);
  for (int i = 0; i < M; i++) {
    int u, v, l, a;
    scanf("%d%d%d%d", &u, &v, &l, &a);
    u--; v--;
    roads.push_back({u, v, l, a});
    dij.addEdge(u, v, l);
    dij.addEdge(v, u, l);
  }
  dij.solve(0);

  KruskalReconstructionTree krt(N);
  for (const auto& r : roads) {
    krt.addEdge(r.u, r.v, r.a);
  }
  krt.kruskal();
  const auto& g = krt.getTree();
  dfs(g, dij.getDist(), 2*N-2, -1, 0);

  binaryLift();

  scanf("%d%d%d", &Q, &K, &S);
  for (int i = 0; i < Q; i++) {
    int v, p;
    scanf("%d%d", &v, &p);
    v = (v + K * lastans - 1) % N;
    p = (p + K * lastans) % (S + 1);
    int u = search(v, p, krt.getVal());
    printf("%d\n", lastans=D[u]);
  }
}

int main() {
  scanf("%d", &T);
  while (T--) {
    solve();
  }
  return 0;
}
