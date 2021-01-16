// https://www.luogu.com.cn/problem/P2787
// 语文1（chin1）- 理理思维

#include <bits/stdc++.h>
using namespace std;

// note it's 1-indexed
class SegmentTree {
  struct Node {
    int cnt[26];
    Node operator + (const Node& other) const {
      Node ret;
      for (int i = 0; i < 26; i++) {
        ret.cnt[i] = cnt[i] + other.cnt[i];
      }
      return ret;
    }
  };

  int N;
  int *flag_;
  Node *nodes_;

 public:
  SegmentTree(int N_): N(N_) {
    flag_ = new int[4*N+1]{};
    memset(flag_, -1, (4*N+1)*sizeof(int));
    nodes_ = new Node[4*N+1]{};
  }

  ~SegmentTree() {
    delete[] flag_;
    delete[] nodes_;
  }

  void build(int* a) {
    build(1, 0, N-1, a);
  }

  void update(int a, int b, int c) {
    assert(0 <= c && c < 26);
    assert(0 <= a && a <= b && b < N);
    update(1, c, 0, N-1, a, b);
  }

  int query(int a, int b, int c) {
    return query(1, 0, N-1, a, b).cnt[c];
  }

  void sort(int a, int b) {
    Node node = query(1, 0, N-1, a, b);
    int curr = a;
    for (int i = 0; i < 26; i++) {
      if (node.cnt[i] > 0) {
        update(curr, curr+node.cnt[i]-1, i);
        curr = curr + node.cnt[i];
      }
    }
    assert(curr == b+1);
  }

 private:
  void build(int k, int l, int r, int* a) {
    if (l == r) {
      memset(nodes_[k].cnt, 0, 26*sizeof(int));
      nodes_[k].cnt[a[l]] = 1;
      return;
    }
    int mid = (l + r) / 2;
    build(2*k, l, mid, a);
    build(2*k+1, mid+1, r, a);
    pushUp(k);
  }

  void update(int k, int t, int l, int r, int a, int b) {
    pushDown(k, l, r);
    if (a <= l && r <= b) {
      memset(nodes_[k].cnt, 0, 26*sizeof(int));
      nodes_[k].cnt[t] = r - l + 1;
      flag_[k] = t;
      return;
    }
    int mid = (l + r) / 2;
    if (a <= mid) update(2*k, t, l, mid, a, b);
    if (mid < b) update(2*k+1, t, mid+1, r, a, b);
    pushUp(k);
  }

  void pushDown(int k, int l, int r) {
    if (flag_[k] == -1 || l == r) return;
    int t = flag_[k];
    flag_[2*k] = flag_[2*k+1] = t;
    int mid = (l + r) / 2;
    memset(nodes_[2*k].cnt, 0, 26*sizeof(int));
    nodes_[2*k].cnt[t] = mid - l + 1;
    memset(nodes_[2*k+1].cnt, 0, 26*sizeof(int));
    nodes_[2*k+1].cnt[t] = r - mid;
    flag_[k] = -1;
  }

  void pushUp(int k) {
    for (int i = 0; i < 26; i++) {
      nodes_[k].cnt[i] = nodes_[2*k].cnt[i] + nodes_[2*k+1].cnt[i];
    }
  }

  Node query(int k, int l, int r, int a, int b) {
    pushDown(k, l, r);
    if (a <= l && r <= b) return nodes_[k];
    int mid = (l + r) / 2;
    if (b <= mid) return query(2*k, l, mid, a, b);
    if (a > mid) return query(2*k+1, mid+1, r, a, b);
    return query(2*k, l, mid, a, b) + query(2*k+1, mid+1, r, a, b);
  }
};

const int MAXN = 50010;
int A[MAXN];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  string s;
  cin >> s;
  for (int i = 0; i < n; i++) {
    A[i] = tolower(s[i]) - 'a';
  }
  SegmentTree st(n);
  st.build(A);
  int op, x, y;
  char ch[5];
  for (int i = 0; i < m; i++) {
    scanf("%d%d%d", &op, &x, &y);
    x--; y--;
    if (op == 1) {
      scanf("%s", ch);
      int c = tolower(ch[0])-'a';
      printf("%d\n", st.query(x, y, c));
    } else if (op == 2) {
      scanf("%s", ch);
      int c = tolower(ch[0])-'a';
      st.update(x, y, c);
    } else {
      st.sort(x, y);
    }
  }

  return 0;
}
