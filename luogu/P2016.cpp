// https://www.luogu.org/problemnew/show/P2016
// 战略游戏

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1510;
int N;
int depth[MAXN], father[MAXN], numChildren[MAXN];
bool covered[MAXN];

class Comp {
public:
    bool operator()(int a, int b) const {
        if (depth[a] < depth[b]) return true;
        if (depth[a] > depth[b]) return false;
        return a < b;
    }
};

priority_queue<int, vector<int>, Comp> pq;

// Note graph node is 0-indexed
class Graph {
    static const int MAXM = 3000;
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

void dfs(const Graph &g, int u, int fa, int d) {
    depth[u] = d;
    father[u] = fa;
    covered[u] = false;

    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v == fa) continue;
        dfs(g, v, u, d+1);
        numChildren[u]++;
    }
    if (numChildren[u] == 0) {
        pq.push(u);
    }
}

int deploy(const Graph &g, int u) {
    int fa = father[u];
    if (fa == -1) return 0;
    covered[fa] = true;
    for (int eidx = g.head[fa]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != father[fa]) {
            covered[v] = true;
        } else {
            if (--numChildren[v] == 0) {
                pq.push(v);
            }
        }
    }
    return 1;
}

int main() {
    scanf("%d", &N);
    Graph g(N);
    for (int i = 0; i < N; i++) {
        int u, k;
        scanf("%d%d", &u, &k);
        for (int j = 0; j < k; j++) {
            int v;
            scanf("%d", &v);
            g.addEdge(u, v);
            g.addEdge(v, u);
        }
    }
    dfs(g, 0, -1, 0);
    int ans = 0;
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        if (!covered[u]) {
            ans += deploy(g, u);
        }
    }
    printf("%d\n", ans);
    return 0;
}
