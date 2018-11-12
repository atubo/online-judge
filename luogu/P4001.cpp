// https://www.luogu.org/problemnew/show/P4001
// [BJOI2006]狼抓兔子

#include <bits/stdc++.h>
using namespace std;

class FastDijkstra {
public:
    static const int INF;

    typedef pair<int,int> PII;  // pair = (dist, vertex)

    FastDijkstra(int N_): N(N_), edges(N), dist(N, INF), dad(N, -1) {}

    void addEdge(int u, int v, int wt) {
        edges[u].push_back(make_pair(wt, v));
    }

    const vector<int>& getDist() const {
        return dist;
    }

    const vector<int>& getDad() const {
        return dad;
    }

    void solve(int s, int t) {
        // use priority queue in which top element has the "smallest" priority
        priority_queue<PII, vector<PII>, greater<PII> > Q;
        Q.push (make_pair (0, s));
        dist[s] = 0;
        while (!Q.empty()){
            PII p = Q.top();
            // break here if we want to stop when we find a target node
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
    }

    void reset() {
        dist.assign(N, INF);
        dad.assign(N, -1);
    }

private:
    const int N;
    vector<vector<PII>> edges;
    vector<int> dist;
    vector<int> dad;
};

const int FastDijkstra::INF = 0x7FFFFFFF;
const int MAXN = 1010;
int N, M;
int H[MAXN][MAXN], V[MAXN][MAXN], D[MAXN][MAXN];

int id1(int x, int y) {
    return 2*(x*(M-1) + y);
}

int id2(int x, int y) {
    return id1(x, y) + 1;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M-1; j++) {
            scanf("%d", &H[i][j]);
        }
    }
    for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &V[i][j]);
        }
    }
    for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < M-1; j++) {
            scanf("%d", &D[i][j]);
        }
    }

    if (N == 1) {
        int ans = INT_MAX;
        for (int i = 0; i < M-1; i++) {
            ans = min(ans, H[0][i]);
        }
        printf("%d\n", ans);
        return 0;
    }

    if (M == 1) {
        int ans = INT_MAX;
        for (int i = 0; i < N-1; i++) {
            ans = min(ans, V[i][0]);
        }
        printf("%d\n", ans);
        return 0;
    }

    const int src = 2*(N-1)*(M-1);
    const int dst = src + 1;
    FastDijkstra dij(dst+1);

    for (int i = 0; i < N-1; i++) {
        dij.addEdge(src, id1(i, 0), V[i][0]);
    }
    for (int i = 0; i < M-1; i++) {
        dij.addEdge(src, id1(N-2, i), H[N-1][i]);
    }
    for (int i = 0; i < M-1; i++) {
        dij.addEdge(id2(0, i), dst, H[0][i]);
    }
    for (int i = 0; i < N-1; i++) {
        dij.addEdge(id2(i, M-2), dst, V[i][M-1]);
    }
    for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < M-1; j++) {
            int u1 = id1(i, j);
            int u2 = id2(i, j);
            if (j > 0) dij.addEdge(u1, id2(i, j-1), V[i][j]);
            if (j < M-2) dij.addEdge(u2, id1(i, j+1), V[i][j+1]);
            if (i > 0) dij.addEdge(u2, id1(i-1, j), H[i][j]);
            if (i < N-2) dij.addEdge(u1, id2(i+1, j), H[i+1][j]);
            dij.addEdge(u1, u2, D[i][j]);
            dij.addEdge(u2, u1, D[i][j]);
        }
    }
    dij.solve(src, dst);
    printf("%d\n", dij.getDist()[dst]);
    return 0;
}
