// https://www.luogu.org/problem/show?pid=1954
// [NOI2010]航空管制

#include <bits/stdc++.h>
using namespace std;


// Note graph node is 0-indexed
class Graph {
    static const int MAXM = 500010;
public:
    struct Edge {
        int next, to;
    };
    Edge *E;

    vector<int> head;
    int eidx;
    int N;

    Graph(int N_):N(N_) {
        E = new Edge[MAXM];
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

const int MAXN = 500010;
int N, M;
int K[MAXN];
int ans[MAXN], in[MAXN], topo[MAXN], in2[MAXN];
Graph g(MAXN);
struct Pii {
    int first, second;
    bool operator < (const Pii &other) const {
        if (first < other.first) return true;
        if (first > other.first) return false;
        return second < other.second;
    }
};

void toposort() {
    memcpy(in2, in, sizeof(in));
    priority_queue<Pii> pq;
    for (int i = 1; i <= N; i++) {
        if (!in2[i]) pq.push(Pii{K[i], i});
    }
    for (int i = N; i >= 1; i--) {
        auto p = pq.top();
        pq.pop();
        int u = p.second;
        topo[i] = u;
        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            in2[v]--;
            if (!in2[v]) pq.push(Pii{K[v], v});
        }
    }
}

int solve(int x) {
    memcpy(in2, in, sizeof(in));
    priority_queue<Pii> pq;
    for (int i = 1; i <= N; i++) {
        if (i != x && !in2[i]) pq.push(Pii{K[i], i});
    }
    for (int i = N; i >= 1; i--) {
        if (pq.empty()) return i;
        auto p = pq.top();
        pq.pop();
        if (p.first < i) return i;
        int u = p.second;
        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            in2[v]--;
            if (v != x && !in2[v]) pq.push(Pii{K[v], v});
        }
    }
    //assert(0);
    return -1;
}

int main() {
    scanf("%d%d", &N, &M);

    for (int i = 1; i <= N; i++) {
        int k;
        scanf("%d", &k);
        K[i] = k;
    }

    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        g.addEdge(b, a);
        in[a]++;
    }

    toposort();
    for (int i = 1; i <= N; i++) {
        printf("%d ", topo[i]);
    }
    printf("\n");

    for (int i = 1; i <= N; i++) {
        printf("%d ", solve(i));
    }
    printf("\n");

    return 0;
}
