// https://www.luogu.org/problem/show?pid=1993
// 小 K 的农场

#include <bits/stdc++.h>
using namespace std;

struct Graph {
    static const int MAXN = 20010;
    vector<int> head;
    int N;

    int next[MAXN];
    int to[MAXN];
    int weight[MAXN];

    Graph(int N_): N(N_) {
        head.resize(N);
    }

    void addEdge(int u, int v, int w) {
        static int q = 1;
        to[q] = v;
        weight[q] = w;
        next[q] = head[u];
        head[u] = q++;
    }
};


class SPFA {
    const static int INF;

public:
    SPFA(const Graph& g): graph(g) {
        N = graph.N;
    }

    void init(int src) {
        while (!Q.empty()) Q.pop();
        inq.clear();
        dist.clear();
        path.clear();

        inq.resize(N, 0);
        dist.resize(N, INF);
        path.resize(N, src);

        dist[src] = 0;
    }

    bool dfs(int u) {
        if (inq[u]) return false;
        inq[u] = 1;
        for (int j = graph.head[u]; j; j = graph.next[j]) {
            int v = graph.to[j];
            int w = graph.weight[j];
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!dfs(v)) return false;
            }
        }
        inq[u] = 0;
        return true;
    }

private:
    const Graph& graph;
    queue<int> Q;
    int N;
    vector<int> inq;    // if node is in queue
    vector<int> dist;
    vector<int> path;
};

const int SPFA::INF = INT_MAX;

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    Graph g(N+1);
    for (int i = 1; i <= N; i++) {
        g.addEdge(0, i, 0);
    }

    for (int i = 0; i < M; i++) {
        int t, a, b, c;
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d %d %d", &a, &b, &c);
            g.addEdge(b, a, -c);
        } else if (t == 2) {
            scanf("%d %d %d", &a, &b, &c);
            g.addEdge(a, b, c);
        } else {
            scanf("%d %d", &a, &b);
            g.addEdge(a, b, 0);
            g.addEdge(b, a, 0);
        }
    }

    SPFA spfa(g);
    spfa.init(0);
    bool ret = spfa.dfs(0);
    if (ret) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}
