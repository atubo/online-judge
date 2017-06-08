// http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=3765
// Lights

#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

int gcd3(int a, int b, int c) {
    return gcd(gcd(a, b), c);
}

// index starts from 1 (0 is for NULL)
class SplayTree {
public:
    static const int MAXINT = 0x3f3f3f3f;

#if 0
    SplayTree(int size, int *a, bool *b, int cap = 0) {
        // 1-indexed
        N = size;
        if (cap == 0) cap = N + 1;
        assert(cap >= N + 1);

        f.resize(cap);
        t.resize(cap);
        sz.resize(cap);
        val.resize(cap);
        status.resize(cap);
        g.resize(cap);

        root = build(1, N, 0, a, b);
    }
#endif
    SplayTree(int cap) {
        f.resize(cap);
        t.resize(cap);
        sz.resize(cap);
        val.resize(cap);
        status.resize(cap);
        g.resize(cap);
    }

    void init(int size, int *a, bool *b) {
        N = size;
        root = build(1, N, 0, a, b);
    }

    // build range [i, j]
    int build(int p, int q, int fa, int *a, bool *b) {
        if (p > q) return 0;
        assert(q - p >= 0);

        int mid = (p + q) / 2;
        initNode(mid, fa, a[mid], b[mid]);

        t[mid][0] = build(p, mid-1, mid, a, b);
        t[mid][1] = build(mid+1, q, mid, a, b);

        pushUp(mid);

        return mid;
    }

    int buildSingleNode(int p, int fa, int v, bool s) {
        initNode(p, fa, v, s);
        pushUp(p);
        return p;
    }

    void pushUp(int x) {
        assert(x);

        sz[x] = sz[t[x][0]] + sz[t[x][1]] + 1;

        for (int i = 0; i < 2; i++) {
            g[x][i] = gcd3(g[t[x][0]][i], status[x] == i ? val[x] : 0, g[t[x][1]][i]);
        }
    }

    void pushDown(int x) {
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
        return x;
    }

    void ins(int x) {
        int y = t[root][1];
        t[y][0] = x;
        f[x] = y;
        pushUp(y);
        pushUp(root);
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
        printf("root: %d", root);
               
        printf("\n");
    }

    int root;
    int N;  // number of elements, 0 (NULL) excluded
    vector<int> f;
    vector<array<int, 2>> t;
    vector<int> sz;
    vector<int> val;
    vector<bool> status;
    vector<array<int, 2>> g;

private:
    void initNode(int p, int fa, int v, bool s) {
        f[p] = fa;
        val[p] = v;
        status[p] = s;
        g[p][status[p]] = v;
        
        t[p][0] = t[p][1] = 0;
    }
};

const int MAXN = 200010;
int A[MAXN];
bool B[MAXN];
int N, Q;

void query(SplayTree &st, int x, int y, int z) {
    x = st.find_by_order(x);
    y = st.find_by_order(y+2);
    st.splay(x, 0);
    st.splay(y, x);
    int ret = st.g[st.t[y][0]][z];
    printf("%d\n", ret ? ret : -1);
}

void insert(SplayTree &st, int p, int v, int s) {
    int x = st.find_by_order(p+1);
    int y = st.find_by_order(p+2);
    st.splay(x, 0);
    st.splay(y, x);
    int z = st.buildSingleNode(st.N+1, 0, v, s);
    st.ins(z);
    st.N++;
}

void del(SplayTree &st, int x) {
    int y = st.find_by_order(x);
    int z = st.find_by_order(x+2);
    st.splay(y, 0);
    st.splay(z, y);
    st.del();
}

void turn(SplayTree &st, int x) {
    x = st.find_by_order(x+1);
    st.splay(x, 0);
    st.status[x] = !st.status[x];
    st.pushUp(x);
}

void modify(SplayTree &st, int x, int y) {
    x = st.find_by_order(x+1);
    st.splay(x, 0);
    st.val[x] = y;
    st.pushUp(x);
}

int main() {
    SplayTree st(300010);
    while (scanf("%d%d", &N, &Q) == 2) {
        for (int i = 2; i < N+2; i++) {
            scanf("%d%d", &A[i], &B[i]);
        }
        //SplayTree st(N+2, A, B, N+Q+2);
        st.init(N+2, A, B);

        char cmd[5];
        int x, y, z;
        for (int i = 0; i < Q; i++) {
            scanf("%s", cmd);
            switch (cmd[0]) {
                case 'Q':
                    scanf("%d%d%d", &x, &y, &z);
                    query(st, x, y, z);
                    break;
                case 'I':
                    scanf("%d%d%d", &x, &y, &z);
                    insert(st, x, y, z);
                    break;
                case 'D':
                    scanf("%d", &x);
                    del(st, x);
                    break;
                case 'R':
                    scanf("%d", &x);
                    turn(st, x);
                    break;
                case 'M':
                    scanf("%d%d", &x, &y);
                    modify(st, x, y);
                    break;
                default:
                    assert(0);
                    break;
            }
        }
    }
    return 0;
}
