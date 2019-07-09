// https://www.luogu.org/problemnew/show/P3242
// [HNOI2015]接水果

#include <bits/stdc++.h>
using namespace std;

class FenwickTree {
public:
    // 1-indexed
    FenwickTree(int size): n_(size) {
        tree_ = new int64_t[n_+1]{};
    }

    ~FenwickTree() {
        delete[] tree_;
    }

    void clear() {
        memset(tree_, 0, (n_+1) * sizeof(int64_t));
    }

    // add v to value at x
    void set(int x, int v) {
        while(x <= n_) {
            tree_[x] += v;
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int64_t get(int x) const {
        int64_t res = 0;
        while(x) {
            res += tree_[x];
            x -= (x & -x);
        }
        return res;
    }

    // get result for [x, y]
    int64_t get(int x, int y) const {
        return get(y) - (x > 1 ? get(x-1) : 0);
    }

    // index of first element with cumulative sum >= x
    int lowerBound(int64_t x) {
        int clz = __builtin_clz(n_);
        int idx = 0, mask = 1 << (31 - clz);     // first power of 2 <= n_
        while (mask) {
            int t = idx + mask;
            if (t <= n_ && x > tree_[t]) {
                idx = t;
                x -= tree_[t];
            }
            mask >>= 1;
        }
        return idx+1;
    }

    int upperBound(int64_t x) {
        int p = lowerBound(x);
        if (p <= n_ && get(p) == x) p = lowerBound(x+1);
        return p;
    }

private:
    int64_t* tree_;
    const int n_;
};

// Online algorithm, pre-computing O(N log N)
// Each query O(log N)

class BinaryLiftLCA {
    // Note graph node is 0-indexed
    class Graph {
    public:
        struct Edge {
            int next, to;
        };

        vector<int> head;
        int eidx;
        int N, M;

        Edge *E;

        Graph(int N_, int M_):N(N_), M(M_) {
            head.resize(N);
            eidx = 0;

            for (int i = 0; i < N; i++) {
                head[i] = -1;
            }

            E = new Edge[M]{};
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

    int N_, root_;
    int MAXB_;
    Graph g_;
public:
    int* depth;
    int** father;
    int* in_, *out_;
    int currId_ = 0;

public:
    BinaryLiftLCA(int N, int root)
        : N_(N), root_(root), MAXB_(log2(N)+1), g_(N, 2*(N-1)) {
            alloc();
    }

    ~BinaryLiftLCA() {
        dealloc();
    }

    void addEdge(int u, int v) {
        g_.addEdge(u, v);
        g_.addEdge(v, u);
    }

    void build() {
        dfs(root_, -1, 0);

        binaryLift();
    }

    int findLCA(int u, int v) const {
        if (depth[u] < depth[v]) swap(u, v);
        for (int b = MAXB_-1; b >= 0; b--) {
            if (father[u][b] == -1) continue;
            if (depth[father[u][b]] >= depth[v]) {
                u = father[u][b];
            }
        }

        if (u == v) return u;

        for (int b = MAXB_-1; b >= 0; b--) {
            if (father[u][b] == -1) continue;
            if (father[u][b] != father[v][b]) {
                u = father[u][b];
                v = father[v][b];
            }
        }
        return father[u][0];
    }

    int findFirst(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int t = depth[u] - depth[v] - 1;
        for (int i = 0; i < MAXB_; i++) {
            if (t>>i&1) u = father[u][i];
        }
        return u;
    }

private:
    void alloc() {
        depth = new int[N_]{};
        father = new int*[N_]{};
        for (int i = 0; i < N_; i++) {
            father[i] = new int[MAXB_]{};
            memset(father[i], -1, MAXB_*sizeof(int));
        }
        in_ = new int[N_]{};
        out_ = new int[N_]{};
    }

    void dealloc() {
        delete[] depth;
        for (int i = 0; i < N_; i++) {
            delete[] father[i];
        }
        delete[] father;
        delete[] in_;
        delete[] out_;
    }

    void dfs(int x, int f, int d) {
        in_[x] = currId_++;
        depth[x] = d;
        father[x][0] = f;
        for (int eidx = g_.head[x]; ~eidx; eidx = g_.E[eidx].next) {
            int u = g_.E[eidx].to;
            if (u != f) dfs(u, x, d+1);
        }
        out_[x] = currId_-1;
    }

    void binaryLift() {
        for (int j = 1; j < MAXB_; j++) {
            for (int i = 0; i < N_; i++) {
                if (father[i][j-1] != -1) {
                    father[i][j] = father[father[i][j-1]][j-1];
                }
            }
        }
    }
};

struct Plate {
    int x1, x2, y1, y2, v;
};

struct Query {
    int x, y, k, id;
};

struct Item {
    int pos, l, r, type;
    bool operator < (const Item &other) const {
        if (pos != other.pos) return pos < other.pos;
        if (type != other.type) return type < other.type;
        if (l != other.l) return l < other.l;
        return r < other.r;
    }
};

const int MAXN = 40010;
const int MAXC = 1000000000;
int N, P, Q;
int ans[MAXN];

void divideConquer(int l, int r, const vector<Plate> &plates,
                   vector<Query> &queries,
                   FenwickTree &ft) {
    if (queries.empty()) return;
    if (l == r) {
        for (const auto &q: queries) {
            ans[q.id] = l;
        }
        return;
    }
    int mid = (l + r) / 2;
    vector<Plate> p1, p2;
    vector<Query> q1, q2;
    vector<Item> items;
    for (const auto &p: plates) {
        if (p.v <= mid) {
            p1.push_back(p);
            items.push_back({p.x1, p.y1, p.y2, 0});
            items.push_back({p.x2+1, p.y1, p.y2, -1});
        } else {
            p2.push_back(p);
        }
    }

    for (int i = 0; i < (int)queries.size(); i++) {
        const auto &q = queries[i];
        items.push_back({q.x, q.y, i, q.k});
    }

    sort(items.begin(), items.end());

    for (const auto &item: items) {
        if (item.type == 0) {
            ft.set(item.l, 1);
            ft.set(item.r+1, -1);
        } else if (item.type == -1) {
            ft.set(item.l, -1);
            ft.set(item.r+1, 1);
        } else {
            int cnt = ft.get(item.l);
            if (cnt >= item.type) {
                q1.push_back(queries[item.r]);
            } else {
                queries[item.r].k -= cnt;
                q2.push_back(queries[item.r]);
            }
        }
    }

    divideConquer(l, mid, p1, q1, ft);
    divideConquer(mid+1, r, p2, q2, ft);
}


int main() {
    scanf("%d%d%d", &N, &P, &Q);
    FenwickTree ft(N);
    BinaryLiftLCA lca(N, 0);
    for (int i = 0; i < N-1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        lca.addEdge(a, b);
    }
    lca.build();

    vector<Plate> plates;
    vector<Query> queries;
    for (int i = 0; i < P; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--; b--;
        if (lca.depth[a] < lca.depth[b]) swap(a, b);
        int p = lca.findLCA(a, b);
        if (p != b) {
            int l1 = lca.in_[a], r1 = lca.out_[a];
            int l2 = lca.in_[b], r2 = lca.out_[b];
            if (l1 > l2) {
                swap(l1, l2);
                swap(r1, r2);
            }
            plates.push_back({l1, r1, l2, r2, c});
        } else {
            int k = lca.findFirst(a, b);
            int l1 = 0, r1 = lca.in_[k]-1;
            int l2 = lca.in_[a], r2 = lca.out_[a];
            plates.push_back({l1, r1, l2, r2, c});
            if (lca.out_[k] < N-1) {
                l1 = lca.in_[a];
                r1 = lca.out_[a];
                l2 = lca.out_[k]+1;
                r2 = N-1;
                plates.push_back({l1, r1, l2, r2, c});
            }
        }
    }

    for (int i = 0; i < Q; i++) {
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);
        u--; v--;
        int x = lca.in_[u], y = lca.in_[v];
        if (x > y) swap(x, y);
        queries.push_back({x, y, k, i});
    }
    divideConquer(0, MAXC, plates, queries, ft);

    for (int i = 0; i < Q; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
