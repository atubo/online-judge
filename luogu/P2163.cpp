// https://www.luogu.com.cn/problem/P2163
// [SHOI2007]园丁的烦恼

#include <bits/stdc++.h>
using namespace std;

class PersistentSegmentTree {
public:
    struct Node {
        // L and R are indices of its children
        // real left and right boundaries are not kept in the node
        // to save memory
        int L, R;
        int sum;

        Node(): L(0), R(0), sum(0) {}
    };

    int N; // number of positions, index is 1-based
    int M; // number of weights, index is 0-based
    int *root;
    Node *T;
    int T_cnt = 1;

    PersistentSegmentTree(int N_, int M_): N(N_), M(M_) {
        root = new int[N+1]{};
        T = new Node[(N+1) * int(log2(M)+2)]{};
    }

    ~PersistentSegmentTree() {
        delete[] root;
        delete[] T;
    }

    // for user's convenience
    void insert(int currRootIndex, int prevRootIndex, int x, int t) {
        root[currRootIndex] = root[prevRootIndex];
        insert(root[currRootIndex], x, t, 0, M-1);
    }

    // query in range [start, end]
    int query(int rootIndex, int start, int end) const {
      if (end < start) return 0;
      return query(root[rootIndex], start, end, 0, M-1);
    }

private:
    // insert a new weight node x with value t
    // current range is [l, r]
    void insert(int &now, int x, int t, int l, int r) {
        T[T_cnt++] = T[now];
        now = T_cnt-1;
        T[now].sum += t;
        if (l == r) return;
        int mid = (l + r) / 2;
        if (x <= mid) insert(T[now].L, x, t, l, mid);
        else          insert(T[now].R, x, t, mid+1, r);
    }

    int query(int node, int start, int end, int l, int r) const {
        if (l > r) return 0;
        if (start <= l && r <= end) return T[node].sum;
        int mid = (l + r) / 2;
        int ret = 0;
        if (start <= mid) ret += query(T[node].L, start, end, l, mid);
        if (mid+1 <= end) ret += query(T[node].R, start, end, mid+1, r);
        return ret;
    }
};

const int MAXN = 500010;
int N, M;

struct Point {
  int x, y;
  bool operator < (const Point& other) const {
    if (x != other.x) return x < other.x;
    return y < other.y;
  }
} P[MAXN];

int main() {
  scanf("%d%d", &N, &M);
  vector<int> ys;
  for (int i = 1; i <= N; i++) {
    scanf("%d%d", &P[i].x, &P[i].y);
    ys.push_back(P[i].y);
  }
  sort(ys.begin(), ys.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());

  sort(P+1, P+N+1);
  for (int i = 1; i <= N; i++) {
    P[i].y = lower_bound(ys.begin(), ys.end(), P[i].y) - ys.begin();
  }

  PersistentSegmentTree pst(N, ys.size());

  for (int i = 1; i <= N; i++) {
    pst.insert(i, i-1, P[i].y, 1);
  }

  for (int i = 0; i < M; i++) {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    int x1 = lower_bound(P+1, P+N+1, Point{a, -1}) - P;
    int y1 = lower_bound(ys.begin(), ys.end(), b) - ys.begin();
    int x2 = upper_bound(P+1, P+N+1, Point{c+1, -1}) - P - 1;
    int y2 = upper_bound(ys.begin(), ys.end(), d) - ys.begin() - 1;
    int ans = pst.query(x2, y1, y2) - pst.query(x1-1, y1, y2);
    printf("%d\n", ans);
  }

  return 0;
}
