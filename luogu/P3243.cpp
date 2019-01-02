// https://www.luogu.org/problemnew/show/P3243
// [HNOI2015]菜肴制作

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

const int MAXN = 100010;
int D;
int N, M;
int in[MAXN], out[MAXN];

void solve() {
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    scanf("%d%d", &N, &M);
    Graph g(N, M);
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--; y--;
        g.addEdge(y, x);
        out[y]++;
        in[x]++;
    }

    priority_queue<int> pq;
    for (int i = 0; i < N; i++) {
        if (!in[i]) pq.push(i);
    }

    vector<int> ans;
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        ans.push_back(u);
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            in[v]--;
            if (!in[v]) pq.push(v);
        }
    }
    if ((int)ans.size() == N) {
        reverse(ans.begin(), ans.end());
        for (int u: ans) {
            printf("%d ", u+1);
        }
        printf("\n");
    } else {
        printf("Impossible!\n");
    }
}

int main() {
    scanf("%d", &D);
    while (D--) {
        solve();
    }
    return 0;
}
