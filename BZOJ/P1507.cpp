// http://www.lydsy.com/JudgeOnline/problem.php?id=1507
// [NOI2003]Editor

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2100000;
char A[MAXN];

// index starts from 1 (0 is for NULL)
class SplayTree {
public:

    SplayTree(int size, int cap = 0) {
        // 1-indexed
        N = size;
        if (cap == 0) cap = N + 1;
        assert(cap >= N + 1);

        f.resize(cap);
        t.resize(cap, vector<int>(2));
        sz.resize(cap);
        tag.resize(cap);
        root = build(1, N, 0);
    }

    // build range [i, j]
    int build(int p, int q, int fa) {
        assert(q - p >= 0);

        int mid = (p + q) / 2;
        f[mid] = fa;

        if (mid - p >= 1) t[mid][0] = build(p, mid-1, mid);
        if (q - mid >= 1) t[mid][1] = build(mid+1, q, mid);

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

    void inorder(int x, string &s) {
        if (t[x][0]) inorder(t[x][0], s);
        s.push_back(A[x]);
        if (t[x][1]) inorder(t[x][1], s);
    }

    int root;
    int N;  // number of elements, 0 (NULL) excluded
    vector<int> f;
    vector<vector<int> > t;
    vector<int> sz;
    vector<int> tag;
};

int main() {
    int t;
    scanf("%d", &t);
    char cmd[10];
    int n;
    SplayTree st(2, MAXN);
    while (t--) {
        scanf("%s", cmd);
        if (cmd[0] == 'I') {
            scanf("%d", &n);
            int cnt = 0;
            while (cnt < n) {
                string s;
                getline(cin, s);
                strncpy(A + 1 + st.N + cnt, s.c_str(), s.length());
                cnt += s.length();
            }
            int y = st.find_by_order(st.order_of_root() + 1);
            st.splay(y, st.root);
            int x = st.build(st.N + 1, st.N + n, 0);
            st.N += n;
            st.ins(x);
        } else if (cmd[0] == 'M') {
            scanf("%d", &n);
            int x = st.find_by_order(n+1);
            int y = st.find_by_order(n+2);
            st.splay(x, 0);
            st.splay(y, x);
        } else if (cmd[0] == 'D') {
            scanf("%d", &n);
            int y = st.find_by_order(st.order_of_root() + n + 1);
            st.splay(y, st.root);
            int x = st.t[y][0];
            st.del(x);
        } else if (cmd[0] == 'G') {
            scanf("%d", &n);
            int y = st.find_by_order(st.order_of_root() + n + 1);
            st.splay(y, st.root);
            int x = st.t[y][0];
            string s;
            st.inorder(x, s);
            printf("%s\n", s.c_str());
        } else if (cmd[0] == 'P') {
            int y = st.find_by_order(st.order_of_root() - 1);
            st.splay(y, 0);
        } else if (cmd[0] == 'N') {
            int y = st.find_by_order(st.order_of_root() + 1);
            st.splay(y, 0);
        } else {
            assert(0);
        }
    }
            
    return 0;
}
