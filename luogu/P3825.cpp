// https://www.luogu.org/problemnew/show/P3825
// [NOI2017]游戏

#include <bits/stdc++.h>
using namespace std;

class TarjanSCC {
    struct Edge {
        int to, next;
        bool sign;  // bridge?
    };

public:
    class Graph {
    private:
        int edgenum;
    public:
        const int N;
        vector<int> head;
        vector<Edge> E;
    public:
        Graph(int N_): N(N_) {
            head.resize(N, -1);
            edgenum = 0;
        }

        void addEdge(int u, int v) {
            Edge e = {v, head[u], false};
            E.push_back(e);
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

    vector<int> in, out;        // in and out degrees of the new graph

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

    Graph build() {
        // set up new graph
        Graph ng(taj);
        in.resize(taj, 0);
        out.resize(taj, 0);

        for (int i = 0; i < g.N; i++) {
            for (int eidx = g.head[i]; ~eidx; eidx = g.E[eidx].next) {
                int u = belong[i];
                int v = belong[g.E[eidx].to];
                if (u != v) {
                    ng.addEdge(u, v);
                    out[u]++;
                    in[v]++;
                }
            }
        }
        return ng;
    }

private:
    void tarjan(int u, int fa) {
        DFN[u] = low[u] = ++Time;
        Stack[top++] = u;
        instack[u] = true;

        for (int i = g.head[u]; ~i; i = g.E[i].next) {
            int v = g.E[i].to;
            if (DFN[v] == -1) {
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (DFN[u] < low[v]) {
                    g.E[i].sign = 1;   // it's bridge
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

const int MAXN = 50010;
const int MAXM = 100010;
int N, D;
int M;
int S[MAXN];
int POS[8];
int FWD[3][3] = {{-1, 0, 1}, {0, -1, 1}, {0, 1, -1}};
int BWD[3][2] = {{1, 2}, {0, 2}, {0, 1}};
char ans[MAXN];

struct Rule {
    int i, hi, j, hj;
} rules[MAXM];

void preprocess(int d) {
    for (int i = 0; i < D; i++) {
        S[POS[i]] = (d >> i) & 1;
    }
}

int solve() {
    TarjanSCC::Graph g(2*N);
    for (int k = 0; k < M; k++) {
        int i = rules[k].i;
        int hi = rules[k].hi;
        int j = rules[k].j;
        int hj = rules[k].hj;
        if (S[i] == hi) continue;
        int x = FWD[S[i]][hi];
        int u1 = i + x*N;
        int u2 = i + (1-x)*N;
        if (S[j] == hj) {
            g.addEdge(u1, u2);
        } else {
            int y = FWD[S[j]][hj];
            int v1 = j + y*N;
            int v2 = j + (1-y)*N;
            g.addEdge(u1, v1);
            g.addEdge(v2, u2);
        }
    }

    TarjanSCC tarjan(g);
    tarjan.dfs();

    bool ret = true;
    for (int i = 0; i < N; i++) {
        int u0 = i;
        int u1 = i + N;
        if (tarjan.belong[u0] == tarjan.belong[u1]) {
            ret = false;
            break;
        }
        int t = 1;
        if (tarjan.belong[u0] < tarjan.belong[u1]) t = 0;
        ans[i] = 'A' + BWD[S[i]][t];
    }

    return ret;
}

int main() {
    scanf("%d%d", &N, &D);
    string line;
    cin >> line;
    for (int i = 0, cnt = 0; i < N; i++) {
        if (line[i] == 'x') {
            S[i] = -1;
            POS[cnt++] = i;
        }
        else S[i] = line[i] - 'a';
    }
    scanf("%d", &M);
    for (int k = 0; k < M; k++) {
        int i, j;
        char ci[5], cj[5];
        scanf("%d%s%d%s", &i, ci, &j, cj);
        rules[k] = {i-1, ci[0]-'A', j-1, cj[0]-'A'};
    }
    bool ok = false;
    for (int d = 0; d < (1<<D); d++) {
        preprocess(d);
        ok = solve();
        if (ok) break;
    }
    if (ok) printf("%s", ans);
    else printf("-1");
        
    return 0;
}
