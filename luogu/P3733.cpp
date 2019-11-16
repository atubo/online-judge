// https://www.luogu.org/problem/P3733
// [HAOI2017]八纵八横

#include <bits/stdc++.h>
using namespace std;

const int MX = 1000;
typedef bitset<1005> bt;
typedef vector<bt> BitsetVec;

string toString(const bt& x) {
  int i;
  for (i = MX; i >= 0; i--) {
    if (x[i]) break;
  }
  if (i < 0) return "0";
  string ret;
  for (int j = i; j >= 0; j--) {
    ret.push_back('0' + int(x[j]));
  }
  return ret;
}

struct XorBase {
  bt b[1005];
  void insert(bt x) {
    if (!x.any()) return;
    for (int i = MX; i >= 0; i--) {
      if (!x[i]) continue;
      if (!b[i].any()) {
        b[i] = x;
        break;
      }
      x ^= b[i];
    }
  }
};

void readBT(bt& x) {
  string s;
  cin >> s;
  for (int i = 0; i < (int)s.length(); i++) {
    x[i] = s[s.length()-1-i] - '0';
  }
}

void printans(const XorBase& base) {
  bt x;
  int i;
  for (i = MX; i >= 0; i--) {
    if (base.b[i].any()) break;
  }
  if (i < 0) {
    printf("0\n");
    return;
  }
  int pos = i;
  for (int j = i; j >= 0; j--) {
    if (base.b[i].any() && !x[j]) x ^= base.b[j];
  }
  for (i = pos; i >= 0; i--) {
    printf("%d", (int)x[i]);
  }
  printf("\n");
}

// note it's 1-indexed
class SegmentTree {
    int N;
    BitsetVec* val = NULL;

public:
    SegmentTree(int N_): N(N_) {
        val = new BitsetVec[4*N+1]{};
    }

    ~SegmentTree() {
        delete[] val;
    }
    // add t to range [a, b]
    void update(const bt& t, int a, int b) {
      update(1, t, 1, N, a, b);
    }

    void query(XorBase base) {
        return query(1, 1, N, base);
    }

private:
    // add t to range [a, b], current node range is [l, r]
    void update(int k, const bt& t, int l, int r, int a, int b) {
        if (a > b) return;
        if (a <= l && r <= b) {
            val[k].push_back(t);
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
    }

    // query range sum in [a, b], current node is [l, r]
    void query(int k, int l, int r, XorBase x) {
        if (!k || r < l) return;
        for (const auto& b: val[k]) {
          x.insert(b);
        }

        if (l == r) {
          printans(x);
          return;
        }

        int mid = (l + r) / 2;
        query(2*k, l, mid, x);
        query(2*k+1, mid+1, r, x);
    }
};

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
        bt wt;
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
    void addEdge(int u, int v, const bt& w) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].wt = w;
        head[u] = eidx++;
    }
};

const int MAXN = 512;
bool vis[MAXN];
bt D[MAXN];

void dfs(const Graph& g, int u, int fa, bt&& x, XorBase& xbase) {
  D[u] = x;
  vis[u] = true;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    const bt& w = g.E[eidx].wt;
    if (v != fa) {
      if (!vis[v]) {
        dfs(g, v, u, D[u]^w, xbase);
      } else {
        xbase.insert(D[u]^D[v]^w);
      }
    }
  }
}

int N, M, Q;
int pre[1024];

struct Edge {
  int u, v;
  bt w;
} E[1024];

int main() {
  scanf("%d%d%d", &N, &M, &Q);
  Graph g(N, 2*M);
  for (int i = 0; i < M; i++) {
    int u, v;
    bt w;
    scanf("%d%d", &u, &v);
    u--; v--;
    readBT(w);
    g.addEdge(u, v, w);
    g.addEdge(v, u, w);
  }
  XorBase xbase;
  dfs(g, 0, -1, bt(), xbase);
  SegmentTree st(Q);

  int top = 0;
  for (int i = 1; i <= Q; i++) {
    char s[80];
    int u;
    scanf("%s", s);
    if (s[0] == 'C') {
      scanf("%d", &u);
      st.update(D[E[u].u]^D[E[u].v]^E[u].w, pre[u], i-1);
      if (s[1] == 'h') {
        pre[u] = i;
        E[u].w.reset();
        readBT(E[u].w);
      } else {
        pre[u] = 0;
      }
    } else {
      pre[++top] = i;
      scanf("%d%d", &E[top].u, &E[top].v);
      E[top].u--; E[top].v--;
      readBT(E[top].w);
    }
  }

  for (int i = 1; i <= top; i++) {
    if (pre[i]) {
      st.update(D[E[i].u]^D[E[i].v]^E[i].w, pre[i], Q);
    }
  }
  printans(xbase);
  if (Q) {
    st.query(xbase);
  }

  return 0;
}
