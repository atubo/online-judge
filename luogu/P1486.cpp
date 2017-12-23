// https://www.luogu.org/problemnew/show/P1486
// 郁闷的出纳员

#include <bits/stdc++.h>
using namespace std;

// index starts from 1 (0 is for NULL)
class SplayTree {
public:
    static const int MAXINT = 0x3f3f3f3f;

    static int min3(int a, int b, int c) {
        return min(min(a, b), c);
    }

    SplayTree(int size, int *a = NULL, int *x = NULL, int cap = 0) {
        // 1-indexed
        if (cap == 0) cap = size + 1;
        assert(cap >= size + 1);
        alloc(cap);
        init(size, a, x);
    }

    void init(int size, int *a, int *x) {
        N = size;

        tot[0] = 0;
        root = build(1, N, 0, a, x);
    }

    // build range [i, j]
    int build(int p, int q, int fa, int *a, int *x) {
        if (p > q) return 0;
        assert(q - p >= 0);

        int mid = (p + q) / 2;
        initNode(mid, fa, (a ? a[mid] : 0), x[mid]);

        t[mid][0] = build(p, mid-1, mid, a, x);
        t[mid][1] = build(mid+1, q, mid, a, x);

        pushUp(mid);

        return mid;
    }

    int buildSingleNode(int p, int fa, int v, int x) {
        initNode(p, fa, v, x);
        pushUp(p);
        return p;
    }

    void pushUp(int x) {
        assert(x);

        sz[x] = sz[t[x][0]] + sz[t[x][1]] + 1;
        tot[x] = tot[t[x][0]] + tot[t[x][1]] + val[x];
    }

    void updateRev(int x) {
        if (!x) return;

        swap(t[x][0], t[x][1]);
        tag[x] ^= 1;
    }

    void pushDown(int x) {
        if (tag[x]) {
            updateRev(t[x][0]);
            updateRev(t[x][1]);
            tag[x] = 0;
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
        printf("tot: ");
        for (int i = 0; i <= N; i++) {
            printf("%d ", tot[i]);
        }
        printf("sal: ");
        for (int i = 0; i <= N; i++) {
            printf("%d ", sal[i]);
        }
        printf("root: %d", root);
               
        printf("\n");
    }

    // find node or its neighbor
    int find(int x) {
        int p = root;
        int last;
        while (p) {
            if (sal[p] == x) return p;
            last = p;
            if (sal[p] > x) p = t[p][0];
            else            p = t[p][1];
        }
        return last;
    }

    int root;
    int N;  // number of elements, 0 (NULL) excluded
    vector<int> f;
    vector<array<int, 2>> t;
    vector<int> sz;
    vector<int> tag;
    vector<int> val;
    vector<int> tot;
    vector<int> sal;

private:
    void alloc(int cap) {
        f.resize(cap);
        t.resize(cap);
        sz.resize(cap);
        tag.resize(cap);
        val.resize(cap);
        tot.resize(cap);
        sal.resize(cap);
    }

    void initNode(int p, int fa, int v, int x) {
        f[p] = fa;
        val[p] = tot[p] = v;
        t[p][0] = t[p][1] = 0;
        sal[p] = x;
    }
};

int N, M;
const int MAXCAP = 100010;
int sz = 3;
int quit = 0;

void insert(SplayTree &st, int s) {
    int x = st.find(s);
    st.splay(x, 0);
    if (st.sal[x] == s) {
        st.val[x]++;
        st.pushUp(x);
        return;
    }
    int order = st.order_of_root();
    if (st.sal[x] > s) {
        int y = st.find_by_order(order-1);
        st.splay(y, 0);
        st.splay(x, y);
        int z = st.buildSingleNode(sz++, x, 1, s);
        st.ins(z);
        st.splay(z, 0);
    } else {
        int y = st.find_by_order(order+1);
        st.splay(x, 0);
        st.splay(y, x);
        int z = st.buildSingleNode(sz++, y, 1, s);
        st.ins(z);
        st.splay(z, 0);
    }
}

void remove(SplayTree &st, int s) {
    int x = st.find(s);
    if (x == 1) return;
    st.splay(x, 0);
    int order = st.order_of_root();
    if (st.sal[x] >= s) {
        int y = st.find_by_order(order-1);
        if (y != 1) {
            st.splay(1, 0);
            st.splay(x, 1);
            st.splay(y, x);
            quit += st.tot[y];
            st.del();
            st.splay(x, 0);
        }
    } else {
        int y = st.find_by_order(order+1);
        st.splay(1, 0);
        st.splay(y, 1);
        st.splay(x, y);
        quit += st.tot[x];
        st.del();
        st.splay(y, 0);
    }
}

int findkth(SplayTree &st, int k) {
    if (k >= st.tot[st.root]) return INT_MIN;
    k = st.tot[st.root] - k - 1;
    int p = st.root;
    while (true) {
        int tot1 = st.tot[st.t[p][0]];
        int tot  = st.tot[p];
        int tot2 = st.tot[st.t[p][1]];
        if (tot1 <= k && k < tot-tot2) {
            return st.sal[p];
        }
        if (k < tot1) {
            p = st.t[p][0];
        } else {
            p = st.t[p][1];
            k -= tot - tot2;
        }
    }
    assert(0);
    return INT_MIN;
}

int main() {
    scanf("%d%d", &N, &M);
    int a[3] = {0, 0, 0};
    int x[3] = {0, INT_MIN, INT_MAX};
    SplayTree st(2, a, x, MAXCAP);
    int adjust = 0;

    for (int i = 0; i < N; i++) {
        char cmd[10];
        int k;
        scanf("%s%d", cmd, &k);
        switch (cmd[0]) {
            case 'I':
                if (k >= M) {
                    insert(st, k-adjust);
                }
                break;
            case 'A':
                adjust += k;
                break;
            case 'S':
                adjust -= k;
                remove(st, M-adjust);
                break;
            case 'F':
                {
                    int ret = findkth(st, k-1);
                    ret = (ret == INT_MIN ? -1 : ret + adjust);
                    printf("%d\n", ret);
                    break;
                }
            default:
                assert(0);
                break;
        }
    }
    printf("%d\n", quit);
    return 0;
}
