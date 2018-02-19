// https://www.luogu.org/problemnew/show/P2939
// [USACO09FEB]改造路Revamping Trails

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

    int64_t solve(int s, int t) {
        // use priority queue in which top element has the "smallest" priority
        priority_queue<PII, vector<PII>, greater<PII> > Q;
        Q.push (make_pair (0, s));
        dist[s] = 0;
        while (!Q.empty()){
            PII p = Q.top();
            if (p.second == t) break;
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
        return dist[t];
    }

private:
    const int N;
    vector<vector<PII>> edges;
    vector<int64_t> dist;
    vector<int> dad;
};

const int64_t FastDijkstra::INF = 0x7FFFFFFFFFFFFFFF;

int N, M, K;

int main() {
    scanf("%d%d%d", &N, &M, &K);
    FastDijkstra dij((K+1)*N+1);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        for (int k = 0; k <= K; k++) {
            dij.addEdge(k*N+u, k*N+v, w);
            dij.addEdge(k*N+v, k*N+u, w);
            if (k < K) {
                dij.addEdge(k*N+u, (k+1)*N+v, 0);
                dij.addEdge(k*N+v, (k+1)*N+u, 0);
            }
        }
    }
    printf("%lld\n", dij.solve(1, (K+1)*N));
    return 0;
}
