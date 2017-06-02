// http://acm.hdu.edu.cn/showproblem.php?pid=2475
// Box

#include <bits/stdc++.h>
using namespace std;

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

        root = build(1, N, 0);
    }

    // build range [i, j]
    int build(int p, int q, int fa) {
        if (p > q) return 0;
        assert(q - p >= 0);

        int mid = (p + q) / 2;
        f[mid] = fa;

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

    int leftmost(int x) {
        while (t[x][0]) x = t[x][0];
        return x;
    }

    int rightmost(int x) {
        while (t[x][1]) x = t[x][1];
        return x;
    }

    void cut(int x) {
        t[f[x]][son(x)] = 0;
        f[x] = 0;
    }

    void connect(int x, int y, int z) {
        // connect y as x's child, z = 0 -> left, 1 -> right
        assert(!f[y] && !t[x][z]);
        f[y] = x;
        t[x][z] = y;
    }

    bool contains(int x, int y) {
        // check if y is in the subtree of x
        while (y) {
            if (y == x) return true;
            y = f[y];
        }
        return false;
    }

    void move(int x, int y) {
        int u = 2*x - 1;
        splay(u, 0);
        splay(u+1, u);

        if (y > 0 && t[u+1][0] && contains(t[u+1][0], 2*y-1)) return;

        int v = t[u][0];
        int w = t[u+1][1];
        if (v && w) {
            cut(v);
            cut(w);
            v = rightmost(v);
            splay(v, 0);
            connect(v, w, 1);
        }

        if (y > 0) {
            v = 2*y - 1;
            splay(v, 0);
            w = leftmost(t[v][1]);
            splay(w, v);
            connect(w, u, 0);
        }
    }


    int root;
    int N;  // number of elements, 0 (NULL) excluded
    vector<int> f;
    vector<array<int, 2>> t;
    vector<int> sz;
    vector<int> tag;
};

int main() {
    int N;
    bool first = true;
    while (scanf("%d", &N) == 1) {
        if (first) first = false;
        else printf("\n");

        SplayTree st(2*N);
        for (int i = 1; i <= N; i++) {
            st.build(2*i-1, 2*i, 0);
        }
        int x, y;
        for (int i = 1; i <= N; i++) {
            scanf("%d", &x);
            if (x > 0) {
                st.move(i, x);
            }
        }
        int M;
        scanf("%d", &M);
        char cmd[10];
        for (int i = 0; i < M; i++) {
            scanf("%s", cmd);
            if (cmd[0] == 'Q') {
                scanf("%d", &x);
                st.splay(2*x-1, 0);
                y = st.leftmost(2*x-1);
                printf("%d\n", (y+1)/2);
            } else {
                scanf("%d%d", &x, &y);
                if (x != y) st.move(x, y);
            }
        }
    }
    return 0;
}
