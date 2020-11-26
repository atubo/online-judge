// https://www.luogu.com.cn/problem/P4150
// [WC2009]最短路问题

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int D[6][MAXN];

class SegmentTree {
  int N;
  static const int INF = 0x3F3F3F3F;

  static int min3(int a, int b, int c) {
    return min(a, min(b, c));
  }

  struct Node {
    int ll[6][6], rr[6][6], lr[6][6];
    void merge(const Node& lc, const Node& rc) {
      static int lm[6][6], rm[6][6];
      memset(lm, 0x3f, sizeof(lm));
      memset(rm, 0x3f, sizeof(rm));
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
          for (int k = 0; k < 6; k++) {
            lm[i][j] = min(lm[i][j],
                lc.lr[i][k] + rc.ll[k][j] + lc.rr[j][j]);
            rm[i][j] = min(rm[i][j],
                rc.ll[i][i] + lc.rr[i][k] + rc.lr[k][j]);
          }
        }
      }
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
          ll[i][j] = lc.ll[i][j];
          rr[i][j] = rc.rr[i][j];
          lr[i][j] = INF;
          for (int k = 0; k < 6; k++) {
            ll[i][j] = min(ll[i][j],
                lm[i][k] + lc.lr[j][k] - lc.rr[k][k]);
            rr[i][j] = min(rr[i][j],
                rc.lr[k][i] + rm[k][j] - rc.ll[k][k]);
            lr[i][j] =
                min3(lr[i][j],
                    lm[i][k] + rm[k][j] - lc.rr[k][k] - rc.ll[k][k],
                    lc.lr[i][k] + rc.lr[k][j]);
          }
        }
      }
    }
  };

  Node *nodes;

 public:
  SegmentTree(int N_): N(N_) {
    nodes = new Node[4*N+1]{};
    build(1, 0, N-1);
  }

  ~SegmentTree() {
    delete[] nodes;
  }

  void update(int x, int y, int t) {
    D[x][y] = t;
    update(1, 0, N-1, y);
  }

  int solve(int x1, int y1, int x2, int y2) const {
    if (y1 > y2) {
      swap(x1, x2);
      swap(y1, y2);
    }
    Node l = query(0, y1);
    Node mid = query(y1, y2);
    Node r = query(y2, N-1);
    int ans = INF;
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 6; j++) {
        for (int k = 0; k < 6; k++) {
          for (int p = 0; p < 6; p++) {
            int t = mid.ll[x1][i] + l.rr[i][j] + mid.lr[j][k] +
                r.ll[k][p] + mid.rr[p][x2] - mid.ll[i][i] - mid.ll[j][j]
                - mid.rr[k][k] - mid.rr[p][p];
            ans = min(ans, t);
          }
        }
      }
    }
    return ans;
  }
 private:

  void pushUp(int k, int l, int r) {
    if (l == r) return;
    nodes[k].merge(nodes[2*k], nodes[2*k+1]);
  }

  void calc(int k, int l) {
    int sum[6];
    for (int i = 0; i < 6; i++) {
      sum[i] = D[i][l] + (i ? sum[i-1] : 0);
    }
    for (int i = 0; i < 6; i++) {
      for (int j = i; j < 6; j++) {
        nodes[k].ll[i][j] = nodes[k].rr[i][j] = nodes[k].lr[i][j] =
        nodes[k].ll[j][i] = nodes[k].rr[j][i] = nodes[k].lr[j][i] =
            sum[j] - (i ? sum[i-1] : 0);
      }
    }
  }

  void build(int k, int l, int r) {
    if (l == r) {
      calc(k, l);
      return;
    }
    int mid = (l + r) / 2;
    build(2*k, l, mid);
    build(2*k+1, mid+1, r);
    pushUp(k, l, r);
  }

  void update(int k, int l, int r, int x) {
    if (l == r) {
      calc(k, l);
      return;
    }
    int mid = (l + r) / 2;
    if (x <= mid) update(2*k, l, mid, x);
    else update(2*k+1, mid+1, r, x);
    pushUp(k, l, r);
  }

  Node query(int a, int b) const {
    return query(1, 0, N-1, a, b);
  }

  Node query(int k, int l, int r, int a, int b) const {
    if (a <= l && r <= b) return nodes[k];
    int mid = (l + r) / 2;
    if (b <= mid) return query(2*k, l, mid, a, b);
    if (a > mid) return query(2*k+1, mid+1, r, a, b);
    Node ret;
    ret.merge(query(2*k, l, mid, a, b), query(2*k+1, mid+1, r, a, b));
    return ret;
  }
};

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &D[i][j]);
    }
  }
  SegmentTree st(n);
  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; i++) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      int x, y, c;
      scanf("%d%d%d", &x, &y, &c);
      x--; y--;
      st.update(x, y, c);
    } else {
      int x1, y1, x2, y2;
      scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
      x1--; y1--; x2--; y2--;
      int ans = st.solve(x1, y1, x2, y2);
      printf("%d\n", ans);
    }
  }
  return 0;
}
