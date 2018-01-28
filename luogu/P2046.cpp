// https://www.luogu.org/problemnew/show/P2046
// [NOI2010]海拔

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


const int MAXN = 510;
int N, S, T;
int west[MAXN][MAXN], east[MAXN][MAXN];
int south[MAXN][MAXN], north[MAXN][MAXN];

int id(int i, int j) {
    if (i < 0 || j >= N) return S;
    if (i >= N || j < 0) return T;
    return i * N + j;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N+1; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &east[i][j]);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N+1; j++) {
            scanf("%d", &south[i][j]);
        }
    }
    for (int i = 0; i < N+1; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &west[i][j]);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N+1; j++) {
            scanf("%d", &north[i][j]);
        }
    }

    S = N*N;
    T = S + 1;

    FastDijkstra dij(T+1);
    // west-east
    for (int i = 0; i < N+1; i++) {
        for (int j = 0; j < N; j++) {
            int up = id(i-1, j);
            int down = id(i, j);
            dij.addEdge(up, down, east[i][j]);
            dij.addEdge(down, up, west[i][j]);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N+1; j++) {
            int left = id(i, j-1);
            int right = id(i, j);
            dij.addEdge(left, right, north[i][j]);
            dij.addEdge(right, left, south[i][j]);
        }
    }

    printf("%lld", dij.solve(S, T));

    return 0;
}
