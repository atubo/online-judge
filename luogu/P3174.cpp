// https://www.luogu.org/problemnew/show/P3174
// [HAOI2009]毛毛虫

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
    static const int MAXM = 600010;
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

const int MAXN = 300010;
int N, M;
int nc[MAXN], dp[MAXN], result[MAXN];
int ans;

void dfs(const Graph &g, int u, int f) {
    vector<int> dpchildren;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != f) {
            nc[u]++;
            dfs(g, v, u);
            dpchildren.push_back(dp[v]);
        }
    }
    sort(dpchildren.begin(), dpchildren.end(), greater<int>());
    int maxc1 = dpchildren.size() > 0 ? dpchildren[0] : 0;
    int maxc2 = dpchildren.size() > 1 ? dpchildren[1] : 0;
    dp[u] = maxc1 + max(nc[u]-1, 0) + 1;
    result[u] = dp[u] + (f != -1);
    result[u] = max(result[u], maxc1 + maxc2 + nc[u] - 1 + (f != -1));
    //printf("u=%d dp=%d result=%d\n", u+1, dp[u], result[u]);
    ans = max(ans, result[u]);
}

int main() {
    scanf("%d%d", &N, &M);
    if (M != N-1){
        printf("-1\n");
        return 0;
    }

    Graph g(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        g.addEdge(a, b);
        g.addEdge(b, a);
    }
    dfs(g, 0, -1);
    printf("%d\n", ans);
    return 0;
}
