// https://www.luogu.org/problemnew/show/P1772
// [ZJOI2006]物流运输

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

    int64_t solve(int s, int t, int mask, int &mask2) {
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
                int to = it->second;
                if ( to == t || (mask>>(to-1)) & 1) {
                    if (dist[here] + it->first < dist[to]){
                        dist[to] = dist[here] + it->first;
                        dad[to] = here;
                        Q.push(make_pair(dist[to], to));
                    }
                }
            }
        }
        if (dist[t] == INF) return -1;
        int path_mask = 0;
        for (int u = dad[t]; u != s; u = dad[u]) {
            path_mask |= (1<<(u-1));
        }
        //if (path_mask != mask) return -1;
        mask2 = path_mask;
        return dist[t];
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
const int MAXN = 110;
const int MAXM = (1<<18);
int N, M, K, E;
int available[MAXN];
int64_t dp[MAXN][MAXM];
bool vis[MAXM];

void mark(int mask, int sup) {
    assert((sup & mask) == mask && sup >= mask);
    int filter = sup & (~mask);
    vector<int> shft;
    for (int i = 0, t = 0; i < 18; i++) {
        if (filter & (1<<i)) {
            shft.push_back(t);
        } else {
            t++;
        }
    }
    int nd = shft.size();
    for (int i = 1; i < (1<<nd); i++) {
        int x = mask;
        for (int j = 0; j < nd; j++) {
            if (i & (1<<j)) {
                x |= (1<<(j+shft[j]));
            }
        }
        vis[x] = true;
    }
}

int main() {
    scanf("%d%d%d%d", &N, &M, &K, &E);

    FastDijkstra dij(M);
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        dij.addEdge(u, v, w);
        dij.addEdge(v, u, w);
    }

    vector<int> mask_list;
    vector<int64_t> dist;
    for (int mask = (1<<(M-2)); mask >= 0; mask--) {
        if (vis[mask]) continue;
        dij.reset();
        int mask2;
        int64_t d = dij.solve(0, M-1, mask, mask2);
        if (d >= 0) {
            mask_list.push_back(mask2);
            dist.push_back(d);
            mark(mask2, mask);
        }
    }

    int d;
    scanf("%d", &d);
    for (int i = 0; i < N; i++) {
        available[i] = (1<<(M-2)) - 1;
    }
    for (int i = 0; i < d; i++) {
        int p, a, b;
        scanf("%d%d%d", &p, &a, &b);
        p--; a--; b--;
        for (int j = a; j <= b; j++) {
            available[j] &= ~(1<<(p-1));
        }
    }

    int64_t prev_min = FastDijkstra::INF;
    for (int i = 0; i < (int)mask_list.size(); i++) {
        int m = mask_list[i];
        if ((m & available[0]) == m) {
            dp[0][i] = dist[i];
        } else {
            dp[0][i] = FastDijkstra::INF;
        }
        prev_min = min(prev_min, dp[0][i]);
    }

    for (int i = 1; i < N; i++) {
        int64_t tmp = FastDijkstra::INF;
        for (int j = 0; j < (int)mask_list.size(); j++) {
            int m = mask_list[j];
            if ((m & available[i]) == m) {
                dp[i][j] = min(dp[i-1][j], prev_min + K) + dist[j];
            } else {
                dp[i][j] = FastDijkstra::INF;
            }
            tmp = min(tmp, dp[i][j]);
        }
        swap(tmp, prev_min);
    }

    printf("%ld", prev_min);

    return 0;
}
