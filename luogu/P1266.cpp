// https://www.luogu.org/problemnew/show/P1266
// 速度限制

#include <bits/stdc++.h>
using namespace std;

int W[151][151];
float dist[151*501];

struct Cmp {
    bool operator () (int u, int v) const {
        return dist[u] > dist[v];
    }
};

class FastDijkstra {
public:
    static const double INF;

    FastDijkstra(int N_): N(N_), edges(N), dad(N, -1) {}

    void addEdge(int u, int v) {
        edges[u].push_back(v);
    }

    void solve(int s) {
        // use priority queue in which top element has the "smallest" priority
        //auto comp = [=](int u, int v) {return dist[u] > dist[v];};
        //priority_queue<int, vector<int>,decltype(comp)> Q(comp);
        priority_queue<int, vector<int>, Cmp> Q;
        dist[s] = 0;
        Q.push(s);
        while (!Q.empty()){
            auto p = Q.top();
            // break here if we want to stop when we find a target node
            Q.pop();

            int here = p;
            for (int u: edges[here]) {
                int speed = u % 501;
                int a = here/501, b = u/501;
                float d2 = dist[here] + 1.0 * W[a][b]/speed;
                if (d2 < dist[u]){
                    dist[u] = d2;
                    dad[u] = here;
                    Q.push(u);
                }
            }
        }
    }

    void reset() {
        //dist.assign(N, INF);
        dad.assign(N, -1);
    }

public:
    const int N;
    vector<vector<int>> edges;
    //vector<float> dist;
    vector<int> dad;
};

const double FastDijkstra::INF = 1e9;
int N, M, D;

void init() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= 500; j++) {
            dist[i*501+j] = 1e9;
        }
    }
}

int main() {
    scanf("%d%d%d", &N, &M, &D);
    init();
    FastDijkstra dij(N*501);
    for (int i = 0; i < M; i++) {
        int a, b, v, l;
        scanf("%d%d%d%d", &a, &b, &v, &l);
        W[a][b] = l;
        if (v != 0) {
            for (int j = 1; j <= 500; j++) {
                int p = a*501 + j;
                int q = b*501 + v;
                dij.addEdge(p, q);
            }
        } else {
            for (int j = 1; j <= 500; j++) {
                int p = a*501 + j;
                int q = b*501 + j;
                dij.addEdge(p, q);
            }
        }
    }
    dij.solve(70);
    double ans = 1e9;
    int t = -1;
    for (int i = 1; i <= 500; i++) {
        if (dist[D*501+i] < ans) {
            ans = dist[D*501+i];
            t = i;
        }
    }
    vector<int> cities;
    int city = D*501 + t;
    while (city != -1) {
        cities.push_back(city/501);
        city = dij.dad[city];
    }
    for (int i = (int)cities.size()-1; i >= 0; i--) {
        printf("%d ", cities[i]);
    }
    printf("\n");
    return 0;
}
