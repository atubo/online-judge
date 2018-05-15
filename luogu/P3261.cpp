// https://www.luogu.org/problemnew/show/P3261
// [JLOI2015]城池攻占

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

const int MAXN = 300010;
int fa[MAXN], dep[MAXN];
int anc[MAXN][10];
int64_t factor[MAXN][10], term[MAXN][10], req[MAXN][10];
int64_t H[MAXN];
int sacrifice[MAXN], occupy[MAXN];

int N, M;

void bfs(const Graph &g) {
    queue<pair<int, int>> q;
    q.push(make_pair(0, 0));
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        int u = p.first;
        int d = p.second;
        dep[u] = d;
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            q.push(make_pair(v, d+1));
        }
    }
}

int getAnc(int u, int k) {
    for (int i = 0; i < 4; i++) {
        u = anc[u][k-1];
        if (u == -1) return -1;
    }
    return u;
}

void build1() {
    for (int i = 0; i < N; i++) {
        anc[i][0] = fa[i];
    }
    for (int k = 1; k < 10; k++) {
        for (int i = 0; i < N; i++) {
            anc[i][k] = getAnc(i, k);
        }
    }
}

void calcCoeff(int u0, int k) {
    int u = u0;
    int64_t f = factor[u][k-1];
    int64_t t = term[u][k-1];
    for (int i = 0; i < 3; i++) {
        u = anc[u][k-1];
        if (u == -1) return;
        f = f * factor[u][k-1];
        t = t * factor[u][k-1] + term[u][k-1];
    }
    factor[u0][k] = f;
    term[u0][k] = t;
}

void build2() {
    for (int k = 1; k < 10; k++) {
        for (int i = 0; i < N; i++) {
            calcCoeff(i, k);
        }
    }
}

void calcReq(int u0, int k) {
    if (anc[u0][k] == -1) return;
    int u1 = anc[u0][k-1], u2 = anc[u1][k-1], u3 = anc[u2][k-1];
    int64_t a = factor[u2][k-1];
    int64_t b = term[u2][k-1];
    int64_t x = (req[u3][k-1] - b + a - 1) / a;
    x = max(x, req[u2][k-1]);
    a = factor[u1][k-1];
    b = term[u1][k-1];
    x = (x - b + a - 1) / a;
    x = max(x, req[u1][k-1]);
    a = factor[u0][k-1];
    b = term[u0][k-1];
    x = (x - b + a - 1) / a;
    x = max(x, req[u0][k-1]);
    req[u0][k] = x;
}


void build3() {
    for (int i = 0; i < N; i++) {
        req[i][0] = H[i];
    }
    for (int k = 1; k < 10; k++) {
        for (int i = 0; i < N; i++) {
            calcReq(i, k);
        }
    }
}

void solve(int knight, int64_t s, int c) {
    int dFirst = dep[c];
    int k = 9;
    int last = -1;
    while (true) {
        while (k >= 0 && (anc[c][k] == -1 || s < req[c][k])) k--;
        if (k < 0) {
            if (c == 0 && s >= req[c][0]) last = -1;
            else last = c;
            break;
        }
        while (c >= 0 && anc[c][k] >= 0 && s >= req[c][k]) {
            s = factor[c][k] * s + term[c][k];
            c = anc[c][k];
        }
    }
    if (last >= 0) sacrifice[last]++;
    occupy[knight] = dFirst - (last >= 0 ? dep[last] : -1);
}

int main() {
    scanf("%d%d", &N, &M);
    Graph g(N, N-1);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &H[i]);
    }
    for (int i = 1; i < N; i++) {
        int a;
        int64_t v;
        scanf("%d%d%lld", &fa[i], &a, &v);
        fa[i]--;
        g.addEdge(fa[i], i);
        if (a == 0) {
            factor[i][0] = 1;
            term[i][0] = v;
        } else {
            factor[i][0] = v;
            term[i][0] = 0;
        }
    }
    fa[0] = -1;
    bfs(g);
    build1();
    build2();
    build3();

    for (int i = 0; i < M; i++) {
        int64_t s;
        int c;
        scanf("%lld%d", &s, &c);
        solve(i, s, c-1);
    }

    for (int i = 0; i < N; i++) {
        printf("%d\n", sacrifice[i]);
    }
    for (int i = 0; i < M; i++) {
        printf("%d\n", occupy[i]);
    }
    return 0;
}
