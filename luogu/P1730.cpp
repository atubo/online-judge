// https://www.luogu.org/problem/show?pid=1730
// 最小密度路径

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
    static const int MAXM = 1100;
public:
    struct Edge {
        int next, to;
        int w;
    } E[MAXM];

    vector<int> head;
    int eidx;
    int N;

    Graph(int N_):N(N_) {
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v, int w) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].w = w;
        head[u] = eidx++;
    }
};

// Note: be sure it's DAG
class TopologicalSort {
public:
    vector<int> topo;  // topologically sorted result

private:
    void topologicalSortUtil(const Graph &g, int v, bool visited[],
                             stack<int> &order) {
        visited[v] = true;

        for (int i = g.head[v]; i != -1; i = g.E[i].next) {
            int m = g.E[i].to;
            if (!visited[m]) {
                topologicalSortUtil(g, m, visited, order);
            }
        }

        order.push(v);
    }

public:
    TopologicalSort() {}

    void sort(const Graph &g) {
        const int N = g.N;
        topo.resize(N);

        stack<int> order;
        bool visited[N];
        for (int i = 0; i < N; i++) {
            visited[i] = false;
        }

        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                topologicalSortUtil(g, i, visited, order);
            }
        }

        int i = 0;
        while (!order.empty()) {
            topo[i++] = order.top();
            order.pop();
        }
    }
};

double dp[110][110][110];

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    Graph g(N);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        g.addEdge(u, v, w);
    }

    TopologicalSort topo;
    topo.sort(g);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                dp[i][j][k] = 1.01e9;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        dp[i][i][0] = 0;
    }

    for (int i = N-1; i >= 0; i--) {
        int u = topo.topo[i];
        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int w = g.E[eidx].w;
            for (int vp = 0; vp < N; vp++) {
                for (int m = 1; m < N; m++) {
                    if (dp[v][vp][m-1] < 1e9) {
                        dp[u][vp][m] = min(dp[u][vp][m], (w + (m-1)*dp[v][vp][m-1])/m);
                    }
                }
            }
        }
    }

    int Q;
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        double ret = 1.01e9;
        for (int m = 0; m < N; m++) {
            ret = min(ret, dp[u][v][m]);
        }
        if (ret < 1e9) {
            printf("%.3lf\n", ret);
        } else {
            printf("OMG!\n");
        }
    }

    return 0;
}
