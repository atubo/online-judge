// https://www.luogu.org/problemnew/show/P3302
// [SDOI2013]森林

#include <bits/stdc++.h>
using namespace std;

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

struct Query {
    int x, y, k;
};


const int MAXN = 80010;
int N, M, T;
int A[MAXN];
vector<int> B;
Query queries[MAXN];

int Hash(int x) {
    return lower_bound(B.begin(), B.end(), x) - B.begin();
}

class Forest {
private:
    class PersistentSegmentTree {
    public:
        struct Node {
            // L and R are indices of its children
            // real left and right boundaries are not kept in the node
            // to save memory
            int L, R;
            int sum;

            Node(): L(0), R(0), sum(0) {}
        };

        int N; // number of positions, index is 1-based
        int M; // number of weights, index is 0-based
        int *root;
        Node *T;
        int T_cnt = 1;

        PersistentSegmentTree(int N_, int M_): N(N_), M(M_) {
            root = new int[N+1]{};
            T = new Node[(N+1) * 600];
        }

        ~PersistentSegmentTree() {
            delete[] root;
            delete[] T;
        }

        // for user's convenience
        void insert(int currRootIndex, int prevRootIndex, int x, int t) {
            root[currRootIndex] = root[prevRootIndex];
            insert(root[currRootIndex], x, t, 0, M-1);
        }

        // query in range [start, end]
        int query(int rootIndex, int start, int end) {
            return query(root[rootIndex], start, end, 0, M-1);
        }

        int queryKth(int u, int v, int p, int pfa, int k) {
            return queryKth(u, v, p, pfa, k, 0, M-1);
        }


    private:
        // insert a new weight node x with value t
        // current range is [l, r]
        void insert(int &now, int x, int t, int l, int r) {
            T[T_cnt++] = T[now];
            now = T_cnt-1;
            T[now].sum += t;
            if (l == r) return;
            int mid = (l + r) / 2;
            if (x <= mid) insert(T[now].L, x, t, l, mid);
            else          insert(T[now].R, x, t, mid+1, r);
        }

        int query(int node, int start, int end, int l, int r) {
            if (l > r) return 0;
            if (start <= l && r <= end) return T[node].sum;
            int mid = (l + r) / 2;
            int ret = 0;
            if (start <= mid) ret += query(T[node].L, start, end, l, mid);
            if (mid+1 <= end) ret += query(T[node].R, start, end, mid+1, r);
            return ret;
        }

        int lft(int u) const {return T[u].L;}
        int rgt(int u) const {return T[u].R;}

        int queryKth(int u, int v, int p, int pfa, int k, int l, int r) {
            if (l == r) return l;
            int mid = (l + r) / 2;
            int order = T[lft(u)].sum - T[lft(pfa)].sum +
                T[lft(v)].sum - T[lft(p)].sum;
            if (order >= k) {
                return queryKth(lft(u), lft(v), lft(p), lft(pfa), k, l, mid);
            } else {
                return queryKth(rgt(u), rgt(v), rgt(p), rgt(pfa), k-order,
                                mid+1, r);
            }
        }
    };

public:
    const int N;
    Graph g;
    PersistentSegmentTree pst;
    vector<int> dep;
    vector<int> fa;
    vector<array<int, 17>> st;
    vector<int> son;
    vector<bool> vis;

    Forest(int N_): N(N_+1), g(N_+1), pst(N_+1, N_) {
        dep.resize(N);
        fa.resize(N);
        st.resize(N);
        son.resize(N);
        vis.resize(N);
    }

    void addEdge(int u, int v) {
        g.addEdge(u, v);
        g.addEdge(v, u);
    }

    void dfs(int x, int father, int rt) {
        st[x][0] = father;
        for (int k = 1; k <= 16; k++) {
            st[x][k] = st[st[x][k-1]][k-1];
        }
        son[rt]++;
        dep[x] = dep[father] + 1;
        fa[x] = father;
        vis[x] = true;
        pst.insert(x, father, Hash(A[x]), 1);
        for (int eidx = g.head[x]; ~eidx; eidx = g.E[eidx].next) {
            int u = g.E[eidx].to;
            if (u == father) continue;
            dfs(u, x, rt);
        }
    }

    int query(int u, int v, int k) {
        int p = lca(u, v);
        int pfa = st[p][0];
        return pst.queryKth(u, v, p, pfa, k);
    }

private:
    int lca(int x, int y) {
        if (x == y) return x;
        if (dep[x] > dep[y]) swap(x, y);
        for (int k = 16; k >= 0; k--) {
            if (dep[st[y][k]] >= dep[x]) {
                y = st[y][k];
            }
        }
        if (x == y) return x;
        for (int k = 16; k >= 0; k--) {
            if (st[x][k] != st[y][k]) {
                x = st[x][k];
                y = st[y][k];
            }
        }
        return st[x][0];
    }

    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
};

int main() {
    int ts;
    scanf("%d", &ts);
    scanf("%d%d%d", &N, &M, &T);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    B.resize(N);
    for (int i = 0; i < N; i++) {
        B[i] = A[i];
    }
    sort(B.begin(), B.end());
    B.erase(unique(B.begin(), B.end()), B.end());

    Forest forest(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        forest.addEdge(u, v);
    }

    for (int i = 0; i < T; i++) {
        char tp[10];
        int x, y, k;
        scanf("%s", tp);
        printf("type=%s\n", tp);
        if (tp[0] == 'Q') {
            scanf("%d%d%d", &x, &y, &k);
        } else {
            scanf("%d%d", &x, &y);
            x--; y--;
            forest.addEdge(x, y);
        }
    }

    return 0;
}
