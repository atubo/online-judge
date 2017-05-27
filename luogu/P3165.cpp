// https://www.luogu.org/problem/show?pid=3165
// [CQOI2014]排序机械臂

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

// index starts from 1 (0 is for NULL)
class SplayTree {
public:
    struct Node {
        Node() {
            sz = 0;
            init(0);
        }

        void init(int x) {
            sz = 0;
            val = x;
            tag = 0;
        }

        int sz;
        int val;
        int tag;
    };

    SplayTree(int sz) {
        // 1-indexed
        nodes.resize(sz + 1);
        f.resize(sz + 1);
        t.resize(sz + 1);
        for (int i = 0; i <= sz; i++) {
            t[i][0] = t[i][1] = 0;
        }
        root = build(1, sz, 0);
    }

    // build range [i, j]
    int build(int p, int q, int fa) {
        assert(q - p >= 0);

        int mid = (p + q) / 2;
        Node& x = nodes[mid];
        x.init(mid);
        f[mid] = fa;

        if (mid - p >= 1) t[mid][0] = build(p, mid-1, mid);
        if (q - mid >= 1) t[mid][1] = build(mid+1, q, mid);

        update(mid);

        return mid;
    }

    void reverse(int x) {
        nodes[x].tag ^= 1;
        swap(t[x][0], t[x][1]);
    }

    void pushDown(int x) {
        if (nodes[x].tag) {
            if (t[x][0]) reverse(t[x][0]);
            if (t[x][1]) reverse(t[x][1]);
            nodes[x].tag = 0;
        }
    }

    void update(int x) {
        assert(x);
    
        nodes[x].sz = 1;
        if (t[x][0]) nodes[x].sz += nodes[t[x][0]].sz;
        if (t[x][1]) nodes[x].sz += nodes[t[x][1]].sz;
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

    void splaySucc(int x) {
        pushDown(x);
        x = t[x][1];
        while (x) {
            pushDown(x);
            if (t[x][0]) x = t[x][0];
            else break;
        }
        splay(x, 0);
    }

    void del(int x) {
        // it must be left child of its parent and has no right child
        f[t[x][0]] = f[x];
        t[f[x]][0] = t[x][0];
        update(f[x]);
    }

    void print() {
        int sz = nodes.size() - 1;
        printf("f: ");
        for (int i = 1; i <= sz; i++) {
            printf("%d ", f[i]);
        }
        printf("t: ");
        for (int i = 1; i <= sz; i++) {
            printf("(%d %d) ", t[i][0], t[i][1]);
        }
        printf("sz: ");
        for (int i = 1; i <= sz; i++) {
            printf("%d ", nodes[i].sz);
        }
        printf("\n");
    }

    int root;
    vector<Node> nodes;
    vector<int> f;
    vector<array<int, 2>> t;
};

using Node = SplayTree::Node;


int main() {
    int N;
    scanf("%d", &N);
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &v[i]);
    }

    vector<PII> b(N);
    for (int i = 0; i < N; i++) {
        b[i] = make_pair(v[i], i+1);
    }
    sort(b.begin(), b.end());

    SplayTree st(N+1);
    for (int i = 0; i < N; i++) {
        int x = b[i].second;
        st.splay(x, 0);
        printf("%d", st.nodes[st.t[st.root][0]].sz + i + 1);
        if (i != N-1) printf(" ");

        st.reverse(st.t[st.root][0]);

        st.splaySucc(st.root);
        st.del(st.t[st.root][0]);
    }

    return 0;
}
