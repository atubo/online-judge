// https://www.luogu.org/problemnew/show/P2176
// [USACO14FEB]路障Roadblock

#include <bits/stdc++.h>
using namespace std;

typedef pair<int64_t,int> PII;  // pair = (dist, vertex)

class FastDijkstra {
public:
    static const int64_t INF;


    FastDijkstra(const vector<vector<PII> >& edges_, int s_, int t_):
        edges(edges_), s(s_), t(t_), N(edges.size()),
        dist(N, INF), dad(N, -1)
    {
        solve();
    }

    const vector<int64_t>& getDist() const {
        return dist;
    }

    const vector<int>& getDad() const {
        return dad;
    }

private:
    void solve() {
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
    }

    const vector<vector<PII> >& edges;
    const int s;
    const int t;
    const int N;
    vector<int64_t> dist;
    vector<int> dad;
};

const int64_t FastDijkstra::INF = 0x7FFFFFFFFFFFFFFF;

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    vector<vector<PII>> edges(N);
    vector<tuple<int, int, int, int>> index(M);
    for (int i = 0; i < M; i++) {
        int a, b, l;
        scanf("%d%d%d", &a, &b, &l);
        a--; b--;
        edges[a].push_back(make_pair(l, b));
        edges[b].push_back(make_pair(l, a));
        index[i] = make_tuple(a, edges[a].size()-1, b, edges[b].size()-1);
    }

    FastDijkstra dijkstra(edges, 0, N-1);
    int64_t dist0 = dijkstra.getDist()[N-1];
    const vector<int> &dad = dijkstra.getDad();
    vector<bool> onPath(N);
    int p = N-1;
    while (p != -1) {
        onPath[p] = true;
        p = dad[p];
    }

    int64_t maxdist = dist0;
    for (int i = 0; i < M; i++) {
        int a, ia, b, ib;
        tie(a, ia, b, ib) = index[i];
        if (onPath[a] && onPath[b] &&
            (dad[edges[a][ia].second] == a ||
             dad[edges[b][ib].second] == b)) {
            edges[a][ia].first *= 2;
            edges[b][ib].first *= 2;
            FastDijkstra d(edges, 0, N-1);
            edges[a][ia].first /= 2;
            edges[b][ib].first /= 2;
            maxdist = max(maxdist, d.getDist()[N-1]);
        }
    }

    printf("%lld\n",maxdist - dist0);
    return 0;
}
