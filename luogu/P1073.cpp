// https://www.luogu.org/problemnew/show/P1073
// 最优贸易

#include <bits/stdc++.h>
using namespace std;

class TarjanSCC {
    struct Edge {
        int to, next;
        bool sign;  // bridge?
    };

public:
    class Graph {
    private:
        int edgenum;
    public:
        const int N;
        vector<int> head;
        vector<Edge> E;
    public:
        Graph(int N_): N(N_) {
            head.resize(N, -1);
            edgenum = 0;
        }

        void addEdge(int u, int v) {
            Edge e = {v, head[u], false};
            E.push_back(e);
            head[u] = edgenum++;
        }
        friend class TarjanSCC;
    };

public:
    Graph& g;
    const int N;
    int taj, top, Time;    // SCC index
    vector<int> belong; // node -> its component
    vector<bool> instack;
    vector<vector<int> > bcc;   // component -> all nodes in it
    vector<int> DFN;
    vector<int> low;
    vector<int> Stack;

    vector<int> in, out;        // in and out degrees of the new graph

    TarjanSCC(Graph& g_):g(g_), N(g.N) {
        top = Time = 0;
        taj = 0;
        belong.resize(N, -1);
        instack.resize(N, false);
        DFN.resize(N, -1);
        low.resize(N, -1);
        Stack.resize(N, -1);
    }

    void dfs() {
        for (int i = 0; i < N; i++) {
            if (DFN[i] == -1) tarjan(i, i);
        }
    }

    Graph build() {
        // set up new graph
        Graph ng(taj);
        in.resize(taj, 0);
        out.resize(taj, 0);

        for (int i = 0; i < g.N; i++) {
            for (int eidx = g.head[i]; ~eidx; eidx = g.E[eidx].next) {
                int u = belong[i];
                int v = belong[g.E[eidx].to];
                if (u != v) {
                    ng.addEdge(u, v);
                    out[u]++;
                    in[v]++;
                }
            }
        }
        return ng;
    }

private:
    void tarjan(int u, int fa) {
        DFN[u] = low[u] = ++Time;
        Stack[top++] = u;
        instack[u] = true;

        for (int i = g.head[u]; ~i; i = g.E[i].next) {
            int v = g.E[i].to;
            if (DFN[v] == -1) {
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (DFN[u] < low[v]) {
                    g.E[i].sign = 1;   // it's bridge
                }
            } else if (instack[v]) low[u] = min(low[u], DFN[v]);
        }

        if (low[u] == DFN[u]) {
            int now;
            bcc.push_back(vector<int>());
            do {
                now = Stack[--top];
                instack[now] = false;
                belong[now] = taj;
                bcc[taj].push_back(now);
            } while (now != u);
            taj++;
        }
    }
};

// Note: be sure it's DAG
class TopologicalSort {
public:
    vector<int> topo;  // topologically sorted result

private:
    void topologicalSortUtil(const TarjanSCC::Graph &g,
                             int v, bool visited[],
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

    void sort(const TarjanSCC::Graph &g) {
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

const int MAXN = 100010;
int N, M;
int P[MAXN];

int main() {
    scanf("%d%d", &N, &M);
    TarjanSCC::Graph g(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &P[i]);
    }
    for (int i = 0; i < M; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        x--; y--;
        g.addEdge(x, y);
        if (z == 2) g.addEdge(y, x);
    }
    TarjanSCC tarjan(g);
    tarjan.dfs();
    TarjanSCC::Graph dag = tarjan.build();

    vector<int> hi(dag.N), lo(dag.N), maxprofit(dag.N);
    vector<bool> reachable(dag.N, false);
    reachable[tarjan.belong[N-1]] = true;
    for (int i = 0; i < dag.N; i++) {
        //printf("%d: ", i+1);
        hi[i] = INT_MIN, lo[i] = INT_MAX;
        for (int j: tarjan.bcc[i]) {
            hi[i] = max(hi[i], P[j]);
            lo[i] = min(lo[i], P[j]);
            //printf("%d ", j+1);
        }
        //printf("(%d %d)\n", lo[i], hi[i]);
    }

    TopologicalSort topo;
    topo.sort(dag);
#if 0
    for (int x: topo.topo) {
        printf("%d ", x);
    }
    printf("\n");
#endif

    for (int i = topo.topo.size()-1; i >= 0; i--) {
        int u = topo.topo[i];
        int maxp = 0;
        for (int eidx = dag.head[u]; ~eidx; eidx = dag.E[eidx].next) {
            int v = dag.E[eidx].to;
            if (reachable[v]) {
                hi[u] = max(hi[u], hi[v]);
                maxp = max(maxp, maxprofit[v]);
                reachable[u] = true;
            }
        }
        if (reachable[u]) {
            maxprofit[u] = max(maxp, hi[u] - lo[u]);
        }
        //printf("u=%d lo=%d hi=%d maxprofit=%d\n",
        //       u, lo[u], hi[u], maxprofit[u]);
    }
    int x0 = tarjan.belong[0];
    printf("%d\n", maxprofit[x0]);
    return 0;
}
