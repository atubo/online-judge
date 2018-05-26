// https://www.luogu.org/problemnew/show/P2018
// 消息传递

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

const int MAXN = 1010;
int N;
int dp[MAXN][MAXN];
int A[MAXN];

int solve(const Graph &g, int u, int fa) {
    if (dp[fa][u] != -1) return dp[fa][u];
    int &ret = dp[fa][u];
    vector<int> tv;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v == fa) continue;
        tv.push_back(solve(g, v, u));
    }
    if (tv.empty()) return ret = 0;
    sort(tv.begin(), tv.end(), greater<int>());
    for (int i = 0; i < (int)tv.size(); i++) {
        ret = max(ret, i+1+tv[i]);
    }
    return ret;
}

int solve2(const Graph &g, int u) {
    vector<int> tv;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        tv.push_back(solve(g, v, u));
    }
    sort(tv.begin(), tv.end(), greater<int>());
    int ret = -1;
    for (int i = 0; i < (int)tv.size(); i++) {
        ret = max(ret, i+1+tv[i]);
    }
    return 1 + ret;
}


int main() {
    memset(dp, -1, sizeof(dp));
    scanf("%d", &N);
    Graph g(N, 2*(N-1));
    for (int i = 1; i < N; i++) {
        int fa;
        scanf("%d", &fa);
        fa--;
        g.addEdge(fa, i);
        g.addEdge(i, fa);
    }
    int ret = INT_MAX;
    for (int i = 0; i < N; i++) {
        A[i] = solve2(g, i);
        ret = min(ret, A[i]);
    }
    printf("%d\n", ret);
    for (int i = 0; i < N; i++) {
        if (A[i] == ret) printf("%d ", i+1);
    }
    return 0;
}
