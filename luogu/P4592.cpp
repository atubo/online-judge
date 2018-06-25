// https://www.luogu.org/problemnew/show/P4592
// [TJOI2018]异或

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

class PersistentBinaryTrie {
public:
    struct Node {
        int children[2];
        int count;
        Node() {
            children[0] = children[1] = 0;
            count = 0;
        }
    };

    PersistentBinaryTrie(int n, int nd): n_(n), nd_(nd) {
        root_ = new int[n_+1]{};
        nodes_ = new Node[(n_+1) * (nd_+1)]{};
    }

    ~PersistentBinaryTrie() {
        delete[] root_;
        delete[] nodes_;
    }

    void insert(int currRootIndex, int prevRootIndex, int x) {
        root_[currRootIndex] = root_[prevRootIndex];
        doInsert(root_[currRootIndex], x, nd_);
    }

    int query(int rootIndex, int x) const {
        Node node = nodes_[root_[rootIndex]];
        for (int i = nd_-1; i >= 0; i--) {
            int d = (x >> i) & 1;
            int c = node.children[d];
            if (c == 0) return 0;
            node = nodes_[c];
        }
        return node.count;
    }

    void print(int id) const {
        if (id == 0) return;
        printf("node=%d left=%d right=%d count=%d\n",
               id, nodes_[id].children[0], nodes_[id].children[1],
               nodes_[id].count);
        print(nodes_[id].children[0]);
        print(nodes_[id].children[1]);
    }

private:
    int n_; // number of positions, index is 1-based
    int nd_;    // number of digits
public:
    int *root_;
    Node *nodes_;
private:
    int currIdx_ = 1;

    void doInsert(int &now, int x, int d) {
        nodes_[currIdx_++] = nodes_[now];
        now = currIdx_ - 1;
        nodes_[now].count++;
        if (d == 0) return;
        d--;
        int t = (x >> d) & 1;
        doInsert(nodes_[now].children[t], x, d);
    }
};

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
    vector<int> depth;
    vector<vector<int> > father;

public:
    BinaryLiftLCA(int N, int root)
        : N_(N), root_(root), MAXB_(log2(N)+1), g_(N, N-1) {
    }

    void addEdge(int u, int v) {
        g_.addEdge(u, v);
    }

    void build() {
        depth.resize(N_);
        father.resize(N_);
        for (int i = 0; i < N_; i++) {
            father[i].resize(MAXB_, -1);
        }

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

private:
    void dfs(int x, int f, int d) {
        depth[x] = d;
        father[x][0] = f;
        for (int eidx = g_.head[x]; ~eidx; eidx = g_.E[eidx].next) {
            int u = g_.E[eidx].to;
            if (u != f) dfs(u, x, d+1);
        }
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

const int MAXN = 100010;
int N, Q;
int A[MAXN], dfn[MAXN], last[MAXN], father[MAXN];
int currIdx = 1;
using Node = PersistentBinaryTrie::Node;

void dfs(const Graph &g,
         PersistentBinaryTrie &dfnTrie,
         PersistentBinaryTrie &treeTrie,
         BinaryLiftLCA &lca,
         int u, int fa) {
    father[u] = fa;
    dfn[u] = currIdx++;
    dfnTrie.insert(dfn[u], dfn[u]-1, A[u]);
    treeTrie.insert(u, fa, A[u]);
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != fa) {
            lca.addEdge(u, v);
            dfs(g, dfnTrie, treeTrie, lca, v, u);
        }
    }
    last[u] = currIdx - 1;
}

void solve1(const PersistentBinaryTrie &trie, int x, int y) {
    int l = dfn[x] - 1, r = last[x];
    Node left = trie.nodes_[trie.root_[l]];
    Node right = trie.nodes_[trie.root_[r]];

    int ans = 0;
    for (int i = 30; i >= 0; i--) {
        int d = (y >> i) & 1;
        int cntLeft = trie.nodes_[left.children[1-d]].count;
        int cntRight = trie.nodes_[right.children[1-d]].count;
        if (cntRight - cntLeft > 0) {
            ans |= (1 << i);
            left = trie.nodes_[left.children[1-d]];
            right = trie.nodes_[right.children[1-d]];
        } else {
            left = trie.nodes_[left.children[d]];
            right = trie.nodes_[right.children[d]];
        }
    }
    printf("%d\n",ans);
}

void solve2(const PersistentBinaryTrie &trie,
            const BinaryLiftLCA &lca, int x, int y, int z) {
    int p = lca.findLCA(x, y);
    int q = father[p];
    Node nodex = trie.nodes_[trie.root_[x]];
    Node nodey = trie.nodes_[trie.root_[y]];
    Node nodep = trie.nodes_[trie.root_[p]];
    Node nodeq = trie.nodes_[trie.root_[q]];

    int ans = 0;
    for (int i = 30; i >= 0; i--) {
        int d = (z >> i) & 1;
        int cnt1 = trie.nodes_[nodex.children[1-d]].count -
            trie.nodes_[nodeq.children[1-d]].count;
        int cnt2 = trie.nodes_[nodey.children[1-d]].count -
            trie.nodes_[nodep.children[1-d]].count;
        if (cnt1 + cnt2 > 0) {
            ans |= (1 << i);
            nodex = trie.nodes_[nodex.children[1-d]];
            nodey = trie.nodes_[nodey.children[1-d]];
            nodep = trie.nodes_[nodep.children[1-d]];
            nodeq = trie.nodes_[nodeq.children[1-d]];
        } else {
            nodex = trie.nodes_[nodex.children[d]];
            nodey = trie.nodes_[nodey.children[d]];
            nodep = trie.nodes_[nodep.children[d]];
            nodeq = trie.nodes_[nodeq.children[d]];
        }
    }
    printf("%d\n", ans);
}

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    Graph g(N+1, 2*(N-1));
    for (int i = 0; i < N-1; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        g.addEdge(x, y);
        g.addEdge(y, x);
    }

    BinaryLiftLCA lca(N+1, 1);
    PersistentBinaryTrie dfnTrie(N, 31);
    PersistentBinaryTrie treeTrie(N, 31);
    dfs(g, dfnTrie, treeTrie, lca, 1, 0);

    lca.build();

    for (int i = 0; i < Q; i++) {
        int t, x, y, z;
        scanf("%d%d%d", &t, &x, &y);
        if (t == 1) {
            solve1(dfnTrie, x, y);
        } else {
            scanf("%d", &z);
            solve2(treeTrie, lca, x, y, z);
        }
    }
    return 0;
}
