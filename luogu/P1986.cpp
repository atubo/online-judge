// https://www.luogu.org/problem/show?pid=1986
// 元旦晚会

#include <bits/stdc++.h>
using namespace std;

const int INF = 123456789;

struct Edge {
    Edge(int u_, int v_, int w_): u(u_), v(v_), w(w_) {}
    int u, v, w;
};

bool bellman_ford(const vector<Edge>& edges, int n, int src,
                  vector<int>& dist) {
    // intialize
    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[src] = 0;

    for (int i = 0; i < n-1; i++) {
        for (const Edge& e: edges) {
            int t = dist[e.u] + e.w;
            if (dist[e.u] != INF && t < dist[e.v]) {
                dist[e.v] = t;
            }
        }
    }

    // check negative loop
    for (const Edge& e: edges) {
        if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
            return false;
        }
    }
    return true;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    vector<Edge> edges;
    for (int i = 0; i < M; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        edges.push_back(Edge(b, a-1, -c));
    }

    for (int i = 0; i < N; i++) {
        edges.push_back(Edge(i, i+1, 1));
        edges.push_back(Edge(i+1, i, 0));
    }

    vector<int> dist(N+1);
    bellman_ford(edges, N+1, N, dist);
    printf("%d\n", -dist[0]);
    return 0;
}
