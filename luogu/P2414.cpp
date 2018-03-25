// https://www.luogu.org/problemnew/show/P2414
// [NOI2011]阿狸的打字机

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
    static const int MAXM = 1e5 + 10;
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

        E = new Edge[MAXM]{};
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

class PersistentSegmentTree {
public:
    struct Node {
        int L, R;
        int sum;

        Node(): L(0), R(0), sum(0) {}
    };

    int N; // number of positions, 1-based
    int M; // number of weights, 0-based
    int *root;
    Node *T;
    int T_cnt = 1;

    PersistentSegmentTree(int N_, int M_): N(N_), M(M_) {
        root = new int[N+1]{};
        T = new Node[(N+1) * int(log2(M)+1)]{};
    }

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

    void insert(int &now, int from, int x, int t) {
        now = from;
        insert(now, x, t, 0, M-1);
    }

    // query in range [start, end]
    int query(int rootIndex, int start, int end) {
        return query(root[rootIndex], start, end, 0, M-1);
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
};

class AhoCorasick {
private:
    int sz = 1;
    int curr = 0;
public:
    int *father, *depth, *link, *que;
    int *start, *finish;
    vector<int> stop;
    vector<array<int, 26>> to;

    Graph linkGraph;
    PersistentSegmentTree pst;

    void addNode(int node, int c) {
        to[node][c] = sz++;
        father[sz-1] = node;
        depth[sz-1] = depth[node] + 1;
    }

public:
    const static int MAXN = 1e5 + 10;

    AhoCorasick(): to(MAXN), linkGraph(MAXN), pst(MAXN, MAXN) {
        father = new int[MAXN]{};
        depth  = new int[MAXN]{};
        link   = new int[MAXN]{};
        que    = new int[MAXN]{};
        start  = new int[MAXN]{};
        finish = new int[MAXN]{};
    }

    ~AhoCorasick() {
        delete[] father;
        delete[] depth;
        delete[] link;
        delete[] que;
        delete[] start;
        delete[] finish;
    }

    void add(char c) {
        c -= 'a';
        if (!to[curr][c]) {
            addNode(curr, c);
        }
        curr = to[curr][c];
    }

    void print() {
        stop.push_back(curr);
    }

    void back() {
        curr = father[curr];
    }
    
    void pushLinks() {
        link[0] = -1;
        int st = 0, fi = 1;
        que[0] = 0;
        while (st < fi) {
            int v = que[st++];
            for (int i = 0; i < 26; i++) {
                int u = to[v][i];
                if (u == 0) continue;
                int j = link[v];
                while (j != -1 && !to[j][i]) j = link[j];
                if (j != -1) link[u] = to[j][i];
                linkGraph.addEdge(link[u], u);
                que[fi++] = u;
            }
        }
    }

    void dfsLinkGraph(int u, int &tick) {
        start[u] = ++tick;
        for (int eidx = linkGraph.head[u]; ~eidx;
             eidx = linkGraph.E[eidx].next) {
            int v = linkGraph.E[eidx].to;
            dfsLinkGraph(v, tick);
        }
        finish[u] = tick;
    }

    void buildPersistentSegmentTree() {
        int st = 0, fi = 1;
        que[0] = 0;
        while (st < fi) {
            int v = que[st++];
            for (int i = 0; i < 26; i++) {
                int u = to[v][i];
                if (u == 0) continue;
                pst.insert(pst.root[u], pst.root[v], start[u], 1);
                que[fi++] = u;
            }
        }
    }

    void setup() {
        pushLinks();
        int tick = -1;
        dfsLinkGraph(0, tick);
        buildPersistentSegmentTree();
    }

    void query(int x, int y) {
        x = stop[x];
        y = stop[y];
        printf("%d\n", pst.query(y, start[x], finish[x]));
    }

    void debug() {
        for (int i = 0; i < 3; i++) {
            printf("%d ", stop[i]);
        }
        printf("\n");
    }
};

int main() {
    string s;
    cin >> s;
    AhoCorasick ac;
    for (char c: s) {
        if (c == 'P') ac.print();
        else if (c == 'B') ac.back();
        else ac.add(c);
    }
    ac.setup();
    int M;
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--; y--;
        ac.query(x, y);
    }

    return 0;
}
