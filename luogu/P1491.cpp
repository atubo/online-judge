// https://www.luogu.org/problemnew/show/P1491
// 集合位置

#include <bits/stdc++.h>
using namespace std;

typedef pair<double,int> PFI;  // pair = (dist, vertex)

const double INF = 1e6;

class FastDijkstra {
public:

    FastDijkstra(const vector<vector<PFI> >& edges_, int s_, int t_):
        edges(edges_), s(s_), t(t_), N(edges.size()),
        dist(N, INF), dad(N, -1)
    {
        solve();
    }

    const vector<double>& getDist() const {
        return dist;
    }

    const vector<int>& getDad() const {
        return dad;
    }

private:
    void solve() {
        // use priority queue in which top element has the "smallest" priority
        priority_queue<PFI, vector<PFI>, greater<PFI> > Q;
        Q.push (make_pair (0.0, s));
        dist[s] = 0;
        while (!Q.empty()){
            PFI p = Q.top();
            if (p.second == t) break;
            Q.pop();

            int here = p.second;
            for (vector<PFI>::const_iterator it=edges[here].begin();
                 it!=edges[here].end(); it++){
                if (dist[here] + it->first < dist[it->second]){
                    dist[it->second] = dist[here] + it->first;
                    dad[it->second] = here;
                    Q.push (make_pair (dist[it->second], it->second));
                }
            }
        }
    }

    const vector<vector<PFI> >& edges;
    const int s;
    const int t;
    const int N;
    vector<double> dist;
    vector<int> dad;
};

const int MAXN = 210;
int N, M;
int X[MAXN], Y[MAXN];

double dist(int p, int q) {
    int sq = (X[p] - X[q]) * (X[p] - X[q]) +
             (Y[p] - Y[q]) * (Y[p] - Y[q]);
    return sqrt(double(sq));
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &X[i], &Y[i]);
    }

    vector<vector<PFI>> edges(N);
    vector<tuple<int, int, int, int>> index(M);
    for (int i = 0; i < M; i++) {
        int p, q;
        scanf("%d%d", &p, &q);
        p--; q--;
        double d = dist(p, q);
        edges[p].push_back(make_pair(d, q));
        edges[q].push_back(make_pair(d, p));
        index[i] = make_tuple(p, edges[p].size()-1, q, edges[q].size()-1);
    }

    FastDijkstra dijkstra(edges, 0, N-1);
    const vector<int> &dad = dijkstra.getDad();
    vector<bool> onPath(N);
    int p = N-1;
    while (p != -1) {
        onPath[p] = true;
        p = dad[p];
    }

    double nextd = INF;
    for (int i = 0; i < M; i++) {
        int a, ia, b, ib;
        tie(a, ia, b, ib) = index[i];
        if (onPath[a] && onPath[b] &&
            (dad[edges[a][ia].second] == a ||
             dad[edges[b][ib].second] == b)) {
            double d0 = edges[a][ia].first;
            edges[a][ia].first = edges[b][ib].first = INF;
            FastDijkstra d(edges, 0, N-1);
            nextd = min(nextd, d.getDist()[N-1]);
            edges[a][ia].first = edges[b][ib].first = d0;
        }
    }

    if (nextd >= INF) {
        printf("-1\n");
    } else {
        printf("%.2lf\n", nextd);
    }
    return 0;
}
