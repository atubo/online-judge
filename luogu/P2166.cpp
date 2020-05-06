// https://www.luogu.com.cn/problem/P2166
// Gty的超级妹子树

#include <bits/stdc++.h>
using namespace std;

class BlockTree {
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

  struct Block {
    vector<int> a;
    void insert(int x) {
      a.insert(lower_bound(a.begin(), a.end(), x+1), x);
    }
    void erase(int x) {
      a.erase(lower_bound(a.begin(), a.end(), x));
    }
    void modify(int x, int y) {
      erase(x);
      insert(y);
    }
    int query(int x) {
      return a.end() - upper_bound(a.begin(), a.end(), x);
    }
    int size() const {
      return a.size();
    }
  };

 public:

  // add undirected edge between u and v
  void add(int u, int v) {
    g_.addEdge(u, v);
    g_.addEdge(v, u);
  }

  // add directed edge from father to children
  void addb(int u, int v) {
    gb_.addEdge(u, v);
  }

  BlockTree(int n)
      : n_(n), cap_(200001), B(sqrt(n)), g_(cap_, 2*cap_-2), gb_(cap_, cap_-1) {
    alloc();
  }

  ~BlockTree() {
    dealloc();
  }

  void dfs(int u, int f) {
    fa_[u] = f;
    int x = a_[u];
    if (u == 0 || blocks_[belong_[f]].size() == B) {
      blocks_[belong_[u]=cnt_++].insert(x);
      if (f >= 0) addb(belong_[f], belong_[u]);
      back_[belong_[u]] = (f == -1 ? -1 : belong_[f]);
    } else {
      blocks_[belong_[u]=belong_[f]].insert(x);
    }
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      if (v != f) {
        dfs(v, u);
      }
    }
  }

  int blockDfs(int u, int x) {
    int ans = blocks_[u].query(x);
    for (int eidx = gb_.head[u]; ~eidx; eidx = gb_.E[eidx].next) {
      int v = gb_.E[eidx].to;
      if (back_[v] == u) {
        ans += blockDfs(v, x);
      }
    }
    return ans;
  }

  void modify(int u, int x) {
    blocks_[belong_[u]].modify(a_[u], x);
    a_[u] = x;
  }

  void addNode(int u, int x) {
    a_[n_++] = x;
    add(u, n_-1);
    fa_[n_-1] = u;
    if (blocks_[belong_[u]].size() == B) {
      blocks_[belong_[n_-1]=cnt_++].insert(x);
      addb(belong_[u], belong_[n_-1]);
      back_[cnt_-1] = belong_[u];
    } else {
      blocks_[belong_[n_-1]=belong_[u]].insert(x);
    }
  }

  int query(int u, int x) {
    return query(u, fa_[u], x);
  }

  int query(int u, int f, int x) {
    int ans = 0;
    if (a_[u] > x) ans++;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      if (v != f && fa_[v] == u) {
        if (belong_[v] == belong_[u]) ans += query(v, u, x);
        else ans += blockDfs(belong_[v], x);
      }
    }
    return ans;
  }

  void cut(int u) {
    int f = fa_[u];
    if (f == -1) return;
    if (belong_[u] != belong_[f]) {
      fa_[u] = -1;
      back_[belong_[u]] = -1;
      return;
    }
    stack<int> c, d;
    cut(u, f, c, d);
    belong_[u] = cnt_++;
    while (!c.empty()) {
      int v = c.top();
      blocks_[belong_[f]].erase(a_[v]);
      blocks_[cnt_-1].insert(a_[v]);
      belong_[v] = cnt_-1;
      c.pop();
    }
    while (!d.empty()) {
      int v = d.top();
      addb(cnt_-1, v);
      back_[v] = cnt_-1;
      d.pop();
    }
    fa_[u] = -1;
  }

  void cut(int u, int f, stack<int>& c, stack<int>& d) {
    c.push(u);
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      if (v != f && fa_[v] == u) {
        if (belong_[v] == belong_[u]) cut(v, u, c, d);
        else d.push(belong_[v]);
      }
    }
  }

  int* a_;
 private:
  void alloc() {
    a_ = new int[cap_]{};
    fa_ = new int[cap_]{};
    memset(fa_, -1, cap_*sizeof(int));
    blocks_ = new Block[cap_]{};
    belong_ = new int[cap_]{};
    back_ = new int[cap_]{};
    memset(back_, -1, cap_*sizeof(int));
  }

  void dealloc() {
    delete[] a_;
    delete[] fa_;
    delete[] blocks_;
    delete[] belong_;
    delete[] back_;
  }

  int n_;
  const int cap_;
  const int B;
  Graph g_, gb_;
  int* fa_;
  Block* blocks_;
  int* belong_;
  int cnt_ = 0;
  int* back_; // index of parent block
};

int N, M;

int main() {
  scanf("%d", &N);

  BlockTree bt(N);
  for (int i = 0; i < N-1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    bt.add(u, v);
  }
  for (int i = 0; i < N; i++) {
    scanf("%d", &bt.a_[i]);
  }
  bt.dfs(0, -1);

  int lastans = 0;
  scanf("%d", &M);
  for (int i = 0; i < M; i++) {
    int op, u, x;
    scanf("%d", &op);
    switch (op) {
      case 0:
        scanf("%d%d", &u, &x);
        u ^= lastans;
        x ^= lastans;
        u--;
        printf("%d\n", lastans=bt.query(u, x));
        break;
      case 1:
        scanf("%d%d", &u, &x);
        u ^= lastans;
        x ^= lastans;
        u--;
        bt.modify(u, x);
        break;
      case 2:
        scanf("%d%d", &u, &x);
        u ^= lastans;
        x ^= lastans;
        u--;
        bt.addNode(u, x);
        break;
      case 3:
        scanf("%d", &u);
        u ^= lastans;
        u--;
        bt.cut(u);
        break;
    }
  }

  return 0;
}
