// https://www.luogu.org/problem/show?pid=3110
// [USACO14DEC]驮运Piggy Back

#include <bits/stdc++.h>
using namespace std;
using Adj = vector<vector<int> >;
using PII = pair<int, int>;
int B, E, P, N, M;

void bfs(const Adj& adj, vector<int>& dist, int s) {
    queue<PII> q;
    q.push(make_pair(s, 0));
    dist[s] = 0;
    while (!q.empty()) {
        int u, d;
        tie(u, d) = q.front();
        q.pop();
        for (int v: adj[u]) {
            if (dist[v] == -1) {
                dist[v] = d + 1;
                q.push(make_pair(v, d+1));
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d %d", &B, &E, &P, &N, &M);
    Adj adj(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> distB(N, -1);
    bfs(adj, distB, 0);

    vector<int> distE(N, -1);
    bfs(adj, distE, 1);

    vector<int> distN(N, -1);
    bfs(adj, distN, N-1);

    int ret = INT_MAX;
    for (int u = 0; u < N; u++) {
        if (distB[u] != -1 && distE[u] != -1 && distN[u] != -1) {
            ret = min(ret, distB[u]*B + distE[u]*E + distN[u]*P);
        }
    }

    printf("%d\n", ret);
    return 0;
}
