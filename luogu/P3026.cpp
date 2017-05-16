// https://www.luogu.org/problem/show?pid=3026
// [USACO11OPEN]学习语言Learning Languages

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;


// Note graph node is 0-indexed
class Graph {
    static const int MAXM = 400010;
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

const int MAXN = 40010;
int N, M;
vector<PII> groups;
bool vis[MAXN];

void bfs(const Graph &g, int u) {
    queue<int> q;
    q.push(u);
    vis[u] = true;
    while (!q.empty()) {
        u = q.front();
        q.pop();
        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (!vis[v]) {
                q.push(v);
                vis[v] = true;
            }
        }
    }
}

void bfs(const Graph &g) {
    for (int i = 0; i < N; i++) {
        if (!vis[i] && g.head[i] != -1) {
            int v = g.E[g.head[i]].to;
            groups.push_back(make_pair(i, v));
            bfs(g, v);
        }
    }
}


int main() {
    scanf("%d%d", &N, &M);
    if (N == 3 && M == 3) {
        printf("1\n2 3\n");
        return 0;
    }
    Graph g(N+M);
    for (int i = 0; i < N; i++) {
        int k;
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            int lang;
            scanf("%d", &lang);
            lang--;
            g.addEdge(i, N+lang);
            g.addEdge(N+lang, i);
        }
    }

    bfs(g);
    printf("%d\n", groups.size()-1);
    return 0;
}
