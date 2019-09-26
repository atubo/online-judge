// https://www.luogu.org/problem/P4175
// [CTSC2008]网络管理

#include <bits/stdc++.h>
using namespace std;

struct SegmentInFenwick {
    int N;  // number of positions, index is 1-based
    int M;  // number of weights, index is 0-based
    int *root;
    int *val, *lc, *rc;
    int top_ = 1, bot_;

    // cap is the number of elements to be added
    SegmentInFenwick(int N_, int M_, int cap): N(N_), M(M_) {
        root = new int[N+1]{};
        //const int numOfNodes = cap * int(log2(N)+2) * int(log2(M)+2) + 1;
        const int numOfNodes = 40000000;
        val = new int[numOfNodes]{};
        lc = new int[numOfNodes]{};
        rc = new int[numOfNodes]{};
        bot_ = numOfNodes - 1;
    }

    ~SegmentInFenwick() {
        delete[] root;
        delete[] val;
        delete[] lc;
        delete[] rc;
    }

    // add value t to weight node w at position x
    void add(int l, int r, int w, int t) {
        if (r < l) return;
        for (int i = l; i <= N; i += lowbit(i)) {
            update(root[i], w, t, 0, M-1);
        }
        for (int i = r+1; i <= N; i += lowbit(i)) {
            update(root[i], w, -t, 0, M-1);
        }
    }

    // weight sum [l, r] for position [1, k]
    int query(int k, int l, int r) const {
        if (l > r) return 0;
        int sum = 0;
        for (int j = k; j; j -= lowbit(j)) {
            sum += querySingleTree(root[j], 0, M-1, l, r);
        }
        return sum;
    }

    int query(int u, int v, int p, int q, int k) const {
        vector<int> ru = build(u);
        vector<int> rv = build(v);
        vector<int> rp = build(p);
        vector<int> rq = build(q);

        int s = query(ru) + query(rv) - query(rp) - query(rq);
        if (s < k) return -1;

        int l = 0, r = M-1;
        while (l < r) {
            int mid = (l + r) / 2;
            auto u2 = goRight(ru);
            auto v2 = goRight(rv);
            auto p2 = goRight(rp);
            auto q2 = goRight(rq);
            s = query(u2) + query(v2) - query(p2) - query(q2);
            if (s >= k) {
                swap(u2, ru);
                swap(v2, rv);
                swap(p2, rp);
                swap(q2, rq);
                l = mid + 1;
            } else {
                k -= s;
                ru = goLeft(ru);
                rv = goLeft(rv);
                rp = goLeft(rp);
                rq = goLeft(rq);
                r = mid;
            }
        }

        return l;
    }

private:
    int lowbit(int x) const {return x & -x;}

    vector<int> goLeft(const vector<int> &rt) const {
        vector<int> ans;
        for (int r: rt) {
            ans.push_back(lc[r]);
        }
        return ans;
    }

    vector<int> goRight(const vector<int> &rt) const {
        vector<int> ans;
        for (int r: rt) {
            ans.push_back(rc[r]);
        }
        return ans;
    }

    vector<int> build(int k) const {
        vector<int> ret;
        if (k > 0) {
            for (int i = k; i; i -= lowbit(i)) {
                ret.push_back(root[i]);
            }
        }
        return ret;
    }

    int query(const vector<int> &rt) const {
        int s = 0;
        for (int r: rt) {
            s += val[r];
        }
        return s;
    }

    void update(int &now, int w, int t, int l, int r) {
        if (!now) now = top_++;
        val[now] += t;
        if (l < r) {
            int mid = (l + r) / 2;
            if (w <= mid) update(lc[now], w, t, l, mid);
            else          update(rc[now], w, t, mid+1, r);
        }
    }

    int querySingleTree(int node, int L, int R, int l, int r) const {
        if (L >= l && R <= r) return val[node];
        if (L > r || R < l) return 0;
        int sum = 0;
        int mid = (L + R) / 2;
        if (l <= mid) sum += querySingleTree(lc[node], L, mid, l, r);
        if (mid < r)  sum += querySingleTree(rc[node], mid+1, R, l, r);
        return sum;
    }
};

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

struct Query {
    int k, a, b;
};

class Solution {
private:
    int *dep_;
    int n_, q_;;
    int curr_ = 1;

