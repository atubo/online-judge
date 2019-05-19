// https://www.luogu.org/problemnew/show/P4234
// 最小差值生成树

#include <bits/stdc++.h>
using namespace std;

class LinkCutTree {
    // tree nodes are 1-indexed

public:
    LinkCutTree(int N): N_(N) {
        alloc();
    }

    ~LinkCutTree() {
        dealloc();
    }

    void access(int x) {
        for (int t = 0; x; t=x, x=fa_[x]) {
            splay(x);
            c_[x][1] = t;
            pushUp(x);
        }
    }

    void makeRoot(int x) {
        access(x);
        splay(x);
        rev_[x] ^= 1;
    }

    void link(int x, int y) {
        makeRoot(x);
        makeRoot(y);
        fa_[x] = y;
        splay(x);
        pushUp(y);
    }

    // split out the path from x to y
    void split(int x, int y) {
        makeRoot(x);
        access(y);
        splay(y);
    }

    void cut(int x, int y) {
        split(x, y);
        c_[y][0] = fa_[x] = 0;
        pushUp(y);
    }

    int find(int x) {
        access(x);
        splay(x);
        int y = x;
        while (c_[y][0]) y = c_[y][0];
        return y;
    }

    int query(int x, int y) {
        makeRoot(x);
        access(y);
        splay(y);
        return mx_[y];
    }

public:
    int *val;
private:
    const int N_;
    int *fa_, *mx_;
    int **c_;
    int *q_;
    bool *rev_;

    void alloc() {
        fa_ = new int[N_+1]{};
        val = new int[N_+1]{};
        mx_ = new int[N_+1]{};
        c_ = new int*[N_+1]{};
        for (int i = 0; i <= N_; i++) {
            c_[i] = new int[2]{};
        }
        q_ = new int[N_+1]{};
        rev_ = new bool[N_+1]{};
    }

    void dealloc() {
        delete[] fa_;
        delete[] val;
        delete[] mx_;
        for (int i = 0; i <= N_; i++) {
            delete[] c_[i];
        }
        delete[] c_;
        delete[] q_;
        delete[] rev_;
    }

    bool isSplayRoot(int x) {
        return c_[fa_[x]][1] != x && c_[fa_[x]][0] != x;
    }

    void pushDown(int x) {
        int l = c_[x][0], r = c_[x][1];
        if (rev_[x]) {
            rev_[x] ^= 1; rev_[l] ^= 1; rev_[r] ^= 1;
            swap(c_[x][1], c_[x][0]);
        }
    }

    void pushUp(int x) {
        int l = c_[x][0], r = c_[x][1];
        mx_[x] = val[x];
        mx_[x] = (mx_[x] < mx_[l] ? mx_[l]: mx_[x]);
        mx_[x] = (mx_[x] < mx_[r] ? mx_[r]: mx_[x]);
    }

    void rotate(int x) {
        int y = fa_[x], z = fa_[y], l, r;
        l = (c_[y][1] == x); r = l^1;
        if (!isSplayRoot(y)) c_[z][c_[z][1]==y] = x;
        fa_[c_[x][r]] = y; fa_[y] = x; fa_[x] = z;
        c_[y][l] = c_[x][r]; c_[x][r] = y;
        pushUp(y); pushUp(x);
    }

    void splay(int x) {
        int top = 0;
        q_[++top] = x;
        for (int i = x; !isSplayRoot(i); i = fa_[i]) {
            q_[++top] = fa_[i];
        }
        while (top) pushDown(q_[top--]);
        while (!isSplayRoot(x)) {
            int y = fa_[x], z = fa_[y];
            if (!isSplayRoot(y)) {
                if ((c_[y][0] == x) ^ (c_[z][0] == y)) rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
    }
};

class UnionFind {
private:
    const int N;
    vector<int> rank;
    vector<int> parent;

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parent[k] = k;
        rank[k] = 0;
    }

    int link(int u, int v) {
        if (u == v) return u;
        if (rank[u] > rank[v]) {
            parent[v] = u;
            return u;
        } else {
            parent[u] = v;
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
            return v;
        }
    }

public:
    UnionFind(int n): N(n) {
        rank.resize(N);
        parent.resize(N);

        reset();
    }

    void reset() {
        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    int find(int k) {
        if (parent[k] == k) return k;
        int root = find(parent[k]);
        return parent[k] = root;
    }

    int join(int u, int v) {
        return link(find(u), find(v));
    }
};

const int MAXM = 200010;
int N, M;

struct Edge {
    int u, v, w;
    bool operator < (const Edge &other) const {
        if (w != other.w) return w < other.w;
        if (u != other.u) return u < other.u;
        return v < other.v;
    }
} edges[MAXM];

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        if (u > v) swap(u, v);
        edges[i] = {u, v, w};
    }
    sort(edges+1, edges+M+1);

    LinkCutTree lct(N+M);
    UnionFind uf(N+1);

    for (int i = 1; i <= M; i++) {
        lct.val[i+N] = i;
    }

    set<int> eids;
    int np = N;
    int ans = INT_MAX;
    for (int i = M; i > 0; i--) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (u == v) continue;
        if (uf.find(u) != uf.find(v)) {
            int x = i + N;
            lct.link(u, x);
            lct.link(x, v);

            uf.join(u, v);
            np--;
            eids.insert(i);
        } else {
            int z = lct.query(u, v);
            int x = edges[z].u;
            int y = edges[z].v;
            lct.cut(x, N+z);
            lct.cut(y, N+z);
            eids.erase(z);

            z = i + N;
            lct.link(u, z);
            lct.link(v, z);
            eids.insert(i);
        }

        if (np == 1) {
            int b = *eids.begin();
            int e = *eids.rbegin();
            ans = min(ans, edges[e].w - edges[b].w);
        }
    }

    printf("%d\n", ans);

    return 0;
}
