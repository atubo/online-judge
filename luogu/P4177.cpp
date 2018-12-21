// https://www.luogu.org/problemnew/show/P4177
// [CEOI2008]order

#include <bits/stdc++.h>
using namespace std;

class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
    struct Edge {
        int to, next, cap;
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

    void addEdge(int x, int y, int w, int rw = 0) {
        E[e] = {y, head[x], w};
        head[x] = e++;
        E[e] = {x, head[y], rw};
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

    int dfs(int x, int low, int t) {
        if (x == t || !low) return low;
        int ret = 0;
        for (int &i = curr[x]; i != -1; i = E[i].next) {
            int v = E[i].to;
            if (d[v] == d[x] - 1 && E[i].cap) {
                int k = dfs(v, min(low-ret, E[i].cap), t);
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

const int MAXN = 1210;
int N, M;
int PAY[MAXN], BUY[MAXN];

struct Procedure {
    int machine, loan;
};

int main() {
    scanf("%d%d", &N, &M);
    vector<vector<Procedure>> orders(N);
    int tot = 0;
    int totrev = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &PAY[i]);
        totrev += PAY[i];
        int n;
        scanf("%d", &n);
        tot += n;
        for (int j = 0; j < n; j++) {
            int m, f;
            scanf("%d%d", &m, &f);
            m--;
            orders[i].push_back({m, f});
        }
    }
    for (int i = 0; i < M; i++) {
        scanf("%d", &BUY[i]);
    }

    Dinic dinic(N+M+2, N+M+tot);
    const int src = N + M;
    const int dst = src + 1;
    for (int i = 0; i < N; i++) {
        dinic.addEdge(src, i, PAY[i]);
        for (const auto &p: orders[i]) {
            dinic.addEdge(i, N+p.machine, p.loan);
        }
    }
    for (int i = 0; i < M; i++) {
        dinic.addEdge(N+i, dst, BUY[i]);
    }
    printf("%d\n", totrev - dinic.dinic(src, dst));
    return 0;
}
