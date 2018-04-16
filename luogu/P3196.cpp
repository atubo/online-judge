// https://www.luogu.org/problemnew/show/P3196
// [HNOI2008]神奇的国度

#include <bits/stdc++.h>
using namespace std;


// MCS to find the perfect elimination order for chordal graphs

class MaximumCardinalitySearch {
    // Note graph node is 0-indexed
    class Graph {
    public:
        struct Edge {
            int next, to;
        };

        vector<int> head;
        int eidx;
        int N;

        Edge *E;

        Graph(int N_, int M):N(N_) {
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

public:
    int N;
    Graph g;
    bool *vis;
    int *peo, *deg;

    MaximumCardinalitySearch(int N_, int M): N(N_), g(N_, 2*M) {
        alloc();
    }

    ~MaximumCardinalitySearch() {
        dealloc();
    }

    void addEdge(int u, int v) {
        g.addEdge(u, v);
        g.addEdge(v, u);
    }

    void solve() {
        vector<list<int>> lists(N);
        vector<list<int>::iterator> iters(N);

        for (int i = 0; i < N; i++) {
            lists[0].push_front(i);
            iters[i] = lists[0].begin();
        }

        int maxd = 0;
        for (int k = N-1; k >= 0; k--) {
            while (lists[maxd].empty()) maxd--;
            int x = lists[maxd].front();
            lists[maxd].pop_front();
            peo[k] = x;
            vis[x] = true;
            for (int eidx = g.head[x]; ~eidx; eidx = g.E[eidx].next) {
                int u = g.E[eidx].to;
                if (vis[u]) continue;
                int d = ++deg[u];
                lists[d-1].erase(iters[u]);
                lists[d].push_front(u);
                iters[u] = lists[d].begin();
                maxd = max(maxd, d);
            }
        }
    }

private:
    void alloc() {
        vis = new bool[N]{};
        peo = new int[N]{};
        deg = new int[N]{};
    }

    void dealloc() {
        delete[] vis;
        delete[] peo;
        delete[] deg;
    }
};

int N, M;
int main() {
    scanf("%d%d", &N, &M);
    MaximumCardinalitySearch mcs(N, M);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        mcs.addEdge(u, v);
    }
    mcs.solve();
    int ans = 0;
    for (int i = 0; i < N; i++) {
        ans = max(ans, mcs.deg[i]);
    }
    printf("%d\n", ans+1);
    return 0;
}
