// https://www.luogu.org/problem/show?pid=2936
// [USACO09JAN]全流Total Flow

#include <bits/stdc++.h>
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

const string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int getIndex(char c) {
    for (int i = 0; i < 52; i++) {
        if (c == ALPHA[i]) return i;
    }
    assert(0);
    return -1;
}

int main() {
    int N;
    scanf("%d", &N);
    PushRelabel pr(52);
    char a[10], b[10];
    for (int i = 0; i < N; i++) {
        int f;
        scanf("%s %s %d", a, b, &f);
        int u = getIndex(a[0]);
        int v = getIndex(b[0]);
        pr.AddEdge(u, v, f);
    }

    printf("%lld\n", pr.GetMaxFlow(0, 25));
    return 0;
}
