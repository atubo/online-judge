// https://www.luogu.org/problem/show?pid=2774
// 方格取数问题

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

int M, N;
int A[110][110], C[110][110];

const int DX[4] = {1, 0 -1, 0};
const int DY[4] = {0, 1, 0, -1};

bool inRange(int i, int j) {
    return 0 <= i && i < M && 0 <= j && j < N;
}

const int INF = 1e9;

int main() {
    scanf("%d%d", &M, &N);
    int total = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &A[i][j]);
            total += A[i][j];
        }
    }
    int B = 1, W = (M*N + 1)/2 + 1;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if ((i+j) % 2 == 0) {
                C[i][j] = B++;
            } else {
                C[i][j] = W++;
            }
        }
    }
    int S = 0, T = W;
    PushRelabel pr(T+1);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if ((i+j) % 2 == 0) {
                pr.AddEdge(S, C[i][j], A[i][j]);
                for (int d = 0; d < 4; d++) {
                    int p = i + DX[d];
                    int q = j + DY[d];
                    if (inRange(p, q)) {
                        pr.AddEdge(C[i][j], C[p][q], INF);
                    }
                }
            } else {
                pr.AddEdge(C[i][j], T, A[i][j]);
            }
        }
    }

    printf("%lld\n", total - pr.GetMaxFlow(S, T));
    return 0;
}
