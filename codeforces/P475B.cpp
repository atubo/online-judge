// http://codeforces.com/problemset/problem/475/B
// "Strongly Connected City"
#include <bits/stdc++.h>
using namespace std;

class TarjanSCC {
    struct Edge {
        int from, to, nex;
        bool sign;  // bridge?
    };

public:
    class Graph {
    private:
        int N, M;
        vector<int> head;
        vector<Edge> edge;
        int edgenum;
    public:
        Graph(int N_): N(N_) {
            head.resize(N, -1);
            edgenum = 0;
        }

        void add(int u, int v) {
            Edge e = {u, v, head[u], false};
            edge.push_back(e);
            head[u] = edgenum++;
        }
        friend class TarjanSCC;
    };

public:
    Graph& g;
    const int N;
    int taj, top, Time;    // SCC index
    vector<int> belong; // node -> its component
    vector<bool> instack;
    vector<vector<int> > bcc;   // component -> all nodes in it
    vector<int> DFN;
    vector<int> low;
    vector<int> Stack;

    vector<vector<int> > ng;    // new graph
    vector<int> du;             // in-degree of the new graph

    TarjanSCC(Graph& g_):g(g_), N(g.N) {
        top = Time = 0;
        taj = 0;
        belong.resize(N, -1);
        instack.resize(N, false);
        DFN.resize(N, -1);
        low.resize(N, -1);
        Stack.resize(N, -1);
    }

    void dfs() {
        for (int i = 0; i < N; i++) {
            if (DFN[i] == -1) tarjan(i, i);
        }
    }

    void assign() {
        // set up new graph
        ng.resize(taj);
        du.resize(taj, 0);
        for (int i = 0; i < g.edgenum; i++) {
            int u = belong[g.edge[i].from], v = belong[g.edge[i].to];
            if (u != v) {
                ng[u].push_back(v);
                du[v]++;
            }
        }
    }

private:
    void tarjan(int u, int fa) {
        DFN[u] = low[u] = ++Time;
        Stack[top++] = u;
        instack[u] = true;

        for (int i = g.head[u]; ~i; i = g.edge[i].nex) {
            int v = g.edge[i].to;
            if (DFN[v] == -1) {
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (DFN[u] < low[v]) {
                    g.edge[i].sign = 1;   // it's bridge
                }
            } else if (instack[v]) low[u] = min(low[u], DFN[v]);
        }

        if (low[u] == DFN[u]) {
            int now;
            bcc.push_back(vector<int>());
            do {
                now = Stack[--top];
                instack[now] = false;
                belong[now] = taj;
                bcc[taj].push_back(now);
            } while (now != u);
            taj++;
        }
    }
};

class Solution {
    using Graph = TarjanSCC::Graph;
private:
    int N, M;
public:
    Solution() {
        cin >> N >> M;
    }

    int flatten(int i, int j) {
        return i * M + j;
    }

    void linkRight(Graph& g, int i) {
        for (int j = 0; j < M-1; j++) {
            g.add(flatten(i, j), flatten(i, j+1));
        }
    }

    void linkLeft(Graph& g, int i) {
        for (int j = 1; j < M; j++) {
            g.add(flatten(i, j), flatten(i, j-1));
        }
    }

    void linkUp(Graph& g, int i) {
        for (int j = 1; j < N; j++) {
            g.add(flatten(j, i), flatten(j-1, i));
        }
    }

    void linkDown(Graph& g, int i) {
        for (int j = 0; j < N-1; j++) {
            g.add(flatten(j, i), flatten(j+1, i));
        }
    }


    void solve() {
        TarjanSCC::Graph g(N*M);
        string s;
        cin >> s;
        for (int i = 0; i < N; i++) {
            if (s[i] == '>') linkRight(g, i);
            else linkLeft(g, i);
        }
        cin >> s;
        for (int i = 0; i < M; i++) {
            if (s[i] == 'v') linkDown(g, i);
            else linkUp(g, i);
        }

        TarjanSCC tarjan(g);
        tarjan.dfs();
        tarjan.assign();
        cout << (tarjan.taj == 1 ? "YES" : "NO") << endl;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
