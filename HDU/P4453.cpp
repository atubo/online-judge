// http://acm.hdu.edu.cn/showproblem.php?pid=4453
// Looploop

#include <bits/stdc++.h>
using namespace std;

// index starts from 1 (0 is for NULL)
class SplayTree {
public:
    static const int MAXINT = 0x3f3f3f3f;

    static int min3(int a, int b, int c) {
        return min(min(a, b), c);
    }

    SplayTree(int size, int *a, int cap = 0) {
        // 1-indexed
        N = size;
        if (cap == 0) cap = N + 1;
        assert(cap >= N + 1);

        f.resize(cap);
        t.resize(cap);
        sz.resize(cap);
        tag.resize(cap);
        val.resize(cap);
        d.resize(cap);
        minVal.resize(cap);

        minVal[0] = MAXINT;

        root = build(1, N, 0, a);
    }

    // build range [i, j]
    int build(int p, int q, int fa, int *a) {
        if (p > q) return 0;
        assert(q - p >= 0);

        int mid = (p + q) / 2;
        f[mid] = fa;
        val[mid] = minVal[mid] = (a ? a[mid] : 0);

        t[mid][0] = build(p, mid-1, mid, a);
        t[mid][1] = build(mid+1, q, mid, a);

        pushUp(mid);

        return mid;
    }

    int buildSingleNode(int p, int fa, int v) {
        f[p] = fa;
        val[p] = minVal[p] = v;
        t[p][0] = t[p][1] = 0;
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
};

const int MAXN = 100010;
int A[MAXN];
int N, M, K1, K2;
int currOrder;
int currIndex;
int total;

void query(SplayTree &st) {
    int x = st.find_by_order(currOrder);
    st.splay(x, 0);
    printf("%d\n", st.val[x]);
}

void insert(SplayTree &st, int v) {
    assert(1 < currOrder && currOrder < total);
    int x = st.find_by_order(currOrder);
    int y = st.find_by_order(currOrder+1);
    st.splay(x, 0);
    st.splay(y, x);
    currIndex++;
    st.buildSingleNode(currIndex, 0, v);
    st.ins(currIndex);
    total++;
    st.N++;
}

void del(SplayTree &st) {
    assert(1 < currOrder && currOrder < total);
    int x = st.find_by_order(currOrder-1);
    int y = st.find_by_order(currOrder+1);
    st.splay(x, 0);
    st.splay(y, x);
    st.del();
    total--;
    if (currOrder == total) currOrder = 2;
}

void move(SplayTree &st, int d) {
    assert(1 < currOrder && currOrder < total);
    if (d == 1) currOrder--;
    else currOrder++;
    if (currOrder == 1) currOrder = total - 1;
    if (currOrder == total) currOrder = 2;
}

void rotateToFront(SplayTree &st, int k) {
    assert(currOrder + k - 1 >= total);
    int x = st.find_by_order(currOrder-1);
    int y = st.find_by_order(total);
    st.splay(x, 0);
    st.splay(y, x);
    int z = st.del();

    x = st.find_by_order(1);
    y = st.find_by_order(2);
    st.splay(x, 0);
    st.splay(y, x);
    st.ins(z);
    currOrder = 2;
}

void add(SplayTree &st, int d) {
    assert(1 < currOrder && currOrder < total);
    if (currOrder + K2 - 1 >= total) {
        rotateToFront(st, K2);
    }
    int x = st.find_by_order(currOrder-1);
    int y = st.find_by_order(currOrder+K2);
    st.splay(x, 0);
    st.splay(y, x);
    st.updateAdd(st.t[y][0], d);
}

void reverse(SplayTree &st) {
    assert(1 < currOrder && currOrder < total);
    if (currOrder + K1 - 1 >= total) {
        rotateToFront(st, K1);
    }
    int x = st.find_by_order(currOrder-1);
    int y = st.find_by_order(currOrder+K1);
    st.splay(x, 0);
    st.splay(y, x);
    st.updateRev(st.t[y][0]);
}

int main() {
    int testno = 1;
    while (scanf("%d%d%d%d", &N, &M, &K1, &K2) && (N + M + K1 + K2) > 0) {
        printf("Case #%d:\n", testno++);
        A[N+2] = 0;
        for (int i = 2; i < N+2; i++) {
            scanf("%d", &A[i]);
        }
        SplayTree st(N+2, A, N+M+2);

        currOrder = 2;
        currIndex = N+2;
        total = N+2;

        char cmd[10];
        int x;
        for (int i = 0; i < M; i++) {
            scanf("%s", cmd);
            if (cmd[0] == 'q') {
                query(st);
            } else if (cmd[0] == 'i') {
                scanf("%d", &x);
                insert(st, x);
            } else if (cmd[0] == 'd') {
                del(st);
            } else if (cmd[0] == 'm') {
                scanf("%d", &x);
                move(st, x);
            } else if (cmd[0] == 'a') {
                scanf("%d", &x);
                add(st, x);
            } else {
                reverse(st);
            }
        }
    }
    return 0;
}
