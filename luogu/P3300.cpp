// https://www.luogu.com.cn/problem/P3300
// [SDOI2013]城市规划

#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
  struct Node {
    Node(): sum(0) {
      memset(l, 0, 7*sizeof(char));
      memset(r, 0, 7*sizeof(char));
      memset(father, 0, 13*sizeof(int));
      memset(building, 0, 13*sizeof(bool));
    }
    int sum;
    char l[7], r[7];
    mutable int father[13];
    bool building[13];
    int find(int now) const {
      if (father[now] == now) return now;
      return father[now] = find(father[now]);
    }

    void add(int a, int b) {
      // merge a to b
      building[find(b)] |= building[find(a)];
      father[find(a)] = find(b);
    }
  };

 public:
  Node merge(const Node& ln, const Node& rn) {
    Node t;
    for (int i = 1; i <= m_; i++) {
      t.l[i] = ln.l[i];
      t.r[i] = rn.r[i];
      t.building[i] = t.building[i+m_] = 0;
      t.father[i] = i;
      t.father[i+m_] = i+m_;
    }
    t.sum = ln.sum + rn.sum;
    for (int i = 1; i <= m_; i++) {
      father_[i] = ln.find(i);
      father_[i+m_] = ln.find(i+m_);
      father_[i+m_*2] = rn.find(i) + 2*m_;
      father_[i+m_*3] = rn.find(i+m_) + 2*m_;
      building_[i] = ln.building[father_[i]];
      building_[i+m_] = ln.building[father_[i+m_]];
      building_[i+m_*2] = rn.building[father_[i+m_*2]-2*m_];
      building_[i+m_*3] = rn.building[father_[i+m_*3]-2*m_];
    }
    for (int i= 1; i <= m_; i++) {
      if (checkV(ln.r[i]) && checkV(rn.l[i]) && find(i+m_) != find(i+2*m_)) {
        if (building_[find(i+m_)] && building_[find(i+2*m_)]) {
          t.sum--;
        }
        building_[find(i+2*m_)] |= building_[find(i+m_)];
        father_[find(i+m_)] = find(i+2*m_);
      }
    }

    memset(f_, 0, 30*sizeof(int));
    for (int i = 1; i <= m_; i++) {
      if (!f_[find(i)]) {
        t.father[i] = f_[find(i)] = i;
        t.building[i] = building_[find(i)];
      } else {
        t.father[i] = f_[find(i)];
      }
    }

    for (int i = m_+1; i <= 2*m_; i++) {
      if (!f_[find(2*m_+i)]) {
        t.father[i] = f_[find(2*m_+i)] = i;
        t.building[i] = building_[find(2*m_+i)];
      } else {
        t.father[i] = f_[find(2*m_+i)];
      }
    }
    return t;
  }

  Node merge(int k, int l, int r) {
    if (l == r) return nodes_[k];
    return merge(nodes_[2*k], nodes_[2*k+1]);
  }

  void pushUp(int k, int l, int r) {
    nodes_[k] = merge(k, l, r);
  }

  void build(int k, int l, int r, char arr[][10]) {
    if (l == r) {
      buildLeaf(k, l, arr);
      return;
    }
    int mid = (l + r) / 2;
    build(2*k, l, mid, arr);
    build(2*k+1, mid+1, r, arr);
    pushUp(k, l, r);
  }

  void buildLeaf(int k, int l, char arr[][10]) {
    for (int i = 1; i <= m_; i++) {
      nodes_[k].l[i] = nodes_[k].r[i] = arr[l][i];
      nodes_[k].building[i] = nodes_[k].building[i+m_] = 0;
      nodes_[k].father[i] = nodes_[k].father[i+m_] = i;
    }
    for (int i = 2; i <= m_; i++) {
      if (checkH(arr[l][i-1]) && checkH(arr[l][i])) {
        nodes_[k].add(i-1, i);
      }
    }
    for (int i = 1; i <= m_; i++) {
      if (arr[l][i] == 'O') {
        nodes_[k].building[nodes_[k].find(i)] = 1;
      }
    }
    nodes_[k].sum = nodes_[k].building[nodes_[k].find(1)];
    for (int i = 2; i <= m_; i++) {
      if (nodes_[k].find(i-1) != nodes_[k].find(i)) {
        nodes_[k].sum += nodes_[k].building[nodes_[k].find(i)];
      }
    }
  }

  void update(int k, int l, int r, int x, char arr[][10]) {
    if (l == r) {
      buildLeaf(k, l, arr);
      return;
    }
    int mid = (l + r) / 2;
    if (x <= mid) update(2*k, l, mid, x, arr);
    else update(2*k+1, mid+1, r, x, arr);
    pushUp(k, l, r);
  }

  Node query(int k, int l, int r, int a, int b) {
    assert(l <= a && b <= r);
    if (l == a && r == b) return nodes_[k];
    int mid = (l + r) / 2;
    if (b <= mid) return query(2*k, l, mid, a, b);
    if (mid < a) return query(2*k+1, mid+1, r, a, b);
    return merge(query(2*k, l, mid, a, mid), query(2*k+1, mid+1, r, mid+1, b));
  }

  SegmentTree(int n, int m) : n_(n), m_(m) {
    alloc();
  }

  ~SegmentTree() {
    dealloc();
  }

  void build(char arr[][10]) {
    build(1, 1, n_, arr);
  }

  Node query(int a, int b) {
    return query(1, 1, n_, a, b);
  }

  void update(int x, char arr[][10]) {
    update(1, 1, n_, x, arr);
  }

 private:
  void alloc() {
    nodes_ = new Node[4*n_+1];
    memset(f_, 0, 30*sizeof(int));
    memset(building_, 0, 30*sizeof(bool));
  }

  void dealloc() {
    delete[] nodes_;
  }

  bool checkH(char c) const {
    return c == '+' || c == 'O' || c == '-';
  }

  bool checkV(char c) const {
    return c == '+' || c == 'O' || c == '|';
  }

  int find(int now) {
    if (father_[now] == now) return now;
    return father_[now] = find(father_[now]);
  }

  Node *nodes_;
  int n_;
  int m_;
  int father_[30], f_[30];
  bool building_[30];
};

const int MAXN = 100010;
const int MAXM = 10;
char A[MAXN][MAXM];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
   scanf("%s", A[i]+1);
  }
  SegmentTree st(n, m);
  st.build(A);
  int q;
  scanf("%d", &q);
  char opt, ch;
  int x, y;
  for (int i = 0; i < q; i++) {
    cin >> opt;
    if (opt == 'Q') {
      scanf("%d%d", &x, &y);
      printf("%d\n", st.query(x, y).sum);
    } else {
      scanf("%d%d", &x, &y);
      cin >> ch;
      A[x][y] = ch;
      st.update(x, A);
    }
  }

  return 0;
}
