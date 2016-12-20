// https://www.luogu.org/problem/show?pid=1144
// 最短路计数
#include <queue>
#include <vector>
#include <inttypes.h>
using namespace std;

typedef pair<int64_t,int> PII;  // pair = (dist, vertex)

const int MOD = 100003;

int add(int a, int b) {
    return (a + b) % MOD;
}


class FastDijkstra {
public:
    static const int64_t INF;


    FastDijkstra(const vector<vector<PII> >& edges_, int s_, int t_):
        edges(edges_), s(s_), t(t_), N(edges.size()),
        dist(N, INF), dad(N, -1), ways(N, 0)
    {
        solve();
    }

    const vector<int64_t>& getDist() const {
        return dist;
    }

    const vector<int>& getDad() const {
        return dad;
    }

public:
    void solve() {
        // use priority queue in which top element has the "smallest" priority
        priority_queue<PII, vector<PII>, greater<PII> > Q;
        Q.push (make_pair (0, s));
        dist[s] = 0;
        ways[s] = 1;
        while (!Q.empty()){
            PII p = Q.top();
            //if (p.second == t) break;
            Q.pop();

            int here = p.second;
            for (vector<PII>::const_iterator it=edges[here].begin();
                 it!=edges[here].end(); it++){
                if (dist[here] + it->first < dist[it->second]){
                    dist[it->second] = dist[here] + it->first;
                    dad[it->second] = here;
                    Q.push (make_pair (dist[it->second], it->second));
                    ways[it->second] = ways[here];
                } else if (dist[here] + it->first == dist[it->second]) {
                    ways[it->second] = add(ways[it->second], ways[here]);
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
    vector<int> ways;
};

const int64_t FastDijkstra::INF = 0x7FFFFFFFFFFFFFFF;

#include <cstdio>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    vector<vector<PII> > edges(N);
    int x, y;
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &x, &y);
        x--; y--;
        edges[x].push_back(make_pair(1, y));
        edges[y].push_back(make_pair(1, x));
    }

    FastDijkstra dijkstra(edges, 0, N-1);
    for (int i = 0; i < N; i++) {
        printf("%d\n", dijkstra.ways[i]);
    }

    return 0;
}
