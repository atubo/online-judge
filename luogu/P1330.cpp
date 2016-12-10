// https://www.luogu.org/problem/show?pid=1330
// 封锁阳光大学
#include <cassert>
#include <cstdio>
#include <utility>
#include <vector>
using namespace std;
typedef vector<vector<int> > Adj;
typedef pair<int, int> PII;

bool dfs(int u, int c, const Adj& adj,
         vector<int>& color,
         vector<bool>& visited, PII& count) {
    assert(color[u] == -1);
    visited[u] = true;
    color[u] = c;
    if (c == 0) count.first++;
    else count.second++;

    for (int i = 0; i < (int)adj[u].size(); i++) {
        int v = adj[u][i];
        if (!visited[v]) {
            if (!dfs(v, !c, adj, color, visited, count)) return false;
        } else {
            if (color[v] != !c) return false;
        }
    }
    return true;
}


int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    vector<int> color(N, -1);
    Adj adj(N);
    int a, b;
    while (M--) {
        scanf("%d %d", &a, &b);
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<bool> visited(N, false);
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            PII count = make_pair(0, 0);
            if (!dfs(i, 0, adj, color, visited, count)) {
                printf("Impossible\n");
                return 0;
            } else {
                ans += min(count.first, count.second);
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
