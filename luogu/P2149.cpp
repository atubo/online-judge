// https://www.luogu.org/problem/show?pid=2149
// [SDOI2009]Elaxia的路线

#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;

class FastDijkstra {
public:
    static const int INF;

    FastDijkstra(const vector<vector<PII> >& edges_):
        edges(edges_), N(edges.size()),
        dist(N, INF), dad(N, -1)
    {
        //solve();
    }

    const vector<int>& getDist() const {
        return dist;
    }

    const vector<int>& getDad() const {
        return dad;
    }

    void solve(int s) {
        init();

        // use priority queue in which top element has the "smallest" priority
        priority_queue<PII, vector<PII>, greater<PII> > Q;
        Q.push (make_pair (0, s));
        dist[s] = 0;
        while (!Q.empty()){
            PII p = Q.top();
            Q.pop();

            int here = p.second;
            for (vector<PII>::const_iterator it=edges[here].begin();
                 it!=edges[here].end(); it++){
                if (dist[here] + it->first < dist[it->second]){
                    dist[it->second] = dist[here] + it->first;
                    dad[it->second] = here;
                    Q.push (make_pair (dist[it->second], it->second));
                }
            }
        }
    }
private:
    void init() {
        for (int i = 0; i < N; i++) {
            dist[i] = INF;
            dad[i] = -1;
        }
    }

    const vector<vector<PII> >& edges;
    const int N;
    vector<int> dist;
    vector<int> dad;
};

const int FastDijkstra::INF = 0x7FFFFFFF;

int N, M;
int A, B, C, D;

int solve(const vector<int>& da,
          const vector<int>& db,
          const vector<int>& dc,
          const vector<int>& dd,
          const vector<vector<PII>>& edges,
          const vector<int>& onPath) {
    vector<int> dp(N, 0);
    int ret = 0;
    for (int u: onPath) {
        for (const PII& e: edges[u]) {
            int v = e.second;
            int wt = e.first;
            if (da[v] + db[v] != db[A] || dc[v] + dd[v] != dc[u] + dd[u]) continue;
            if (da[v] + wt == da[u] && dc[v] + wt == dc[u]) {
                dp[u] = max(dp[u], wt + dp[v]);
                ret = max(ret, dp[u]);
            }
        }
    }
    return ret;
}

int main() {
    scanf("%d%d", &N, &M);
    scanf("%d%d%d%d", &A, &B, &C, &D);
    A--; B--; C--; D--;
    vector<vector<int>> adj(N);
    vector<vector<PII>> edges(N);
    for (int i = 0; i < M; i++) {
        int u, v, l;
        scanf("%d%d%d", &u, &v, &l);
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges[u].push_back(make_pair(l, v));
        edges[v].push_back(make_pair(l, u));
    }

    FastDijkstra dijkstra(edges);
    dijkstra.solve(A);
    vector<int> da = dijkstra.getDist();
    dijkstra.solve(B);
    vector<int> db = dijkstra.getDist();
    dijkstra.solve(C);
    vector<int> dc = dijkstra.getDist();
    dijkstra.solve(D);
    vector<int> dd = dijkstra.getDist();

    //for (int i = 0; i < N; i++) {
    //    printf("%d %d %d %d\n", da[i], db[i], dc[i], dd[i]);
    //}
    vector<int> onPath;
    for (int i = 0; i < N; i++) {
        if (da[i] + db[i] == db[A] && dc[i] + dd[i] == dd[C]) {
            onPath.push_back(i);
        }
    }

    sort(onPath.begin(), onPath.end(),
         [&da](int a, int b) {return da[a] < da[b];});
    //for (int x: onPath) {
    //    printf("%d ", x);
    //}
    //printf("\n");

    int ret = solve(da, db, dc, dd, edges, onPath);
    ret = max(ret, solve(da, db, dd, dc, edges, onPath));
    printf("%d\n", ret);

    return 0;
}
