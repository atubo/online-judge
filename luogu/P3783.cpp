// https://www.luogu.com.cn/problem/P3783
// [SDOI2017]天才黑客

#include <bits/stdc++.h>
using namespace std;

class Tree {
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
    int curr_ = 0;
public:
    int* depth;
    int** father;
    int* dfn;

public:
    Tree(int N, int root)
        : N_(N), root_(root), MAXB_(log2(N)+1), g_(N, 2*(N-1)) {
            alloc();
    }

    ~Tree() {
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
      dfn = new int[N_]{};
      depth = new int[N_]{};
      father = new int*[N_]{};
      for (int i = 0; i < N_; i++) {
        father[i] = new int[MAXB_]{};
        memset(father[i], -1, MAXB_*sizeof(int));
      }
    }

    void dealloc() {
      delete[] dfn;
      delete[] depth;
      for (int i = 0; i < N_; i++) {
        delete[] father[i];
      }
      delete[] father;
    }

    void dfs(int x, int f, int d) {
      dfn[x] = curr_++;
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
const int MAXM = 50010;
int T;
int N, M, K;
int E[MAXM];
int W[MAXM];

void solve() {
  scanf("%d%d%d", &N, &M, &K);
  vector<vector<int>> in(N), out(N);
  for (int i = 0; i < M; i++) {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    a--; b--;
    out[a].push_back(i);
    in[b].push_back(i);
    E[i] = d - 1;
    W[i] = c;
  }

  Tree tree(K, 0);
  for (int i = 0; i < K-1; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    u--; v--;
    tree.addEdge(u, v);
  }
  tree.build();

  FastDijkstra dij(4*M+1);
  auto cmpByDfn = [&tree](int u, int v) {
    return tree.dfn[E[u]] < tree.dfn[E[v]];
  };
  for (int e = 0; e < M; e++) {
    dij.addEdge(4*e+1, 4*e+2, W[e]);
    dij.addEdge(4*e+1, 4*e+4, W[e]);
    dij.addEdge(4*e+3, 4*e+4, W[e]);
    dij.addEdge(4*e+3, 4*e+2, W[e]);
  }
  for (int u = 0; u < N; u++) {
    sort(in[u].begin(), in[u].end(), cmpByDfn);
    sort(out[u].begin(), out[u].end(), cmpByDfn);
    for (int i = 0; i < (int)in[u].size()-1; i++) {
      int e1 = in[u][i];
      int e2 = in[u][i+1];
      dij.addEdge(4*e1+2, 4*e2+2, 0);
      dij.addEdge(4*e2+4, 4*e1+4, 0);
    }
    for (int i = 0; i < (int)out[u].size()-1; i++) {
      int e1 = out[u][i];
      int e2 = out[u][i+1];
      dij.addEdge(4*e1+1, 4*e2+1, 0);
      dij.addEdge(4*e2+3, 4*e1+3, 0);
    }

    using PII = pair<int, int>;
    auto cmpByDfn2 = [&tree](PII p1, PII p2) {
      return tree.dfn[E[p1.first]] < tree.dfn[E[p2.first]];
    };
    vector<PII> tr;
    for (int i = 0; i < (int)in[u].size(); i++) {
      tr.push_back(make_pair(in[u][i], 0));
    }
    for (int i = 0; i < (int)out[u].size(); i++) {
      tr.push_back(make_pair(out[u][i], 1));
    }
    sort(tr.begin(), tr.end(), cmpByDfn2);
    for (int t = 0, i = 0, j = 0; t < (int)tr.size()-1; t++) {
      if (tr[t].second == 0) i++;
      else j++;
      int p = tree.findLCA(E[tr[t].first], E[tr[t+1].first]);
      int h = tree.depth[p];
      if (i != 0 && j != (int)out[u].size()) {
        dij.addEdge(4*in[u][i-1]+2, 4*out[u][j]+1, h);
      }
      if (i != (int)in[u].size() && j != 0) {
        dij.addEdge(4*in[u][i]+4, 4*out[u][j-1]+3, h);
      }
    }
  }
  for (int e : out[0]) {
    dij.addEdge(0, 4*e+1, 0);
    dij.addEdge(0, 4*e+3, 0);
  }
  dij.solve(0);
  const auto& dist = dij.getDist();
  for (int u = 1; u < N; u++) {
    int64_t ans = FastDijkstra::INF;
    for (int e : in[u]) {
      ans = min(ans, dist[4*e+2]);
      ans = min(ans, dist[4*e+4]);
    }
    printf("%ld\n", ans);
  }
}

int main() {
  scanf("%d", &T);
  while (T--) {
    solve();
  }
  return 0;
}
