// https://www.luogu.com.cn/problem/P4008
// [NOI2003]文本编辑器

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2*1024*1024+10;
int A[MAXN];

// index starts from 1 (0 is for NULL)
class SplayTree {
public:
    static const int MAXINT = 0x3f3f3f3f;

    static int min3(int a, int b, int c) {
        return min(min(a, b), c);
    }

    SplayTree(int size, int *a = NULL, int cap = 0) {
        // 1-indexed
        if (cap == 0) cap = size + 1;
        assert(cap >= size + 1);
        alloc(cap);
        init(size, a);
    }

    void init(int size, int *a) {
        N = size;

        minVal[0] = MAXINT;
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
        minVal[x] = min3(minVal[t[x][0]], val[x], minVal[t[x][1]]);
    }

    void updateRev(int x) {
        if (!x) return;

        swap(t[x][0], t[x][1]);
        tag[x] ^= 1;
    }

    void updateAdd(int x, int D) {
        if (!x) return;

        val[x] += D;
        minVal[x] += D;
        d[x] += D;
    }

    void pushDown(int x) {
        if (tag[x]) {
            updateRev(t[x][0]);
            updateRev(t[x][1]);
            tag[x] = 0;
        }

        if (d[x]) {
            updateAdd(t[x][0], d[x]);
            updateAdd(t[x][1], d[x]);
            d[x] = 0;
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
        if (t[x][0]) inorder(t[x][0]);
        printf("%d ", val[x]);
        if (t[x][1]) inorder(t[x][1]);
    }

    // starting from 1
    int order_of_root() {
        return 1 + sz[t[root][0]];
    }

    void collect(char *c, int& idx) {
      int y = t[root][1];
      int x = t[y][0];
      collect(x, c, idx);
    }

    void collect(int x, char* c, int& idx) {
      if (t[x][0]) {
        collect(t[x][0], c, idx);
      }
      c[idx++] = char(A[x]);
      if (t[x][1]) {
        collect(t[x][1], c, idx);
      }
    }

    // both deletion and insertion must happen on the left child of
    // root's right child
    int del() {
        int y = t[root][1];
        int x = t[y][0];
        t[y][0] = 0;
        pushUp(y);
        pushUp(root);
        f[x] = 0;
        N -= sz[x];
        return x;
    }

    void ins(int x) {
        int y = t[root][1];
        t[y][0] = x;
        f[x] = y;
        pushUp(y);
        pushUp(root);
        N += sz[x];
    }

    void print() {
        printf("f: ");
        for (int i = 0; i <= N; i++) {
            printf("%d ", f[i]);
        }
        printf("t: ");
        for (int i = 0; i <= N; i++) {
            printf("(%d %d) ", t[i][0], t[i][1]);
        }
        printf("sz: ");
        for (int i = 0; i <= N; i++) {
            printf("%d ", sz[i]);
        }
        printf("val: ");
        for (int i = 0; i <= N; i++) {
            printf("%d ", val[i]);
        }
        printf("d: ");
        for (int i = 0; i <= N; i++) {
            printf("%d ", d[i]);
        }
        printf("min: ");
        for (int i = 0; i <= N; i++) {
            printf("%d ", minVal[i]);
        }
        printf("root: %d", root);

        printf("\n");
    }

    int root;
    int N;  // number of elements, 0 (NULL) excluded
    vector<int> f;
    vector<array<int, 2>> t;
    vector<int> sz;
    vector<int> tag;
    vector<int> val;
    vector<int> d;
    vector<int> minVal;

private:
    void alloc(int cap) {
        f.resize(cap);
        t.resize(cap);
        sz.resize(cap);
        tag.resize(cap);
        val.resize(cap);
        d.resize(cap);
        minVal.resize(cap);
    }

    void initNode(int p, int fa, int v) {
        f[p] = fa;
        val[p] = minVal[p] = v;
        t[p][0] = t[p][1] = 0;
    }
};

char out[3*1024*1024+10];

bool isValid(char ch) {
  return 32 <= ch && ch <= 126;
}

int main() {
  SplayTree st(2, A, MAXN);
  int m;
  scanf("%d", &m);
  char cmd[10];
  int idx = 3;
  int cursor = 2;
  int n;
  int sz = 0;
  while (m--) {
    scanf("%s", cmd);
    if (cmd[0] == 'I') {
      int x = st.find_by_order(cursor-1);
      int y = st.find_by_order(cursor);
      st.splay(x, 0);
      st.splay(y, x);
      scanf("%d", &n);
      for (int i = 0; i < n;) {
        char c;
        if (isValid(c = getchar())) {
          A[idx+i] = int(c);
          i++;
        }
      }
      x = st.build(idx, idx+n-1, 0, A);
      st.ins(x);
      idx += n;
      sz += n;
    } else if (cmd[0] == 'M') {
      scanf("%d", &n);
      cursor = 2+n;
    } else if (cmd[0] == 'D') {
      scanf("%d", &n);
      int x = st.find_by_order(cursor-1);
      st.splay(x, 0);
      int y = st.find_by_order(cursor+n);
      st.splay(y, x);
      st.del();
      sz -= n;
    } else if (cmd[0] == 'N') {
      cursor++;
    } else if (cmd[0] == 'P') {
      cursor--;
    } else if (cmd[0] == 'G') {
      scanf("%d", &n);
      int x = st.find_by_order(cursor-1);
      st.splay(x, 0);
      int y = st.find_by_order(cursor+n);
      st.splay(y, x);
      int len = 0;
      st.collect(out, len);
      out[len] = '\0';
      printf("%s\n", out);
    } else {
      return 0;
    }
  }
  return 0;
}
