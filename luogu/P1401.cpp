// https://www.luogu.org/problemnew/show/P1401
// 城市

#include <bits/stdc++.h>
using namespace std;

int guess;

class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
    struct Edge {
        int to, next, cap, wt;
    };

    const int N, MAXM;
    int *head;
    Edge *E;
    int *orig_cap;
    int e;
private:
    int *curr;

public:
    Dinic(int N_, int M_): N(N_), MAXM(2*M_) {
        alloc();
        init();
    }

    ~Dinic() {
        dealloc();
    }

    void init() {
        e = 0;
        memset(head, -1, N * sizeof(int));
    }

    void reset() {
        for (int i = 0; i < MAXM; i++) {
            E[i].cap = orig_cap[i];
        }
    }

    void addEdge(int x, int y, int w, int wt) {
        orig_cap[e] = w;
        E[e] = {y, head[x], w, wt};
        head[x] = e++;
        orig_cap[e] = w;
        E[e] = {x, head[y], w, wt};
        head[y] = e++;
    }

    int dinic(int s, int t) {
        int ans = 0;
        while (bfs(s, t)) {
            for (int i = 0; i < N; i++) {
                curr[i] = head[i];
            }
            int k = dfs(s, inf, t);
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
        orig_cap = new int[MAXM]{};
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
                if (d[v] == -1 && E[i^1].cap && E[i^1].wt <= guess) {
                    d[v] = d[u] + 1;
                    q[back++] = v;
                    if (v == s) return true;
                }
            }
        }
        return false;
    }

    int dfs(int x, int low, int t) {
        if (x == t || !low) return low;
        int ret = 0;
        for (int &i = curr[x]; i != -1; i = E[i].next) {
            int v = E[i].to;
            if (d[v] == d[x] - 1 && E[i].cap && E[i].wt <= guess) {
                int k = dfs(v, min(low-ret, E[i].cap), t);
                if (k > 0) {
                    E[i].cap -= k;
                    E[i^1].cap += k;
                    ret += k;
                }
            }
            if (low == ret) break;
        }
        return ret;
    }
};

int N, M, target;

int main() {
    scanf("%d%d%d", &N, &M, &target);
    Dinic dinic(N+2, M+2);
    int maxl = 0;
    for (int i = 0; i < M; i++) {
        int a, b, l;
        scanf("%d%d%d", &a, &b, &l);
        dinic.addEdge(a, b, 1, l);
        maxl = max(maxl, l);
    }
    const int S = 0, T = N+1;
    dinic.addEdge(S, 1, target, 0);
    dinic.addEdge(N, T, target, 0);

    guess = maxl;
    if (dinic.dinic(S, T) < target) {
        printf("%d", 0);
        return 0;
    }

    int lo = -1, hi = maxl;
    while (lo < hi - 1) {
        guess = (lo + hi) / 2;
        dinic.reset();
        int flow = dinic.dinic(S, T);
        if (flow >= target) hi = guess;
        else lo = guess;
    }
    printf("%d", hi);

    return 0;
}
