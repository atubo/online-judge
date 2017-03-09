// https://www.luogu.org/problem/show?pid=1993
// 小 K 的农场

#include <bits/stdc++.h>
using namespace std;



typedef vector<map<int, int>> Adj;

class SPFA {
    const static int INF;

public:
    SPFA(const Adj& adj_):adj(adj_) {
        N = adj.size();
    }

    void init(int src) {
        while (!Q.empty()) Q.pop();
        inq.clear();
        dist.clear();
        path.clear();

        inq.resize(N, 0);
        dist.resize(N, INF);
        path.resize(N, src);
        cnt.resize(N, 0);

        dist[src] = 0;
        inq[src]++;
    }

    bool solve(int src) {
        init(src);

        Q.push(src);
        cnt[src]++;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            inq[u]--;

            for (const auto& nbr: adj[u]) {
                int v;
                int w;
                tie(v, w) = nbr;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    path[v] = u;
                    if (!inq[v]) {
                        Q.push(v);
                        inq[v]++;
                        cnt[v]++;
                        if (cnt[v] > N) return false;
                    }
                }
            }
        }
        return true;
    }

    const vector<int>& getDist() const {return dist;}

    const vector<int>& getPath() const {return path;}

private:
    const Adj& adj;
    queue<int> Q;
    int N;
    vector<int> inq;    // if node is in queue
    vector<int> dist;
    vector<int> path;
    vector<int> cnt;
};

const int SPFA::INF = INT_MAX;

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    Adj adj(N+1);
    for (int i = 1; i <= N; i++) {
        adj[0][i] = 0;
    }

    for (int i = 0; i < M; i++) {
        int t, a, b, c;
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d %d %d", &a, &b, &c);
            if (adj[b].count(a) > 0) {
                adj[b][a] = min(adj[b][a], -c);
            } else {
                adj[b][a] = -c;
            }
        } else if (t == 2) {
            scanf("%d %d %d", &a, &b, &c);
            if (adj[a].count(b) > 0) {
                adj[a][b] = min(adj[a][b], c);
            } else {
                adj[a][b] = c;
            }
        } else {
            scanf("%d %d", &a, &b);
            if (adj[a].count(b) > 0) {
                adj[a][b] = min(adj[a][b], 0);
            } else {
                adj[a][b] = 0;
            }
            if (adj[b].count(a) > 0) {
                adj[b][a] = min(adj[b][a], 0);
            } else {
                adj[b][a] = 0;
            }
        }
    }

    SPFA spfa(adj);
    bool ret = spfa.solve(0);
    if (ret) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}
