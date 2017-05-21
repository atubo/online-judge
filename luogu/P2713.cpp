// https://www.luogu.org/problem/show?pid=2713
// 铲雪

#include <bits/stdc++.h>
using namespace std;


// Note graph node is 0-indexed
class Graph {
    static const int MAXM = 200000;
public:
    struct Edge {
        int next, to, weight;
    } E[MAXM];

    vector<int> head;
    int eidx;
    int N;

    Graph(int N_):N(N_) {
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v, int w) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].weight = w;
        head[u] = eidx++;
    }
};


template<typename V, typename D=V>
class SegmentTreeTD {
    struct Node {
        Node(): value(0), update(0),count(0) {}
        V value;
        D update;
        int count;
    };

public:
    SegmentTreeTD(const vector<V>& A, V zero_, D zeroUpdate_) :
        N(A.size()), zero(zero_), zeroUpdate(zeroUpdate_) {
        int nlog = 0;
        int n = N;
        while (n > 0) {
            n = (n >> 1);
            nlog++;
        }
        int msize = 2 * (1 << (nlog+1)) + 1;
        M = new Node[msize];
        for (int i = 1; i < msize; i++) M[i].update = zeroUpdate;
        initialize(1, 0, N-1, A);
    }

    ~SegmentTreeTD() {
        delete[] M;
    }

    void initialize(int node, int b, int e, const vector<V>& A) {
        if (b == e) {
            M[node].value = A[b];
            M[node].count = 1;
        }
        else {
            initialize(2*node, b, (b+e)/2, A);
            initialize(2*node+1, (b+e)/2+1, e, A);
            M[node].value = eval(M[2*node]) + eval(M[2*node+1]);
            M[node].count = M[2*node].count + M[2*node+1].count;
        }
    }

    // i, j inclusive
    V query(int i, int j) const {
        return query(1, 0, N-1, i, j);
    }

    void update(int i, int j, D d) {
        update(1, 0, N-1, i, j, d);
    }

private:
    const int N;
    const V zero;   // zero element for combine
    const D zeroUpdate; // zero for update

    Node* M;

    V eval(const Node& node) const {
        return node.value + node.update * node.count;
    }

    V query(int node, int b, int e, int i, int j) const {
        assert(b <= e);
        if (i > e || j < b) {
            return zero;
        }

        if (M[node].update != zeroUpdate) {
            M[node].value = eval(M[node]);
            if (b != e) {
                M[2*node].update = M[node].update + M[2*node].update;
                M[2*node+1].update = M[node].update + M[2*node+1].update;
            }
            M[node].update = zeroUpdate;
        }

        if (b >= i && e <= j) {
            return M[node].value;
        }

        V p1 = query(2*node, b, (b+e)/2, i, j);
        V p2 = query(2*node+1, (b+e)/2+1, e, i, j);

        return p1 + p2;
    }

    void update(int node, int b, int e, int i, int j, D d) {
        if (i > e || j < b) {
            return;
        }
        if (b >= i && e <= j) {
            M[node].update = d + M[node].update;
            return;
        }
        if (M[node].update != zeroUpdate) {
            M[2*node].update = M[node].update + M[2*node].update;
            M[2*node+1].update = M[node].update + M[2*node+1].update;
        }

        update(2*node, b, (b+e)/2, i, j, d);
        update(2*node+1, (b+e)/2+1, e, i, j, d);
        M[node].value = eval(M[2*node]) + eval(M[2*node+1]);
        M[node].update = zeroUpdate;
    }
};


class HeavyLightDecomposition {
public:
    const Graph &g;
    const int N;
    vector<int> size;
    vector<int> dep;
    vector<int> rev;    // node to father-edge
    vector<int> heavy;
    vector<int> num;    // edge to segment tree index
    vector<int> fa;
    vector<int> top;
    vector<int> weight;
    int root;
    int Seg_size;
    SegmentTreeTD<int> *st;

    HeavyLightDecomposition(const Graph &g_): g(g_), N(g_.N) {
        size.resize(N);
        dep.resize(N);
        rev.resize(N);
        heavy.resize(N);
        num.resize(2*N, -1);
        fa.resize(N);
        top.resize(N);
        weight.resize(N-1);

        root = 0;
        Seg_size = 0;

        prepare();
    }

    ~HeavyLightDecomposition() {
        delete st;
        st = NULL;
    }

    void dfs1(int u, int f) {
        int mx = -1, e = -1;
        size[u] = 1;

        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (v == f) continue;
            dep[v] = dep[u] + 1;
            rev[v] = eidx ^ 1;
            dfs1(v, u);
            size[u] += size[v];
            if (size[v] > mx) {
                mx = size[v];
                e = eidx;
            }
        }
        heavy[u] = e;
        if (e != -1) fa[g.E[e].to] = u;
    }

    void dfs2(int u, int f) {
        if (heavy[u] != -1) {
            int t = heavy[u];
            weight[Seg_size] = g.E[t].weight;
            num[t^1] = Seg_size++;
            int v = g.E[t].to;
            top[v] = top[u];
            dfs2(v, u);
        }

        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (v == f || eidx == heavy[u]) continue;
            weight[Seg_size] = g.E[eidx].weight;
            num[eidx^1] = Seg_size++;
            top[v] = v;
            dfs2(v, u);
        }
    }

    void prepare() {
        // set up segment tree
        vector<int> A(N-1, 0);
        st = new SegmentTreeTD<int>(A, 0, 0);

        dfs1(root, root);
        top[root] = root;
        dfs2(root, root);
    }

    void updateChain(int u, int anc, int val) {
        while (u != anc) {
            int fe = rev[u];
            if (top[u] != u) {
                int p = top[u];
                if (dep[p] < dep[anc]) p = anc;
                int l = num[heavy[p]^1];
                int r = num[fe];
                st->update(l, r, val);
                u = p;
            } else {
                int r = num[fe];
                st->update(r, r, val);
                u = g.E[fe].to;
            }
        }
    }


    void update(int u, int v, int d) {
        int p = lca(u, v);;
        updateChain(u, p, d);
        updateChain(v, p, d);

        // if it's node update, update p related information here
    }

    int lca(int u, int v) {
        while (true) {
            int a = top[u], b = top[v];
            if (a == b) return dep[u] < dep[v] ? u : v;
            else if (dep[a] >= dep[b]) u = g.E[rev[a]].to;
            else v = g.E[rev[b]].to;
        }
    }
};

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    Graph g(N);
    for (int i = 0; i < N-1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        g.addEdge(u, v, w);
        g.addEdge(v, u, w);
    }

    HeavyLightDecomposition hld(g);

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        hld.update(u, v, 1);
    }

    int total = 0;
    int maxcut = 0;
    for (int i = 0; i < N-1; i++) {
        int w = hld.weight[i];
        int f = hld.st->query(i, i);
        total += w * f;
        maxcut = max(maxcut, w * f);
    }
    printf("%d\n", total - maxcut);
    return 0;
}
