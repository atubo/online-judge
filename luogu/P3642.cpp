// https://www.luogu.com.cn/problem/P3642
// [APIO2016]烟火表演

#include <bits/stdc++.h>
using namespace std;

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

template <class Cmp = less<int64_t>>
// nodes are 1-indexed
class LeftistTree {
public:

    LeftistTree(int size) {
        N = size;

        f = new int[N+1]{};
        t = new int*[N+1]{};
        for (int i = 0; i <= N; i++) {
          t[i] = new int[2]{};
        }
        val = new int64_t[N+1]{};
        d = new int[N+1];
        memset(d, -1, (N+1) * sizeof(int));
    }

    ~LeftistTree() {
        delete[] f;
        for (int i = 0; i <= N; i++) {
          delete[] t[i];
        }
        delete[] t;
        delete[] val;
        delete[] d;
    }

    void clear(int m) {
        int sz = (m + 1) * sizeof(int);
        memset(f, 0, sz);
        memset(val, 0, sz);
        memset(d, -1, sz);
        for (int i = 0; i <= m; i++) {
            t[i][0] = t[i][1] = 0;
        }
    }

    // build single node
    void build(int x, int64_t v) {
        f[x] = 0;
        t[x][0] = t[x][1] = 0;
        val[x] = v;
        d[x] = 0;
    }

    bool son(int x) const {
        return t[f[x]][0] == x ? 0 : 1;
    }

    // push to tree at root, return new root
    int push(int root, int x, int64_t v) {
        build(x, v);
        if (!root) return x;
        else return merge(root, x);
    }

    int64_t top(int root) const {
        assert(!f[root]);
        return val[root];
    }

    // must be a root, return new root
    int pop(int x) {
        assert(!f[x]);
        int lc = t[x][0], rc = t[x][1];
        if (lc) cut(lc);
        if (rc) cut(rc);
        if (rc) return merge(lc, rc);
        else return lc;
    }

    // merge two trees rooted at x and y, return new root
    int merge(int x, int y) {
        assert(x && y);
        if (cmp(val[y], val[x])) {
            swap(x, y);
        }

        if (t[x][1] == 0) {
            connect(x, y, 1);
        } else if (cmp(val[y], val[t[x][1]])) {
            int rc = t[x][1];
            cut(rc);
            connect(x, y, 1);
            merge(y, rc);
        } else {
            merge(t[x][1], y);
        }

        if (d[t[x][1]] > d[t[x][0]]) {
            swap(t[x][0], t[x][1]);
        }
        d[x] = d[t[x][1]] + 1;
        return x;
    }

    int N;  // number of elements, 0 (NULL) excluded
    int *f;
    int **t;
    int64_t *val;
    int *d;
    Cmp cmp;

private:
    // cut x from its parent
    void cut(int x) {
        assert(x && f[x] && (t[f[x]][son(x)] == x));
        t[f[x]][son(x)] = 0;
        f[x] = 0;
    }

    // connect y as x's child, z = 0 -> left, 1 -> right
    void connect(int x, int y, int z) {
        assert(!f[y] && !t[x][z]);
        f[y] = x;
        t[x][z] = y;
    }
};

using Lefty = LeftistTree<greater<int64_t>>;

const int MAXN = 600010;
int N, M;
int NC[MAXN];
int idx = 1;
int64_t tot;

int shift(Lefty& lt, int root, int nc, int w) {
  for (int i = 0; i < nc-1; i++) {
    root = lt.pop(root);
  }
  int64_t r = lt.top(root);
  root = lt.pop(root);
  int64_t l = lt.top(root);
  root = lt.pop(root);
  root = lt.push(root, idx++, l+w);
  root = lt.push(root, idx++, r+w);
  return root;
}

int dfs(const Graph& g, int u, int f, Lefty& lt) {
  NC[u] = 0;
  int curr = 0;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    int w = g.E[eidx].wt;
    if (v != f) {
      tot += w;
      int r = dfs(g, v, u, lt);
      r = shift(lt, r, NC[v], w);
      NC[u]++;
      if (curr) {
        curr = lt.merge(curr, r);
      } else {
        curr = r;
      }
    }
  }
  if (NC[u] == 0) {
    lt.build(idx++, 0);
    int root = idx - 1;
    root = lt.push(root, idx++, 0);
    return root;
  } else {
    return curr;
  }
}

int64_t solve(Lefty& lt, int root) {
  for (int i = 0; i < NC[1]-1; i++) {
    root = lt.pop(root);
  }
  int64_t ans = 0;
  int64_t pos = lt.top(root);
  int64_t slope = 0;
  while (true) {
    root = lt.pop(root);
    if (!root) {
      ans += slope * pos;
      break;
    }
    ans += slope * (pos - lt.top(root));
    pos = lt.top(root);
    slope++;
  }
  return ans;
}

int main() {
  scanf("%d%d", &N, &M);
  Graph g(N+M+1, N+M-1);
  for (int i = 2; i < N+M+1; i++) {
    int p, c;
    scanf("%d%d", &p, &c);
    g.addEdge(p, i, c);
  }
  Lefty lt(2*M+2*(N+M-1));
  int root = dfs(g, 1, 0, lt);
  printf("%ld\n", tot - solve(lt, root));

  return 0;
}
