// https://www.luogu.org/problemnew/show/P4009
// 汽车加油行驶问题

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
    }

private:
    const int N;
    vector<vector<PII>> edges;
    vector<int64_t> dist;
    vector<int> dad;
};

const int64_t FastDijkstra::INF = 0x7FFFFFFFFFFFFFFF;

int N, K, A, B, C;
int G[110][110];

int encode(int i, int j, int d) {
    return d*N*N + i*N + j;
}

int main() {
    scanf("%d%d%d%d%d", &N, &K, &A, &B, &C);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &G[i][j]);
        }
    }

    FastDijkstra dij(N*N*(K+1));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (G[i][j]) {
                int u = encode(i, j, 0);
                for (int d = 1; d <= K; d++) {
                    dij.addEdge(encode(i, j, d), u, A);
                }
                if (i < N-1) dij.addEdge(u, encode(i+1, j, 1), 0);
                if (j < N-1) dij.addEdge(u, encode(i, j+1, 1), 0);
                if (i > 0) dij.addEdge(u, encode(i-1, j, 1), B);
                if (j > 0) dij.addEdge(u, encode(i, j-1, 1), B);
            } else {
                for (int d = 0; d < K; d++) {
                    int u = encode(i, j, d);
                    if (i < N-1) {
                        dij.addEdge(u, encode(i+1, j, d+1), 0);
                    }
                    if (j < N-1) {
                        dij.addEdge(u, encode(i, j+1, d+1), 0);
                    }
                    if (i > 0) {
                        dij.addEdge(u, encode(i-1, j, d+1), B);
                    }
                    if (j > 0) {
                        dij.addEdge(u, encode(i, j-1, d+1), B);
                    }
                }
                if (!(i==N-1 && j==N-1)) {
                    dij.addEdge(encode(i, j, K), encode(i, j, 0), C+A);
                }
            }
        }
    }
    dij.solve(encode(0, 0, 0));
    int64_t ans =  FastDijkstra::INF;
    for (int d = 0; d <= K; d++) {
        ans = min(ans, dij.getDist()[encode(N-1, N-1, d)]);
    }
    printf("%ld\n", ans);
    return 0;
}
