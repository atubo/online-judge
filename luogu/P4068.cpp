// https://www.luogu.org/problemnew/show/P4068
// [SDOI2016]数字配对

#include <bits/stdc++.h>
using namespace std;

class MincostMaxflow {
    // NOTE
    // 1. nodes are 0-indexed
    // 2. call init() before you use it again
public:
    const static int64_t INF = 1e13;

    MincostMaxflow(int N_, int M):N(N_), Q(N_) {
        V = new Edge*[N]{};
        ES = new Edge[2*M]{};
        sp = new int64_t[N]{};
        prev = new int[N]{};
        path = new Edge*[N]{};
        init();
    }

    ~MincostMaxflow() {
        delete[] V;
        delete[] ES;
        delete[] sp;
        delete[] prev;
        delete[] path;
    }

    void addEdge(int a, int b, int64_t cost, int64_t capacity) {
        Edge e1 = {V[a], 0, b, capacity, cost}, e2 = {V[b], 0, a, 0, -cost};
        ES[++EC] = e1; V[a] = &ES[EC];
        ES[++EC] = e2; V[b] = &ES[EC];
        V[a]->op = V[b]; V[b]->op = V[a];
    }

    struct FlowCost {
        int64_t flow, cost;
        FlowCost& operator += (const FlowCost &other) {
            flow += other.flow;
            cost += other.cost;
            return *this;
        }
    };

    // returns maxflow, mincost
    pair<int64_t, int64_t> mincostFlow(int s, int t) {
        FlowCost fc{};
        while (SPFA(s, t)) {
            fc += augment(t);
        }
        return make_pair(fc.flow, fc.cost);
    }

private:
    int N;
    struct Edge {
        Edge *next, *op;
        int t;
        int64_t c, v;    // node, residual, cost
    };

    Edge *ES;
    Edge **V;
    int EC = -1;

    void init() {
        EC = -1;
        memset(V, 0, N * sizeof(Edge*));
    }

    struct Queue {
        Queue(int N_): N(N_) {
            Q = new int[N]{};
            inq = new bool[N]{};
        }

        ~Queue() {
            delete[] Q;
            delete[] inq;
        }

        int N;
        int *Q;
        int QH, QL, Size;
        bool *inq;

        void ins(int v) {
            if (++QL >= N) QL = 0;
            Q[QL] = v;
            inq[v] = true;
            Size++;
        }

        int pop() {
            int r = Q[QH];
            inq[r] = false;
            Size--;
            if (++QH >= N) QH = 0;
            return r;
        }

        void reset() {
            memset(Q, 0, N* sizeof(int));
            QH = Size = 0;
            QL = -1;
        }
    };
    Queue Q;


    int64_t *sp;
    int *prev;
    Edge **path;

    bool SPFA(int s, int t) {
        int u, v;
        for (u = 0; u < N; u++) sp[u] = INF;
        Q.reset();
        Q.ins(s);
        sp[s] = 0; prev[s] = -1;
        while (Q.Size) {
            u = Q.pop();
            for (Edge *k = V[u]; k; k = k->next) {
                v = k->t;
                if (k->c > 0 && sp[u] + k->v < sp[v]) {
                    sp[v] = sp[u] + k->v;
                    prev[v] = u;
                    path[v] = k;
                    if (!Q.inq[v]) Q.ins(v);
                }
            }
        }
        return sp[t] != INF;
    }

    FlowCost augment(int t) {
        int i;
        int64_t low = INF, cost = 0;
        Edge *e;
        for (i = t; prev[i] != -1; i = prev[i]) {
            e = path[i];
            if (e->c < low) low = e->c;
        }
        for (i = t; prev[i] != -1; i = prev[i]) {
            e = path[i];
            e->c -= low; e->op->c += low;
            cost += e->v * low;
        }
        return FlowCost{low, cost};
    }
};

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

class EulerSieve {
private:
public:
    vector<bool> isPrime;
    vector<int> primes, mu, phi, sigma;

