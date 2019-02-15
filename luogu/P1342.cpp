// https://www.luogu.org/problemnew/show/P1342
// 请柬

#include <bits/stdc++.h>
using namespace std;

class FastDijkstra {
public:
    static const int64_t INF;

    typedef pair<int64_t,int> PII;  // pair = (dist, vertex)

    FastDijkstra(int N_): N(N_), edges(N), dist(N, INF), dad(N, -1) {}

    void addEdge(int u, int v, int64_t wt) {
        edges[u].push_back(make_pair(wt, v));
    }

    const vector<int64_t>& getDist() const {
        return dist;
    }

    const vector<int>& getDad() const {
        return dad;
    }

    void solve(int s) {
        // use priority queue in which top element has the "smallest" priority
        priority_queue<PII, vector<PII>, greater<PII> > Q;
        Q.push (make_pair (0, s));
        dist[s] = 0;
        while (!Q.empty()){
            PII p = Q.top();
            // break here if we want to stop when we find a target node
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

    void reset() {
        dist.assign(N, INF);
        dad.assign(N, -1);
        edges.clear();
        edges.resize(N);
    }

private:
    const int N;
    vector<vector<PII>> edges;
    vector<int64_t> dist;
    vector<int> dad;
};

const int64_t FastDijkstra::INF = 0x7FFFFFFFFFFFFFFF;

const int MAXM = 1000010;
int N, M;
struct Edge {
    int u, v, w;
} edges[MAXM];

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        edges[i] = {u, v, w};
    }
    FastDijkstra dij(N);
    for (int i = 0; i < M; i++) {
        dij.addEdge(edges[i].u, edges[i].v, edges[i].w);
    }
    dij.solve(0);
    int64_t ans = 0;
    const auto& dist = dij.getDist();
    for (int i = 0; i < N; i++) {
        ans += dist[i];
    }

    dij.reset();
    for (int i = 0; i < M; i++) {
        dij.addEdge(edges[i].v, edges[i].u, edges[i].w);
    }
    dij.solve(0);
    for (int i = 0; i < N; i++) {
        ans += dist[i];
    }

    printf("%ld\n", ans);
    return 0;
}
