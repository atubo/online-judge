// https://www.luogu.org/problem/show?pid=2932
// [USACO09JAN]地震造成的破坏Earthquake Damage

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
    static const int MAXM = 200010;
public:
    struct Edge {
        int next, to;
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
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

const int MAXN = 30010;
bool noreturn[MAXN];
int P, C, N;

int main() {
    scanf("%d%d%d", &P, &C, &N);
    Graph g(P);
    for (int i = 0; i < C; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g.addEdge(u, v);
        g.addEdge(v, u);
    }

    for (int i = 0; i < N; i++) {
        int u;
        scanf("%d", &u);
        u--;
        noreturn[u] = true;
        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            noreturn[v] = true;
        }
    }

    int ret = 0;
    for (int i = 0; i < P; i++) {
        ret += noreturn[i];
    }
    printf("%d\n", ret);
    return 0;
}
