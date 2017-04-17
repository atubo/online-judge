// https://www.luogu.org/problem/show?pid=1231
// 教辅的组成

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

struct Edge {
    int from, to, index;
    LL cap, flow;
    Edge(int from_, int to_, int index_, LL cap_, LL flow_) :
        from(from_), to(to_), index(index_), cap(cap_), flow(flow_) {}
};

struct PushRelabel {
    int N;
    vector<vector<Edge> > G;
    vector<LL> excess;
    vector<int> dist, active, count;
    queue<int> Q;

    PushRelabel(int N_) : N(N_), G(N_), excess(N_), dist(N_), active(N_), count(2*N_) {}

    void AddEdge(int from, int to, LL cap) {
        G[from].push_back(Edge(from, to, G[to].size(), cap, 0));
        if (from == to) G[from].back().index++;
        G[to].push_back(Edge(to, from, G[from].size()-1, 0, 0));
    }

    void Enqueue(int v) { 
        if (!active[v] && excess[v] > 0) { active[v] = true; Q.push(v); } 
    }

    void Push(Edge &e) {
        LL amt = min(excess[e.from], e.cap - e.flow);
        if (dist[e.from] <= dist[e.to] || amt <= 0) return;
        e.flow += amt;
        G[e.to][e.index].flow -= amt;
        excess[e.to] += amt;    
        excess[e.from] -= amt;
        Enqueue(e.to);
    }

    void Gap(int k) {
        for (int v = 0; v < N; v++) {
            if (dist[v] < k) continue;
            count[dist[v]]--;
            dist[v] = max(dist[v], N+1);
            count[dist[v]]++;
            Enqueue(v);
        }
    }

    void Relabel(int v) {
        count[dist[v]]--;
        dist[v] = 2*N;
        for (int i = 0; i < (int)G[v].size(); i++) 
            if (G[v][i].cap - G[v][i].flow > 0)
                dist[v] = min(dist[v], dist[G[v][i].to] + 1);
        count[dist[v]]++;
        Enqueue(v);
    }

    void Discharge(int v) {
        for (int i = 0; excess[v] > 0 && i < (int)G[v].size(); i++) Push(G[v][i]);
        if (excess[v] > 0) {
            if (count[dist[v]] == 1) 
                Gap(dist[v]); 
            else
                Relabel(v);
        }
    }

    LL GetMaxFlow(int s, int t) {
        count[0] = N-1;
        count[N] = 1;
        dist[s] = N;
        active[s] = active[t] = true;
        for (int i = 0; i < (int)G[s].size(); i++) {
            excess[s] += G[s][i].cap;
            Push(G[s][i]);
        }

        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();
            active[v] = false;
            Discharge(v);
        }

        LL totflow = 0;
        for (int i = 0; i < (int)G[s].size(); i++) totflow += G[s][i].flow;
        return totflow;
    }
};

int N1, N2, N3, M1, M2;

int main() {
    scanf("%d%d%d", &N1, &N2, &N3);
    const int S = 0, T = 2*N1+N2+N3+1;
    PushRelabel pr(T+1);

    for (int i = 1; i <= N2; i++) {
        pr.AddEdge(S, i, 1);
    }
    for (int i = 2*N1+N2+1; i <= 2*N1+N2+N3; i++) {
        pr.AddEdge(i, T, 1);
    }
    for (int i = 1; i <= N1; i++) {
        pr.AddEdge(N2+2*i-1, N2+2*i, 1);
    }

    scanf("%d", &M1);
    int x, y;
    for (int i = 0; i < M1; i++) {
        scanf("%d%d", &x, &y);
        pr.AddEdge(y, N2+2*x-1, 1);
    }

    scanf("%d", &M2);
    for (int i = 0; i < M2; i++) {
        scanf("%d%d", &x, &y);
        pr.AddEdge(N2+2*x, 2*N1+N2+y, 1);
    }

    printf("%lld\n", pr.GetMaxFlow(S, T));
    return 0;
}
