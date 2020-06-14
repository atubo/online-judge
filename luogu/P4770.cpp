// https://www.luogu.com.cn/problem/P4770
// [NOI2018]你的名字

#include <bits/stdc++.h>
using namespace std;

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

class SuffixAutomaton {
  // state index is from 1. 0 is reserved for null
  // state n+1 is root
 public:
  int** mp;
  int ct = 0;
  int *fa;
  int *len;
  int n;
  int *id;

  SuffixAutomaton(int nn): n(nn) {
    alloc();
    for (int i = 1; i <= n; i++) {
      len[i] = i;
      id[i] = i;
    }
    ct = n + 1;
  }

  ~SuffixAutomaton() {
    dealloc();
  }

  void build(const string& s) {
    for (int i = 1; i <= n; i++) {
      extend(i, s[i-1] - 'a');
    }
  }

 private:
  void alloc() {
    int cap = 2*n + 1;
    mp = new int*[cap]{};
    for (int i = 0; i < cap; i++) {
      mp[i] = new int[26]{};
    }
    fa = new int[cap]{};
    len = new int[cap]{};
    id = new int[cap]{};
  }

  void dealloc() {
    for (int i = 0; i < 2*n+1; i++) {
      delete[] mp[i];
    }
    delete[] mp;
    delete[] fa;
    delete[] len;
    delete[] id;
  }

  void extend(int x, int c) {
    // index x is from 1
    int p = (x == 1) ? n+1 : x-1;
    for (; p && mp[p][c] == 0; p = fa[p]) mp[p][c] = x;
    if (p == 0) {
      fa[x] = n + 1;
      return;
    }
    int q = mp[p][c];
    if (len[q] == len[p] + 1) {
      fa[x] = q;
      return;
    }
    len[++ct] = len[p] + 1;
    id[ct] = id[q];
    for (int i = 0; i < 26; i++) {
      mp[ct][i] = mp[q][i];
    }
    for (; p && mp[p][c] == q; p = fa[p]) {
      mp[p][c] = ct;
    }
    fa[ct] = fa[q];
    fa[q] = fa[x] = ct;
  }
};

//const int N = 1e6+10;

class SegmentTree {
 public:
  int cnt = 0;;
  SuffixAutomaton* sam = NULL;

  SegmentTree(int n): n_(n) {
    alloc();
  }

  ~SegmentTree() {
    dealloc();
    delete sam;
    sam = NULL;
  }

  void ins(int p, int l, int r, int pos) {
    if (l == r) return;
    int mid = (l + r) / 2;
    if (pos <= mid) {
      ins(ls[p]=++cnt, l, mid, pos);
    } else {
      ins(rs[p]=++cnt, mid+1, r, pos);
    }
  }

  int merge(int p1, int p2, bool isRoot) {
    int nw = (isRoot ? p1 : ++cnt);
    if (ls[p1] && ls[p2]) {
      ls[nw] = merge(ls[p1], ls[p2], 0);
    } else {
      ls[nw] = ls[p2] ? ls[p2] : ls[p1];
    }
    if (rs[p1] && rs[p2]) {
      rs[nw] = merge(rs[p1], rs[p2], 0);
    } else {
      rs[nw] = rs[p2] ? rs[p2] : rs[p1];
    }
    return nw;
  }

  int query(int p, int l, int r, int dl, int dr) const {
    if (!p) return 0;
    if (dl <= l && r <= dr) return 1;
    int mid = (l + r) / 2;
    if (dl <= mid && query(ls[p], l, mid, dl, dr)) return 1;
    if (mid < dr && query(rs[p], mid+1, r, dl, dr)) return 1;
    return 0;
  }

  void dfs(const Graph& g, int u) {
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
      int v = g.E[eidx].to;
      dfs(g, v);
      merge(u, v, true);
    }
  }

  void build(const string& str) {
    int n = str.length();
    sam = new SuffixAutomaton(n);
    sam->build(str);
    cnt = sam->ct;
    Graph g(sam->ct+1, sam->ct);
    for (int i = 1; i <= sam->ct; i++) {
      g.addEdge(sam->fa[i], i);
    }

    for (int i = 1; i <= n; i++) {
      ins(i, 1, n, i);
    }
    dfs(g, n+1);
  }

 private:
  int n_;

  int* ls;
  int* rs;

  void alloc() {
    ls = new int[40*n_]{};
    rs = new int[40*n_]{};
  }

  void dealloc() {
    delete[] ls;
    delete[] rs;
  }
};

class Solution {
 public:
  void solve(const SegmentTree& sm, const string& s, int n) {
    int nl, nr;
    scanf("%d%d", &nl, &nr);

    const int m = s.length();
    SuffixAutomaton sam(m);
    sam.build(s);

    vector<int> l(sam.ct+1, 0);
    int len = 0;
    int o = n+1;
    for (int i = 1; i <= (int)s.length(); i++) {
      int c = s[i-1] - 'a';
      while (true) {
        if (sm.sam->mp[o][c] && sm.query(sm.sam->mp[o][c], 1, n, nl+len, nr)) {
          o = sm.sam->mp[o][c];
          len++;
          break;
        }
        if (len == 0) break;
        len--;
        if (len == sm.sam->len[sm.sam->fa[o]]) {
          o = sm.sam->fa[o];
        }
      }
      l[i] = len;
    }
    int64_t ans = 0;
    for (int i = 1; i <= sam.ct; i++) {
      ans += max(0, sam.len[i] - max(sam.len[sam.fa[i]], l[sam.id[i]]));
    }
    printf("%ld\n", ans);
  }
};

int main() {
  string s;
  cin >> s;
  SegmentTree st(s.length());
  st.build(s);
  int m;
  scanf("%d", &m);
  while (m--) {
    string t;
    cin >> t;
    Solution sol;
    sol.solve(st, t, s.length());
  }

  return 0;
}
