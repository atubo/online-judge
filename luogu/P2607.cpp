// https://www.luogu.org/problemnew/show/P2607
// [ZJOI2008]骑士

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

const int MAXN = 1000010;
int N;
int S[MAXN], nxt[MAXN], component[MAXN], lead[MAXN];
int64_t dp[MAXN][2];
bool vis[MAXN];
int component_id;
int64_t ans;

void traverse(Graph &g, int u) {
    stack<int> stk;
    while (true) {
        vis[u] = true;
        stk.push(u);
        u = nxt[u];
        if (vis[u]) break;
    }
    if (component[u] == -1) {
        while (stk.top() != u) {
            int v = stk.top();
            stk.pop();
            component[v] = component_id;
        }
        stk.pop();
        lead[component_id] = u;
        component[u] = component_id;

        component_id++;
    }

    while (!stk.empty()) {
        u = stk.top();
        stk.pop();
        int v = nxt[u];
        g.addEdge(v, u);
        component[u] = component[v];
    }
}

int64_t solve(const Graph &g, int u, bool enlist) {
    if (dp[u][enlist] >= 0) return dp[u][enlist];
    int64_t &res = dp[u][enlist] = 0;

    if (enlist) {
        res += S[u];
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            res += solve(g, v, false);
        }
    } else {
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            res += max(solve(g, v, true), solve(g, v, false));
        }
    }
    return res;
}

void solveLoop(int u0) {
    int u = u0;
    vector<int> line;
    do {
        line.push_back(u);
        u = nxt[u];
    } while (u != u0);
    int n = line.size();
    vector<pair<int64_t, int64_t>> dp1(n), dp2(n);
    dp1[0].first = dp[line[0]][0];
    for (int i = 1; i < n; i++) {
        dp1[i].first = dp[line[i]][0] + max(dp1[i-1].first, dp1[i-1].second);
        dp1[i].second = dp[line[i]][1] + dp1[i-1].first;
    }
    dp2[0].first = dp[line[0]][0];
    dp2[0].second = dp[line[0]][1];
    for (int i = 1; i < n-1; i++) {
        dp2[i].first = dp[line[i]][0] + max(dp2[i-1].first, dp2[i-1].second);
        dp2[i].second = dp[line[i]][1] + dp2[i-1].first;
    }
    int64_t s = max(dp1[n-1].first, dp1[n-1].second);
    if (n > 1) {
        s = max(s, max(dp2[n-2].first, dp2[n-2].second) + dp[line[n-1]][0]);
    } else {
        s = max(s, max(dp2[0].first, dp2[0].second));
    }
    ans += s;
}


void solveComponent(const Graph &g, int comp) {
    int u = lead[comp];
    do {
        dp[u][0] = solve(g, u, 0);
        dp[u][1] = solve(g, u, 1);
        u = nxt[u];
    } while (u != lead[comp]);

    solveLoop(lead[comp]);
}

int main() {
    memset(component, -1, sizeof(component));
    memset(lead, -1, sizeof(lead));
    memset(dp, -1, sizeof(dp));
    scanf("%d", &N);
    Graph g(N, N);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &S[i], &nxt[i]);
        nxt[i]--;
    }

    for (int i = 0; i < N; i++) {
        if (!vis[i]) traverse(g, i);
    }

    for (int i = 0; i < component_id; i++) {
        solveComponent(g, i);
    }

    printf("%lld", ans);

    return 0;
}
