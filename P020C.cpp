#include <queue>
#include <vector>
using namespace std;

class FastDijkstra {
public:
    static const int INF  = 2000000000;
    typedef pair<int,int> PII;  // pair = (dist, vertex)

    FastDijkstra(const vector<vector<PII> >& edges_, int s_, int t_):
        edges(edges_), s(s_), t(t_), N(edges.size()),
        dist(N, INF), dad(N, -1)
    {
        solve();
    }

    const vector<int>& getDist() const {
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
    vector<int> dist;
    vector<int> dad;
};

//======================
#include <iostream>
int main()
{
    typedef pair<int, int> PII;

    int n, m;
    cin >> n >> m;
    vector<vector<PII> > edges(n);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--; b--;
        edges[a].push_back(make_pair(w, b));
        edges[b].push_back(make_pair(w, a));
    }

    FastDijkstra dijkstra(edges, 0, n-1);
    const vector<int> dist = dijkstra.getDist();
    const vector<int> dad  = dijkstra.getDad();

    if (dist[n-1] == FastDijkstra::INF) {
        cout << -1 << endl;
    }
    else {
        vector<int> result;
        for (int i = n-1; i != -1; i = dad[i]) {
            result.push_back(i+1);
        }
        for (int i = result.size()-1; i >= 0; i--) {
            cout << result[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
