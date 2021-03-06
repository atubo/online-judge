// https://www.luogu.org/problem/show?pid=1339
// [USACO09OCT]热浪Heat Wave

#include <queue>
#include <vector>
#include <inttypes.h>
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

#include <iostream>
int main() {
    int T, C, Ts, Te;
    cin >> T >> C >> Ts >> Te;
    Ts--; Te--;

    vector<vector<PII> > edges(T);
    int a, b, c;
    for (int i = 0; i < C; i++) {
        cin >> a >> b >> c;
        a--; b--;
        edges[a].push_back(make_pair(c, b));
        edges[b].push_back(make_pair(c, a));
    }

    FastDijkstra dijkstra(edges, Ts, Te);
    cout << dijkstra.getDist()[Te] << endl;

    return 0;
}