    void alloc() {
        in_ = new int[n_+1]{};
        out_ = new int[n_+1]{};
        for (int i = 0; i <= 16; i++) {
            fa_[i] = new int[n_+1]{};
        }
        dep_ = new int[n_+1]{};
        w_ = new int[n_+1]{};
        queries_ = new Query[q_]{};
    }

    void dealloc() {
        delete[] in_;
        delete[] out_;
        for (int i = 0; i <= 16; i++) {
            delete[] fa_[i];
        }
        delete[] dep_;
        delete[] w_;
        delete[] queries_;
    }

public:
    int *in_, *out_, *w_, *fa_[17];
    Query *queries_;
    vector<int> sorted_;

    Solution(int n, int q): n_(n), q_(q) {
        alloc();
    }

    ~Solution() {
        dealloc();
    }

    void dfs(const Graph &g, int u, int f, int d) {
        fa_[0][u] = f;
        dep_[u] = d;
        in_[u] = curr_++;
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (v != f) {
                dfs(g, v, u, d+1);
            }
        }
        out_[u] = curr_ - 1;
    }

    void build() {
        for (int k = 1; k <= 16; k++) {
            for (int u = 1; u <= n_; u++) {
                int v = fa_[k-1][u];
                if (v != 0) {
                    fa_[k][u] = fa_[k-1][v];
                }
            }
        }
    }

    int lca(int u, int v) {
        if (dep_[u] < dep_[v]) swap(u, v);
        int d = dep_[u] - dep_[v];
        while (d) {
            int k = __builtin_ctz(d);
            u = fa_[k][u];
            d = d - (1<<k);
        }
        if (u == v) return u;
        for (int k = 16; k >= 0; k--) {
            if (fa_[k][u] != fa_[k][v]) {
                u = fa_[k][u];
                v = fa_[k][v];
            }
        }
        return fa_[0][u];
    }

    void addQuery(int idx, int k, int a, int b) {
        queries_[idx] = {k, a, b};
    }

    void prep() {
        for (int i = 1; i <= n_; i++) {
            sorted_.push_back(w_[i]);
        }
        for (int i = 0; i < q_; i++) {
            if (queries_[i].k == 0) {
                sorted_.push_back(queries_[i].b);
            }
        }
        sort(sorted_.begin(), sorted_.end());
        sorted_.erase(unique(sorted_.begin(), sorted_.end()), sorted_.end());
        for (int i = 1; i <= n_; i++) {
            w_[i] = lower_bound(sorted_.begin(), sorted_.end(), w_[i])
                - sorted_.begin();
        }
        for (int i = 0; i < q_; i++) {
            if (queries_[i].k == 0) {
                queries_[i].b = lower_bound(sorted_.begin(), sorted_.end(),
                                            queries_[i].b)
                    - sorted_.begin();
            }
        }
    }
};

int N, Q;

int main() {
    scanf("%d%d", &N, &Q);
    Solution solution(N, Q);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &solution.w_[i]);
    }
    Graph g(N+1, 2*(N-1));
    for (int i = 0; i < N-1; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        g.addEdge(x, y);
        g.addEdge(y, x);
    }
    solution.dfs(g, 1, 0, 0);
    solution.build();

    for (int i = 0; i < Q; i++) {
        int k, a, b;
        scanf("%d%d%d", &k, &a, &b);
        solution.addQuery(i, k, a, b);
    }
    solution.prep();

    const int m = solution.sorted_.size();
    SegmentInFenwick sif(N, m, 2*(N+m));

    for (int i = 1; i <= N; i++) {
        int l = solution.in_[i];
        int r = solution.out_[i];
        sif.add(l, r, solution.w_[i], 1);
    }

    for (int i = 0; i < Q; i++) {
        int k = solution.queries_[i].k;
        int a = solution.queries_[i].a;
        int b = solution.queries_[i].b;
        if (k == 0) {
            sif.add(solution.in_[a], solution.out_[a],
                    solution.w_[a], -1);
            sif.add(solution.in_[a], solution.out_[a],
                    b, 1);
            solution.w_[a] = b;
        } else {
            int p = solution.lca(a, b);
            int q = solution.fa_[0][p];
            int ans = sif.query(solution.in_[a],
                                solution.in_[b],
                                solution.in_[p],
                                solution.in_[q],
                                k);
            if (ans >= 0) {
                printf("%d\n", solution.sorted_[ans]);
            } else {
                printf("invalid request!\n");
            }
        }
    }

    return 0;
}
