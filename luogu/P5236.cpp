// https://www.luogu.com.cn/problem/P5236
// 【模板】静态仙人掌

#include <bits/stdc++.h>
using namespace std;

class Cactus {
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
      E[eidx].wt = w;
      E[eidx].next = head[u];
      head[u] = eidx++;
    }
  };

 public:
  Cactus(int n, int m)
      : n_(n), m_(m), nb_(m-n+1), maxb_(log2(m+1)+1),
        g_(n, 2*m), gt_(m+1, 2*(m+1)) {
    alloc();
  }

  ~Cactus() {
    dealloc();
  }

  void addEdge(int u, int v, int w) {
    g_.addEdge(u, v, w);
    g_.addEdge(v, u, w);
  }

  void build() {
    tarjan(0);
    for (int i = 0; i < nb_; i++) {
      reverse(hs_[i].begin(), hs_[i].end());
      reverse(ls_[i].begin(), ls_[i].end());
    }
    for (int i = 0; i < nb_; i++) {
      int64_t len = -ls_[i][0];
      for (int j = 0; j < (int)hs_[i].size(); j++) {
        len += ls_[i][j];
        ds_[i].push_back(len);
        adde(n_+i, hs_[i][j], min(len, cl_[i]-len));
      }
    }

    dfs(0, -1, 0, 0);
    binaryLift();
  }

  int query(int u, int v) const {
    int p = lca(u, v);
    if (p < n_) return length_[u] + length_[v] - 2*length_[p];
    int x = jump(u, depth_[u] - depth_[p] - 1);
    int y = jump(v, depth_[v] - depth_[p] - 1);
    int g = p - n_;
    int cx = bsearch(hs_[g], x);
    int cy = bsearch(hs_[g], y);
    if (cx > cy) swap(cx, cy);
    int ans = length_[u] + length_[v] - length_[x] - length_[y]
        + min(ds_[g][cy]-ds_[g][cx], cl_[g]-ds_[g][cy]+ds_[g][cx]);
    return ans;
  }

 private:
  const int n_, m_, nb_, maxb_;
  Graph g_, gt_;
  int* dfn_;
  int* low_;
  int* root_;
  int* tag_;
  int* fe_; // length of node's back-edge
  int* cl_; // loop length
  int* depth_;
  int* length_;
  int** father_;
  int cnt_ = 0;
  stack<int> st_;
  vector<int>* hs_;  // vertices of a block
  vector<int>* ls_;  // edge lengths of a block
  vector<int>* ds_;  // distance to the root
  int blockCnt_ = 0;

  void alloc() {
    dfn_ = new int[n_]{};
    memset(dfn_, -1, n_*sizeof(int));
    low_ = new int[n_]{};
    memset(low_, -1, n_*sizeof(int));
    tag_ = new int[n_]{};
    memset(tag_, -1, n_*sizeof(int));
    fe_ = new int[n_]{};

    root_ = new int[nb_]{};
    memset(root_, -1, nb_*sizeof(int));
    cl_ = new int[nb_]{};
    hs_ = new vector<int>[nb_]{};
    ls_ = new vector<int>[nb_]{};
    ds_ = new vector<int>[nb_]{};

    depth_ = new int[m_+1]{};
    length_ = new int[m_+1]{};
    father_ = new int*[m_+1]{};
    for (int i = 0; i <= m_; i++) {
      father_[i] = new int[maxb_]{};
      memset(father_[i], -1, maxb_*sizeof(int));
    }
  }

  void dealloc() {
    delete[] dfn_;
    delete[] low_;
    delete[] root_;
    delete[] tag_;
    delete[] fe_;
    delete[] cl_;

    delete[] hs_;
    delete[] ls_;
    delete[] ds_;

    delete[] depth_;
    delete[] length_;
    for (int i = 0; i <= m_; i++) {
      delete[] father_[i];
    }
    delete[] father_;
  }

  void adde(int u, int v, int w) {
    gt_.addEdge(u, v, w);
    gt_.addEdge(v, u, w);
  }

  void tarjan(int u) {
    dfn_[u] = low_[u] = cnt_++;
    st_.push(u);
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      if (dfn_[v] != -1) {
        low_[u] = min(low_[u], dfn_[v]);
        continue;
      }
      int w = g_.E[eidx].wt;
      fe_[v] = w;
      tarjan(v);
      low_[u] = min(low_[u], low_[v]);
      if (dfn_[u] <= low_[v]) {
        if (st_.top() == v) {
          adde(u, v, w);
          st_.pop();
          continue;
        }
        int g = blockCnt_++;
        int tl = 0;
        root_[g] = u;
        int fl = st_.top();
        tag_[fl] = g;
        while (true) {
          int cur = st_.top();
          st_.pop();
          hs_[g].push_back(cur);
          ls_[g].push_back(fe_[cur]);
          tl += fe_[cur];
          if (cur == v) break;
        }
        hs_[g].push_back(u);
        ls_[g].push_back(-1);
        cl_[g] = tl;
      }
    }

    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      if (tag_[v] == -1) continue;
      int w = g_.E[eidx].wt;
      int r = tag_[v];
      cl_[r] += w;
      ls_[r][ls_[r].size()-1] = w;
      tag_[v] = -1;
    }
  }

  void dfs(int u, int f, int d, int l) {
    depth_[u] = d;
    length_[u] = l;
    father_[u][0] = f;
    for (int eidx = gt_.head[u]; ~eidx; eidx = gt_.E[eidx].next) {
      int v = gt_.E[eidx].to;
      int w = gt_.E[eidx].wt;
      if (v != f) dfs(v, u, d+1, l+w);
    }
  }

  void binaryLift() {
    for (int j = 1; j < maxb_; j++) {
      for (int i = 0; i <= m_; i++) {
        if (father_[i][j-1] != -1) {
          father_[i][j] = father_[father_[i][j-1]][j-1];
        }
      }
    }
  }

  int lca(int u, int v) const {
    if (depth_[u] < depth_[v]) swap(u, v);
    for (int b = maxb_-1; b >= 0; b--) {
      if (father_[u][b] == -1) continue;
      if (depth_[father_[u][b]] >= depth_[v]) {
        u = father_[u][b];
      }
    }

    if (u == v) return u;

    for (int b = maxb_-1; b >= 0; b--) {
      if (father_[u][b] == -1) continue;
      if (father_[u][b] != father_[v][b]) {
        u = father_[u][b];
        v = father_[v][b];
      }
    }
    return father_[u][0];
  }

  int jump(int u, int d) const {
    for (int b = maxb_-1; b >= 0; b--) {
      if ((1<<b) > d) continue;
      d -= (1 << b);
      u = father_[u][b];
      if (u == -1 || d == 0) break;
    }
    return u;
  }

  int bsearch(const vector<int>& h, int x) const {
    int lo = 0, hi = h.size()-1;
    if (h[0] == x) return 0;
    while (lo < hi - 1) {
      int mid = (lo + hi) / 2;
      if (dfn_[h[mid]] < dfn_[x]) lo = mid;
      else hi = mid;
    }
    return hi;
  }
};

int N, M, Q;

int main() {
  scanf("%d%d%d", &N, &M, &Q);
  Cactus cactus(N, M);
  for (int i = 0; i < M; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    u--; v--;
    cactus.addEdge(u, v, w);
  }
  cactus.build();
  for (int i = 0; i < Q; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    printf("%d\n", cactus.query(u, v));
  }
  return 0;
}
