// http://www.spoj.com/problems/GSS6/
// Can you answer these queries VI

#include <bits/stdc++.h>
using namespace std;

vector<int> A;
const int MAXN = 200010;
const int MININT = -1000000;

int max3(int a, int b, int c) {
    return max(max(a, b), c);
}

// index starts from 1 (0 is for NULL)
class SplayTree {
public:

    SplayTree(int size, int cap = 0) {
        // 1-indexed
        N = size;
        if (cap == 0) cap = N + 1;
        assert(cap >= N + 1);

        f.resize(cap);
        t.resize(cap);
        sz.resize(cap);
        tag.resize(cap);
        val.resize(cap);
        total.resize(cap);
        maxL.resize(cap);
        maxR.resize(cap);
        maxM.resize(cap);
        maxL[0] = maxR[0] = maxM[0] = MININT;

        root = build(1, N, 0);
    }

    // build range [i, j]
    int build(int p, int q, int fa) {
        if (p > q) return 0;
        assert(q - p >= 0);

        int mid = (p + q) / 2;
        f[mid] = fa;
        val[mid] = maxL[mid] = maxR[mid] = maxM[mid] = A[mid];

        t[mid][0] = build(p, mid-1, mid);
        t[mid][1] = build(mid+1, q, mid);

        update(mid);

        return mid;
    }

    void reverse(int x) {
        tag[x] ^= 1;
        swap(t[x][0], t[x][1]);
    }

    void pushDown(int x) {
        if (tag[x]) {
            if (t[x][0]) reverse(t[x][0]);
            if (t[x][1]) reverse(t[x][1]);
            tag[x] = 0;
        }
    }

    void update(int x) {
        assert(x);
    
        sz[x] = sz[t[x][0]] + sz[t[x][1]] + 1;
        total[x] = total[t[x][0]] + val[x] + total[t[x][1]];
        maxL[x] = max3(maxL[t[x][0]], total[t[x][0]] + val[x],
                       total[t[x][0]] + val[x] + maxL[t[x][1]]);
        maxR[x] = max3(maxR[t[x][1]], total[t[x][1]] + val[x],
                       total[t[x][1]] + val[x] + maxR[t[x][0]]);
        maxM[x] = max(max3(maxM[t[x][0]], val[x], maxM[t[x][1]]),
                      max3(maxR[t[x][0]] + val[x],
                           maxL[t[x][1]] + val[x],
                           maxR[t[x][0]] + val[x] + maxL[t[x][1]]));
    }

    bool son(int x) const {
        return t[f[x]][0] == x ? 0 : 1;
    }

    void rotate(int x) {
        int y = f[x], z = son(x);

        t[y][z] = t[x][1-z];
        if (t[x][1-z]) f[t[x][1-z]] = y;

        f[x] = f[y];
        if (f[x]) t[f[x]][son(y)] = x;

        f[y] = x; t[x][1-z] = y;
        update(y); update(x);
    }

    void propagate(int x, int y) {
        if (x == y) return;
        stack<int> d;
        do {
            d.push(x);
            x = f[x];
        } while (x != y);
        while (!d.empty()) {
            x = d.top();
            d.pop();
            pushDown(x);
        }
    }

    void splay(int x, int y) {
        propagate(x, y);
        while (f[x] != y) {
            if (f[f[x]] != y) {
                if (son(f[x]) == son(x)) rotate(f[x]);
                else rotate(x);
            }
            rotate(x);
        }
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

    // starting from 1
    int order_of_root() {
        return 1 + sz[t[root][0]];
    }

    // both deletion and insertion must happen on the left child of
    // root's right child
    void del(int x) {
        t[f[x]][0] = 0;
        update(f[x]);
        update(f[f[x]]);
        f[x] = 0;
    }

    void ins(int x) {
        int y = t[root][1];
        t[y][0] = x;
        f[x] = y;
        update(y);
        update(root);
    }

    void inorder(int x) {
        if (t[x][0]) inorder(t[x][0]);
        printf("%d ", val[x]);
        if (t[x][1]) inorder(t[x][1]);
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
        printf("tag: ");
        for (int i = 0; i <= N; i++) {
            printf("%d ", tag[i]);
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
    vector<int> total;
    vector<int> maxL;
    vector<int> maxR;
    vector<int> maxM;
};

int main() {
    int N;
    scanf("%d", &N);
    A.resize(N+3);
    A[1] = A[N+2] = MININT;
    for (int i = 2; i < N+2; i++) {
        scanf("%d", &A[i]);
    }

    SplayTree st(N+2, MAXN);

    int M;
    scanf("%d", &M);
    char cmd[5];
    int x, y;
    for (int i = 0; i < M; i++) {
        scanf("%s", cmd);
        if (cmd[0] == 'I') {
            scanf("%d%d", &x, &y);
            int pred = st.find_by_order(x);
            int succ = st.find_by_order(x+1);
            st.splay(pred, 0);
            st.splay(succ, pred);
            A.push_back(y);
            int curr = st.N + 1;
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
            st.del(st.t[succ][0]);
        } else if (cmd[0] == 'R') {
            scanf("%d%d", &x, &y);
            int curr = st.find_by_order(x+1);
            st.splay(curr, 0);
            st.val[curr] = y;
            st.update(curr);
        } else {
            assert(cmd[0] == 'Q');
            scanf("%d%d", &x, &y);
            int pred = st.find_by_order(x);
            int succ = st.find_by_order(y+2);
            st.splay(pred, 0);
            st.splay(succ, pred);
            int curr = st.t[succ][0];
            printf("%d\n", max3(st.maxL[curr], st.maxR[curr], st.maxM[curr]));
        }
    }
    return 0;
}
