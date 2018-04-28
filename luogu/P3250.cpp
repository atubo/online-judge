// https://www.luogu.org/problemnew/show/P3250
// [HNOI2016]网络

#include <bits/stdc++.h>
using namespace std;


class HeavyLightDecomposition {
private:
    // Note graph node is 0-indexed
    class Graph {
    public:
        struct Edge {
            int next, to;
        };

        vector<int> head;
        int eidx;
        int N;

        Edge *E;

        Graph(int N_):N(N_) {
            head.resize(N);
            eidx = 0;

            for (int i = 0; i < N; i++) {
                head[i] = -1;
            }

            // since this should be a tree
            E = new Edge[2*N-2]{};
        }

        ~Graph() {
            delete[] E;
        }

        // assume 0-indexed and no duplication
        void addEdge(int u, int v) {
            E[eidx].to = v;
            E[eidx].next = head[u];
            head[u] = eidx++;
        }
    };

    struct Link {
        int x, y;
        bool operator < (const Link &other) const {
            return x < other.x;
        }
    };

    // 1-indexed
    class SegmentTree {
        int N;
        priority_queue<int> *pq1, *pq2;

    public:
        SegmentTree(int N_): N(N_) {
            pq1 = new priority_queue<int>[4*N];
            pq2 = new priority_queue<int>[4*N];
        }

        ~SegmentTree() {
            delete[] pq1;
            delete[] pq2;
        }
        // add t to range [a, b]
        void add(int t, int a, int b) {
            add(1, t, 1, N, a, b);
        }

        // remove t from range [a, b]
        void remove(int t, int a, int b) {
            remove(1, t, 1, N, a, b);
        }

        // query range sum in [a, b]
        int64_t query(int a) {
            return query(1, a, 1, N);
        }

    private:
        // add t to range [a, b], current node range is [l, r]
        void add(int k, int t, int l, int r, int a, int b) {
            if (a > b) return;
            if (a <= l && r <= b) {
                pq1[k].push(t);
                return;
            }
            if (l == r) return;
            int mid = (l + r) / 2;
            if (a <= mid) add(2*k,   t, l, mid, a, b);
            if (mid < b)  add(2*k+1, t, mid+1, r, a, b);
        }

        void remove(int k, int t, int l, int r, int a, int b) {
            if (a > b) return;
            if (a <= l && r <= b) {
                pq2[k].push(t);
                return;
            }
            if (l == r) return;
            int mid = (l + r) / 2;
            if (a <= mid) remove(2*k, t, l, mid, a, b);
            if (mid < b) remove(2*k+1, t, mid+1, r, a, b);
        }

        // query position a, current node is [L, R]
        int query(int k, int a, int L, int R) {
            int ans = top(k);
            if (L == R) return ans;
            int mid = (L + R) / 2;
            if (a <= mid) return max(ans, query(2*k, a, L, mid));
            else return max(ans, query(2*k+1, a, mid+1, R));
        }

        int top(int k) {
            int ans = -1;
            while (!pq1[k].empty() && !pq2[k].empty()) {
                if (pq1[k].top() != pq2[k].top()) break;
                pq1[k].pop();
                pq2[k].pop();
            }
            if (!pq1[k].empty()) ans = pq1[k].top();
            return ans;
        }
    };

public:
    const int N;
    Graph g;
    SegmentTree st;
    vector<int> size;
    vector<int> dep;
    vector<int> rev;    // node to father-edge
    vector<int> heavy;
    vector<int> stIdx;    // node to segment tree index
    vector<int> fa;
    vector<int> top;
    vector<Link> links;
    int root;
    int Seg_size;

    HeavyLightDecomposition(int N_): N(N_), g(N_), st(N_) {
        size.resize(N);
        dep.resize(N);
        rev.resize(N);
        heavy.resize(N);
        stIdx.resize(N, -1);
        fa.resize(N);
        top.resize(N);
        links.resize(N+1);

        root = 0;
        Seg_size = 1;   // segment tree is 1-indexed
    }

    void addEdge(int u, int v) {
        g.addEdge(u, v);
        g.addEdge(v, u);
    }

    void decompose() {
        dfs1(root, root);
        top[root] = root;
        dfs2(root, root);
    }

    int query(int u) {
        return st.query(stIdx[u]);
    }

    void addRequest(int a, int b, int c) {
        int k = 0;
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]]) swap(a, b);
            links[++k].y = stIdx[a];
            links[k].x = stIdx[top[a]];
            a = g.E[rev[top[a]]].to;
        }
        if (dep[a] > dep[b]) swap(a, b);
        links[++k].x = stIdx[a];
        links[k].y = stIdx[b];
        sort(links.begin()+1, links.begin()+k+1);
        links[0].y = 0;
        links[++k].x = N+1;
        for (int i = 1; i <= k; i++) {
            if (links[i-1].y+1 <= links[i].x-1) {
                if (c > 0) {
                    st.add(c, links[i-1].y+1, links[i].x-1);
                } else {
                    st.remove(-c, links[i-1].y+1, links[i].x-1);
                }
            }
        }
    }

private:
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
        stIdx[u] = Seg_size++;

        if (heavy[u] != -1) {
            int t = heavy[u];
            int v = g.E[t].to;
            top[v] = top[u];
            dfs2(v, u);
        }

        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (v == f || eidx == heavy[u]) continue;
            top[v] = v;
            dfs2(v, u);
        }
    }

    int lca(int u, int v) {
        while (true) {
            int a = top[u], b = top[v];
            if (a == b) return dep[u] < dep[v] ? u : v;
            else if (dep[a] >= dep[b]) u = g.E[rev[a]].to;
            else v = g.E[rev[b]].to;
        }
    }

    int heavyChild(int u) const {
        int e = heavy[u];
        int ret = 0;
        if (e != -1) {
            ret = g.E[e].to;
        }
        return ret;
    }
};

const int MAXM = 200010;
int N, M;
struct Request {
    int a, b, v;
} req[MAXM];

int main() {
    scanf("%d%d", &N, &M);
    HeavyLightDecomposition hld(N);
    for (int i = 0; i < N-1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        hld.addEdge(u, v);
    }
    hld.decompose();
    for (int i = 0; i < M; i++) {
        int t;
        int a, b, c;
        scanf("%d", &t);
        switch (t) {
            case 0:
                scanf("%d%d%d", &a, &b, &c);
                a--; b--;
                hld.addRequest(a, b, c);
                req[i] = {a, b, c};
                break;
            case 1:
                scanf("%d", &a);
                a--;
                hld.addRequest(req[a].a, req[a].b, -req[a].v);
                break;
            case 2:
                scanf("%d", &a);
                a--;
                printf("%d\n", hld.query(a));
                break;
            default:
                assert(0);
                break;
        }
    }

    return 0;
}
