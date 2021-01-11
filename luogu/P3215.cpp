// https://www.luogu.com.cn/problem/P3215
// [HNOI2011]括号修复 / [JSOI2011]括号序列

#include <bits/stdc++.h>
using namespace std;

#define MIN(a, b) ((a) < (b) ? a : b)
#define MAX(a, b) ((a) > (b) ? a : b)
#define SWAP(a, b) {int tmp=a; a=b; b=tmp;}

// index starts from 1 (0 is for NULL)
class SplayTree {
public:
    static const int MAXINT = 0x3f3f3f3f;

    SplayTree(int size, int *a = NULL, int cap = 0) {
        // 1-indexed
        if (cap == 0) cap = size + 1;
        assert(cap >= size + 1);
        alloc(cap);
        init(size, a);
    }

    ~SplayTree() {
      dealloc();
    }

    void init(int size, int *a) {
        N = size;

        psMin[0] = qsMin[0] = MAXINT;
        psMax[0] = qsMax[0] = -MAXINT;
        root = build(1, N, 0, a);
    }

    // build range [i, j]
    int build(int p, int q, int fa, int *a) {
        if (p > q) return 0;
        assert(q - p >= 0);

        int mid = (p + q) / 2;
        initNode(mid, fa, (a ? a[mid] : 0));

        t[mid][0] = build(p, mid-1, mid, a);
        t[mid][1] = build(mid+1, q, mid, a);

        pushUp(mid);

        return mid;
    }

    int buildSingleNode(int p, int fa, int v) {
        initNode(p, fa, v);
        pushUp(p);
        return p;
    }

    void pushUp(int x) {
      assert(x);

      sz[x] = sz[t[x][0]] + sz[t[x][1]] + 1;
      int l = t[x][0], r = t[x][1];
      psMin[x] = min(psMin[l], tot[l] + val[x] + MIN(0, psMin[r]));
      psMax[x] = max(psMax[l], tot[l] + val[x] + MAX(0, psMax[r]));
      qsMin[x] = min(qsMin[r], tot[r] + val[x] + MIN(0, qsMin[l]));
      qsMax[x] = max(qsMax[r], tot[r] + val[x] + MAX(0, qsMax[l]));
      tot[x] = tot[l] + val[x] + tot[r];
    }

    void pushDown(int x) {
      if (tagr[x]) {
        updateReplace(t[x][0], tagr[x]);
        updateReplace(t[x][1], tagr[x]);
        tagr[x] = 0;
      }
      if (tags[x]) {
        updateSwap(t[x][0]);
        updateSwap(t[x][1]);
        tags[x] = false;
      }
      if (tagi[x]) {
        updateInvert(t[x][0]);
        updateInvert(t[x][1]);
        tagi[x] = false;
      }
    }

    bool son(int x) const {
        return t[f[x]][0] == x ? 0 : 1;
    }

    void rotate(int x) {
        int y = f[x], z = son(x);

        pushDown(y);
        pushDown(x);

        t[y][z] = t[x][1-z];
        if (t[x][1-z]) f[t[x][1-z]] = y;

        f[x] = f[y];
        if (f[x]) t[f[x]][son(y)] = x;

        f[y] = x; t[x][1-z] = y;
        pushUp(y);
    }

    void splay(int x, int y) {
        if (x == y) return;
        pushDown(x);
        while (f[x] != y) {
            if (f[f[x]] != y) {
                if (son(f[x]) == son(x)) rotate(f[x]);
                else rotate(x);
            }
            rotate(x);
        }
        pushUp(x);
        if (!y) root = x;
    }

    // find k-th element (starting from 1)
    int find_by_order(int k) {
        assert(1 <= k && k <= N);
        int x = root;
        while (true) {
            pushDown(x);
            if (sz[t[x][0]] == k-1) return x;
            if (sz[t[x][0]] < k-1) {
                k -= sz[t[x][0]] + 1;
                x = t[x][1];
            } else {
                x = t[x][0];
            }
        }
        assert(false);
        return x;
    }

    void inorder(int x) {
      pushDown(x);
      if (t[x][0]) inorder(t[x][0]);
      printf("%d ", val[x]);
      if (t[x][1]) inorder(t[x][1]);
    }

