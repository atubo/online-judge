// https://www.luogu.org/problem/show?pid=1954
// [NOI2010]航空管制

#include <bits/stdc++.h>
using namespace std;


// Note graph node is 0-indexed
class Graph {
    static const int MAXM = 500010;
public:
    struct Edge {
        int next, to;
    };
    Edge *E;

    vector<int> head;
    int eidx;
    int N;

    Graph(int N_):N(N_) {
        E = new Edge[MAXM];
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

const int MAXN = 500010;
int N, M;
int K[MAXN];
int ans[MAXN], in[MAXN], topo[MAXN], in2[MAXN];
Graph g(MAXN);

class Pq {
public:
    int *q;
    int len;
    Pq(int n) {
        q = new int[4*n];
        len = 0;
    }
    ~Pq() {
        delete[] q;
    }

    void push(int i) {
        q[++len] = i;
        int x = len;
        while (x >> 1) {
            if (K[q[x>>1]] >= K[q[x]]) break;
            swap(q[x>>1], q[x]);
            x >>= 1;
        }
    }

    int top() const {
        return q[1];
    }

    bool empty() const {
        return len == 0;
    }

    void pop() {
        q[1] = q[len--];
        int x = 1, v;
        while ((x<<1) <= len) {
            v = x << 1;
            if ((v|1)<= len && K[q[v|1]] > K[q[v]]) v |= 1;
            if (K[q[x]] >= K[q[v]]) break;
            swap(q[x], q[v]);
            x = v;
        }
    }
};

Pq pq(MAXN);

void toposort() {
    pq.len = 0;
    memcpy(in2, in, sizeof(in));
    for (int i = 1; i <= N; i++) {
        if (!in2[i]) pq.push(i);
    }
    for (int i = N; i >= 1; i--) {
        auto u = pq.top();
        pq.pop();
        topo[i] = u;
        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            in2[v]--;
            if (!in2[v]) pq.push(v);
        }
    }
}

int solve(int x) {
    pq.len = 0;
    for (int i = 1; i <= N; i++) {
        if (i != x && !(in2[i]=in[i])) pq.push(i);
    }
    for (int i = N; i >= 1; i--) {
        if (pq.empty()) return i;
        auto u = pq.top();
        pq.pop();
        if (K[u] < i) return i;
        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            in2[v]--;
            if (v != x && !in2[v]) pq.push(v);
        }
    }
    return -1;
}

int main() {
    scanf("%d%d", &N, &M);

    for (int i = 1; i <= N; i++) {
        int k;
        scanf("%d", &k);
        K[i] = k;
    }

    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        g.addEdge(b, a);
        in[a]++;
    }

    toposort();
    for (int i = 1; i <= N; i++) {
        printf("%d ", topo[i]);
    }
    printf("\n");

    for (int i = 1; i <= N; i++) {
        printf("%d ", solve(i));
    }
    printf("\n");

    return 0;
}
