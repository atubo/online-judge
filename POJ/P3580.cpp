// http://poj.org/problem?id=3580
// SuperMemo

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <stack>
#include <vector>
using namespace std;

const int MAXINT = 0x3F3F3F3F;
const int MAXN   =  200010;

vector<int> A;
int t[MAXN][2];
int f[MAXN];
int sz[MAXN];
int tag[MAXN];
int val[MAXN];
int d[MAXN];
int minVal[MAXN];

int min3(int a, int b, int c) {
    return min(min(a, b), c);
}

// index starts from 1 (0 is for NULL)
class SplayTree {
public:

    SplayTree(int size, int cap = 0) {
        // 1-indexed
        N = size;
        if (cap == 0) cap = N + 1;
        assert(cap >= N + 1);

        minVal[0] = MAXINT;

        root = build(1, N, 0);
    }

    // build range [i, j]
    int build(int p, int q, int fa) {
        if (p > q) return 0;
        assert(q - p >= 0);

        int mid = (p + q) / 2;
        f[mid] = fa;
        val[mid] = minVal[mid] = A[mid];

        t[mid][0] = build(p, mid-1, mid);
        t[mid][1] = build(mid+1, q, mid);

        pushUp(mid);

        return mid;
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
    void del(int x) {
        t[f[x]][0] = 0;
        pushUp(f[x]);
        pushUp(f[f[x]]);
        f[x] = 0;
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
    //vector<int> f;
    //vector<int> sz;
    //vector<int> tag;
    //vector<int> val;
    //vector<int> d;
    //vector<int> minVal;
};

void reverse(SplayTree &st, int x, int y) {
    int pred = st.find_by_order(x);
    int succ = st.find_by_order(y+2);
    st.splay(pred, 0);
    st.splay(succ, pred);
    //st.reverse(t[succ][0]);
    st.updateRev(t[succ][0]);
    st.pushUp(succ);
    st.pushUp(pred);
}

int main() {
    int N;
    scanf("%d", &N);
    A.resize(N+3);
    A[1] = A[N+2] = MAXINT;
    for (int i = 2; i < N+2; i++) {
        scanf("%d", &A[i]);
    }

    SplayTree st(N+2, MAXN);
    int M;
    scanf("%d", &M);

    char cmd[10];
    int x, y, z;
    for (int i = 0; i < M; i++) {
        scanf("%s", cmd);
        if (cmd[0] == 'A') {
            scanf("%d%d%d", &x, &y, &z);
            int pred = st.find_by_order(x);
            int succ = st.find_by_order(y+2);
            st.splay(pred, 0);
            st.splay(succ, pred);
            st.updateAdd(t[succ][0], z);
            st.pushUp(succ);
            st.pushUp(pred);
        } else if (cmd[0] == 'I') {
            scanf("%d%d", &x, &y);
            int pred = st.find_by_order(x+1);
            int succ = st.find_by_order(x+2);
            st.splay(pred, 0);
            st.splay(succ, pred);
            int curr = st.N + 1;
            A.push_back(y);
            st.build(curr, curr, 0);
            st.ins(curr);
            st.N++;
            assert((int)A.size() == st.N + 1);
        } else if (cmd[0] == 'D') {
            scanf("%d", &x);
            int pred = st.find_by_order(x);
            int succ = st.find_by_order(x+2);
            st.splay(pred, 0);
            st.splay(succ, pred);
            st.del(t[succ][0]);
        } else if (cmd[0] == 'M') {
            scanf("%d%d", &x, &y);
            int pred = st.find_by_order(x);
            int succ = st.find_by_order(y+2);
            st.splay(pred, 0);
            st.splay(succ, pred);
            printf("%d\n", minVal[t[succ][0]]);
        } else if (cmd[3] == 'E') {
            scanf("%d%d", &x, &y);
            reverse(st, x, y);
        } else {
            scanf("%d%d%d", &x, &y, &z);
            z = z % (y - x + 1);
            if (z) {
                int pred = st.find_by_order(y-z+1);
                int succ = st.find_by_order(y+2);
                st.splay(pred, 0);
                st.splay(succ, pred);
                int curr = t[succ][0];
                st.del(curr);
                pred = st.find_by_order(x);
                succ = st.find_by_order(x+1);
                st.splay(pred, 0);
                st.splay(succ, pred);
                st.ins(curr);

            }
        }
    }
    return 0;
}
