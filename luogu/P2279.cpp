// https://www.luogu.org/problem/show?pid=2279
// [HNOI2003]消防局的设立

#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int> > Adj;
typedef pair<int, int> PII;
typedef pair<int, PII> TIII;

class Solution {
private:
    int N;
    Adj adj;
    vector<int> depth;
    vector<int> father;
public:
    Solution() {
        scanf("%d", &N);
        adj.resize(N);
        depth.resize(N);
        father.resize(N);
        for (int i = 1; i < N; i++) {
            int a;
            scanf("%d", &a);
            a--;
            adj[i].push_back(a);
            adj[a].push_back(i);
        }
    }

    void dfs(int u, int f, int d) {
        father[u] = f;
        depth[u] = d;
        for (int i = 0; i < (int)adj[u].size(); i++) {
            int v = adj[u][i];
            if (v != f) {
                dfs(v, u, d+1);
            }
        }
    }

    void bfs(int u, vector<bool>& covered) {
        queue<TIII> q;
        q.push(make_pair(u, make_pair(-1, 0)));
        while (!q.empty()) {
            TIII t = q.front();
            q.pop();
            int v = t.first;
            int f = t.second.first;
            int d = t.second.second;
            covered[v] = true;
            for (int i = 0; i < (int)adj[v].size(); i++) {
                int w = adj[v][i];
                if (w != f && d < 2) {
                    q.push(make_pair(w, make_pair(v, d+1)));
                }
            }
        }
    }

    void solve() {
        dfs(0, -1, 0);

        vector<bool> covered(N);
        priority_queue<PII> pq;
        for (int i = 0; i < N; i++) {
            pq.push(make_pair(depth[i], i));
        }

        int ans = 0;
        while (!pq.empty()) {
            PII pr = pq.top();
            pq.pop();
            int d = pr.first;
            int u = pr.second;
            if (covered[u]) continue;

            ans++;
            if (d >= 2) {
                int g = father[father[u]];
                bfs(g, covered);
            } else {
                break;
            }
        }
        printf("%d\n", ans);
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
