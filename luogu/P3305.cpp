// https://www.luogu.org/problemnew/show/P3305
// [SDOI2013]费用流

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

class Dinic {
public:
    static constexpr double inf = 1e9;
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
    double *save_;

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

    void save() {
        for (int i = 0; i < e; i++) {
            save_[i] = E[i].cap;
        }
    }

    void restore(double mx) {
        for (int i = 0; i < e; i++) {
            E[i].cap = min(save_[i], mx);
        }
    }

    double dinic(int s, int t) {
        double ans = 0;
        while (bfs(s, t)) {
            for (int i = 0; i < N; i++) {
                curr[i] = head[i];
            }
            double k = dfs(s, inf, t);
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
        save_ = new double[MAXM]{};
    }

    void dealloc() {
        delete[] head;
        delete[] curr;
        delete[] E;
        delete[] d;
        delete[] q;
        delete[] save_;
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
                if (d[v] == -1 && (E[i^1].cap > EPS)) {
                    d[v] = d[u] + 1;
                    q[back++] = v;
                    if (v == s) return true;
                }
            }
        }
        return false;
    }

    double dfs(int x, double low, int t) {
        if (x == t || low < EPS) return low;
        double ret = 0;
        for (int &i = curr[x]; i != -1; i = E[i].next) {
            int v = E[i].to;
            if (d[v] == d[x] - 1 && (E[i].cap > 0)) {
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

int N, M, P;

int main() {
    scanf("%d%d%d", &N, &M, &P);
    Dinic dinic(N, M);
    int maxcap = 0;
    for (int i = 0; i < M; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--; b--;
        dinic.addEdge(a, b, c);
        maxcap = max(maxcap, c);
    }
    dinic.save();
    double maxflow = dinic.dinic(0, N-1);

    double minmax = 0;
    if (maxflow > 0) {
        double lo = 0, hi = maxcap;
        while (lo < hi-EPS) {
            double mid = (lo + hi) / 2;
            dinic.restore(mid);
            if (dinic.dinic(0, N-1) < maxflow-EPS) lo = mid;
            else hi = mid;
        }
        minmax = hi;
    }
    printf("%d\n%.4f\n", int(maxflow+0.1), (float)(P*minmax));
    return 0;
}
