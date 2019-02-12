// https://www.luogu.org/problemnew/show/P3324
// [SDOI2015]星际战争

#include <bits/stdc++.h>
using namespace std;

const double INF = 1e9;
const double EPS = 1e-6;

class Dinic {
public:
    struct Edge {
        int to, next;
        double cap;
    };

    const int N, MAXM;
    int *head;
    Edge *E;
    int e;
private:
    int *curr;

public:
    Dinic(int N_, int M_): N(N_), MAXM(2*M_) {
        alloc();
        reset();
    }

    ~Dinic() {
        dealloc();
    }

    void reset() {
        e = 0;
        memset(head, -1, N * sizeof(int));
    }

    void addEdge(int x, int y, double w, double rw = 0) {
        E[e] = {y, head[x], w};
        head[x] = e++;
        E[e] = {x, head[y], rw};
        head[y] = e++;
    }

    double dinic(int s, int t) {
        double ans = 0;
        while (bfs(s, t)) {
            for (int i = 0; i < N; i++) {
                curr[i] = head[i];
            }
            double k = dfs(s, INF, t);
            if (k > 0) ans += k;
        }
        return ans;
    }

private:
    void alloc() {
        head = new int[N]{};
        curr = new int[N]{};
        E    = new Edge[MAXM]{};
        d    = new int[N]{};
        q    = new int[N]{};
    }

    void dealloc() {
        delete[] head;
        delete[] curr;
        delete[] E;
        delete[] d;
        delete[] q;
    }

    int *d;
    int *q;

    bool bfs(int s, int t) {
        memset(d, -1, N * sizeof(int));
        int front = 0, back = 0;
        q[back++] = t;

        d[t] = 0;
        while (front != back) {
            int u = q[front];
            front++;
            for (int i = head[u]; i != -1; i = E[i].next) {
                int v = E[i].to;
                if (d[v] == -1 && E[i^1].cap) {
                    d[v] = d[u] + 1;
                    q[back++] = v;
                    if (v == s) return true;
                }
            }
        }
        return false;
    }

    double dfs(int x, double low, int t) {
        if (x == t || low <= EPS) return low;
        double ret = 0;
        for (int &i = curr[x]; i != -1; i = E[i].next) {
            int v = E[i].to;
            if (d[v] == d[x] - 1 && E[i].cap > EPS) {
                double k = dfs(v, min(low-ret, E[i].cap), t);
                if (k > 0) {
                    E[i].cap -= k;
                    E[i^1].cap += k;
                    ret += k;
                }
            }
            // without the following line curr[x] might change
            // prematurely, causing runtime increase
            if (low == ret) break;
        }
        return ret;
    }
};

const int MAXN = 52;
int N, M;
int A[MAXN], B[MAXN];
int C[MAXN][MAXN];
int ne;

bool check(double t) {
    Dinic dinic(N+M+2, N+M+ne);
    const int src = N+M, dst = N+M+1;
    for (int i = 0; i < M; i++) {
        dinic.addEdge(src, i, t*B[i]);
        for (int j = 0; j < N; j++) {
            if (C[i][j]) dinic.addEdge(i, M+j, INF);
        }
    }
    double tot = 0;
    for (int i = 0; i < N; i++) {
        dinic.addEdge(M+i, dst, A[i]);
        tot += A[i];
    }

    double flow = dinic.dinic(src, dst);
    return (flow >= tot - EPS);
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < M; i++) {
        scanf("%d", &B[i]);
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &C[i][j]);
            ne += C[i][j];
        }
    }

    double lo = 0, hi = 1e7;
    while (lo < hi - 1e-5) {
        double mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid;
    }
    printf("%.6f\n", hi);

    return 0;
}