    void replace(int c) {
      assert(c == 1 || c == -1);
      int y = t[root][1];
      int x = t[y][0];
      updateReplace(x, c);
      pushUp(y);
      pushUp(root);
    }

    void swap() {
      int y = t[root][1];
      int x = t[y][0];
      updateSwap(x);
      pushUp(y);
      pushUp(root);
    }

    void invert() {
      int y = t[root][1];
      int x = t[y][0];
      updateInvert(x);
      pushUp(y);
      pushUp(root);
    }

    int query() {
      int y = t[root][1];
      int x = t[y][0];
      int x1 = max(0, (-psMin[x] + 1) / 2);
      int x2 = tot[x]/2 + x1;
      return x1 + x2;
    }

    int root;
    int N;  // number of elements, 0 (NULL) excluded
    int *f;
    int **t;

    int *sz;
    int *val;
    int *psMin, *psMax;
    int *qsMin, *qsMax;
    int *tot;
    int *tagr;
    bool *tags, *tagi;

private:
    void alloc(int cap) {
      f = new int[cap]{};
      t = new int*[cap]{};
      for (int i = 0; i < cap; i++) t[i] = new int[2]{};

      sz = new int[cap]{};
      val = new int[cap]{};
      psMin = new int[cap]{};
      psMax = new int[cap]{};
      qsMin = new int[cap]{};
      qsMax = new int[cap]{};
      tot = new int[cap]{};
      tagr = new int[cap]{};
      tags = new bool[cap]{};
      tagi = new bool[cap]{};
    }

    void dealloc() {
      delete[] f;
      for (int i = 0; i < N+1; i++) delete[] t[i];
      delete[] t;
      delete[] sz;
      delete[] val;
      delete[] psMin;
      delete[] psMax;
      delete[] qsMin;
      delete[] qsMax;
      delete[] tot;
      delete[] tagr;
      delete[] tags;
      delete[] tagi;
    }

    void initNode(int p, int fa, int v) {
        f[p] = fa;
        val[p] = v;
        psMin[p] = psMax[p] = qsMin[p] = qsMax[p] = tot[p] = v;
        t[p][0] = t[p][1] = 0;
    }

    void updateReplace(int x, int c) {
      if (!x) return;
      val[x] = c;
      psMin[x] = qsMin[x] = min(c, c * sz[x]);
      psMax[x] = qsMax[x] = max(c, c * sz[x]);
      tot[x] = c * sz[x];

      tagr[x] = c;
      tags[x] = false;
      tagi[x] = false;
    }

    void updateSwap(int x) {
      if (!x) return;

      SWAP(t[x][0], t[x][1]);
      SWAP(psMin[x], qsMin[x]);
      SWAP(psMax[x], qsMax[x]);
      tags[x] = !tags[x];
    }

    void updateInvert(int x) {
      if (!x) return;
      std::swap(psMin[x], psMax[x]);
      psMin[x] = -psMin[x];
      psMax[x] = -psMax[x];
      std::swap(qsMin[x], qsMax[x]);
      qsMin[x] = -qsMin[x];
      qsMax[x] = -qsMax[x];
      tot[x] = -tot[x];
      val[x] = -val[x];

      tagi[x] = !tagi[x];
    }

};

const int MAXN = 100010;
int N, Q;
int A[MAXN];

int main() {
  scanf("%d%d", &N, &Q);
  string s;
  cin >> s;
  for (int i = 2; i <= N+1; i++) {
    A[i] = (s[i-2] == '(' ? 1 : -1);
  }
  SplayTree st(N+2, A);
  char op[10], c[5];
  int a, b;
  for (int i = 0; i < Q; i++) {
    scanf("%s%d%d", op, &a, &b);
    int x = st.find_by_order(a);
    int y = st.find_by_order(b+2);
    st.splay(x, 0);
    st.splay(y, x);
    if (op[0] == 'R') {
      scanf("%s", c);
      st.replace(c[0] == '(' ? 1 : -1);
    } else if (op[0] == 'S') {
      st.swap();
    } else if (op[0] == 'I') {
      st.invert();
    } else {
      printf("%d\n", st.query());
    }
  }
  return 0;
}
