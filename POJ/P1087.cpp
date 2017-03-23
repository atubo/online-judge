// http://poj.org/problem?id=1087
// A Plug for UNIX


#include <cmath>
#include <vector>
#include <iostream>
#include <queue>
#include <map>

using namespace std;
typedef long long LL;

struct Edge {
	int from, to, cap, flow, index;
	Edge(int from_, int to_, int cap_, int flow_, int index_) :
		from(from_), to(to_), cap(cap_), flow(flow_), index(index_) {}
};

struct PushRelabel {
	int N;
	vector<vector<Edge> > G;
	vector<LL> excess;
	vector<int> dist, active, count;
	queue<int> Q;

	PushRelabel(int N_) : N(N_), G(N_), excess(N_), dist(N_), active(N_), count(2*N_) {}

	void AddEdge(int from, int to, int cap) {
		G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
		if (from == to) G[from].back().index++;
		G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
	}

	void Enqueue(int v) { 
		if (!active[v] && excess[v] > 0) { active[v] = true; Q.push(v); } 
	}

	void Push(Edge &e) {
		int amt = int(min(excess[e.from], LL(e.cap - e.flow)));
		if (dist[e.from] <= dist[e.to] || amt == 0) return;
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

typedef map<string, string>::const_iterator Iter;
const int INF = 30000000;

int main() {
    map<string, int> recMap;
    PushRelabel pr(510);

    const int S = 0, T = 1;
    int tot = 105;
    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        string s;
        cin >> s;
        recMap[s] = tot++;
        pr.AddEdge(S, recMap[s], 1);
    }

    int M;
    cin >> M;
    for (int i = 1; i <= M; i++) {
        string s, t;
        cin >> s >> t;
        if (recMap.count(t) == 0) {
            recMap[t] = tot++;
        }
        pr.AddEdge(1+i, T, 1);
        pr.AddEdge(recMap[t], 1+i, 1);
    }

    int K;
    cin >> K;
    for (int i = 1; i <= K; i++) {
        string s, t;
        cin >> s >> t;
        if (recMap.count(s) == 0) {
            recMap[s] = tot++;
        }
        if (recMap.count(t) == 0) {
            recMap[t] = tot++;
        }
        int v = recMap[s];
        int u = recMap[t];
        pr.AddEdge(u, v, INF);
    }

    cout << M - pr.GetMaxFlow(0, 1) << endl;
    return 0;
}