    EulerSieve(int N) {
        assert(N > 1);

        isPrime.resize(N+1, true);
        mu.resize(N+1);
        phi.resize(N+1);
        sigma.resize(N+1);

        // local variable to calculate sigma (divisor function)
        // i = pj^k * ..., and pi(i) = (1 + pj + pj^2 + ...)
        vector<int> pi(N+1);

        isPrime[0] = isPrime[1] = false;
        mu[1] = 1;
        phi[1] = 1;
        sigma[1] = 1;
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) {
                primes.push_back(i);
                mu[i] = -1;
                phi[i] = i - 1;
                sigma[i] = pi[i] = i + 1;
            }

            for (int j = 0; j < (int)primes.size(); j++) {
                int64_t t = (int64_t)i * primes[j];
                if ( t > N) break;
                isPrime[t] = false;
                if (i % primes[j] == 0) {
                    mu[t] = 0;
                    phi[t] = phi[i] * primes[j];
                    pi[t] = pi[i] * primes[j] + 1;
                    sigma[t] = sigma[i]/pi[i] * pi[t];
                    break;
                } else {
                    mu[t] = -mu[i];
                    phi[t] = phi[i] * (primes[j] - 1);
                    pi[t] = primes[j] + 1;
                    sigma[t] = sigma[primes[j]] * sigma[i];
                }
            }
        }
    }
};

const int MAXN = 210;
int N;

struct Node {
    int a, b, c;
    bool operator < (const Node &other) const {
        if (a != other.a) return a < other.a;
        if (b != other.b) return b < other.b;
        return c < other.c;
    }
} nodes[MAXN];

int C[MAXN];
bool vis[MAXN];

bool check(int a, int b, const EulerSieve &sieve) {
    if (a % b != 0) return false;
    int x = a / b;
    if (x == 1) return false;
    for (int i = 0; i < (int)sieve.primes.size(); i++) {
        int p = sieve.primes[i];
        if (1LL*p*p > x) break;
        if (x % p == 0) return false;
    }
    return true;
}

Graph build(const EulerSieve &sieve) {
    Graph g(N, N*(N-1));
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (check(nodes[i].a, nodes[j].a, sieve)) {
                g.addEdge(i, j);
                g.addEdge(j, i);
            }
        }
    }
    return g;
}

void dfs(const Graph &g, int u, int c) {
    vis[u] = true;
    C[u] = c;

    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (!vis[v]) {
            assert(C[v] == -1);
            dfs(g, v, 1^c);
        } else {
            assert(C[v] == (1^c));
        }
    }
}


void color(const Graph &g) {
    memset(C, -1, sizeof(C));
    for (int i = 0; i < N; i++) {
        if (!vis[i]) dfs(g, i, 0);
    }
}

int max_cap() {
    int m[2] = {0, 0};
    for (int i = 0; i < N; i++) {
        int c = C[i];
        m[c] += nodes[i].b;
    }
    return min(m[0], m[1]);
}

bool feasible(int cap, const Graph &g) {
    const int src = N;
    const int dst1 = N+1, dst2 = N+2;
    MincostMaxflow mcf(N+3, N*(N-1)/2+N+1);
    for (int i = 0; i < N; i++) {
        if (C[i] == 0) {
            mcf.addEdge(src, i, 0, nodes[i].b);
            for (int eidx = g.head[i]; ~eidx; eidx = g.E[eidx].next) {
                int j = g.E[eidx].to;
                mcf.addEdge(i, j, -1LL*nodes[i].c*nodes[j].c,
                            MincostMaxflow::INF);
            }
        } else {
            mcf.addEdge(i, dst1, 0, nodes[i].b);
        }
    }
    mcf.addEdge(dst1, dst2, 0, cap);

    auto flow = mcf.mincostFlow(src, dst2);
    return flow.first == cap && flow.second <= 0;
}


int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &nodes[i].a);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &nodes[i].b);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &nodes[i].c);
    }

    sort(nodes, nodes+N);

    EulerSieve sieve(32000);

    Graph g = build(sieve);
    color(g);

    int maxc = max_cap();

    int lo = 0, hi = maxc+1;
    while (lo < hi-1) {
        int mid = (lo + hi) / 2;
        if (feasible(mid, g)) lo = mid;
        else hi = mid;
    }
    printf("%d\n", lo);

    return 0;
}
