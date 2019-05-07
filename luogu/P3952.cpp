// https://www.luogu.org/problemnew/show/P3952
// 时间复杂度

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
    };

    vector<int> head;
    int eidx;
    int N, M;

    Edge *E;

    Graph(int N_, int M_):N(N_), M(M_) {
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }

        E = new Edge[M]{};
    }

    ~Graph() {
        delete[] E;
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

int T;
int L;
char S[80];
bool INS[26];
int IDX;

struct Frame {
    int var;
    int order;
} frames[128];

int dfs(const Graph &g, int u) {
    auto f = frames[u];
    if (f.order == -1) return 0;
    int mx = 0;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        mx = max(mx, dfs(g, v));
    }
    return f.order + mx;
}

void solve() {
    scanf("%d%s", &L, S);
    memset(INS, 0, sizeof(INS));
    int order = 0;
    if (S[2] == 'n') order = atoi(S+4);

    IDX = 1;
    frames[0] = {'n'-'a', 0};
    stack<int> st;
    st.push(0);

    Graph g(128, 128);

    char cmd[5], vname[5], be[5], en[5];
    bool ok = true;
    for (int i = 0; i < L; i++) {
        scanf("%s", cmd);
        if (cmd[0] == 'F') {
            scanf("%s%s%s", vname, be, en);
            if (!ok) continue;
            int v = vname[0] - 'a';
            if (INS[v]) {
                ok = false;
                continue;
            }
            INS[v] = true;
            if (isdigit(be[0]) && isdigit(en[0])) {
                int x = stoi(be);
                int y = stoi(en);
                if (x <= y) {
                    frames[IDX] = {v, 0};
                } else {
                    frames[IDX] = {v, -1};
                }
                g.addEdge(st.top(), IDX);
                st.push(IDX);
                IDX++;
            } else if (!isdigit(be[0]) && !isdigit(en[0])) {
                frames[IDX] = {v, 0};
                g.addEdge(st.top(), IDX);
                st.push(IDX);
                IDX++;
            } else if (!isdigit(be[0])) {
                frames[IDX] = {v, -1};
                g.addEdge(st.top(), IDX);
                st.push(IDX);
                IDX++;
            } else {
                frames[IDX] = {v, 1};
                g.addEdge(st.top(), IDX);
                st.push(IDX);
                IDX++;
            }
        } else {
            if (!ok) continue;
            if (st.size() <= 1) {
                ok = false;
                continue;
            }
            // pop frame, goto father
            int u = st.top();
            st.pop();
            INS[frames[u].var] = false;
        }
    }
    ok = (ok && st.size() == 1);
    if (!ok) {
        printf("ERR\n");
    } else {
        int ans = dfs(g, 0);
        printf(ans == order ? "Yes\n" : "No\n");
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
