// https://www.luogu.org/problemnew/show/P4174
// [NOI2006]最大获利

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

const int MAXN = 5010;
const int MAXM = 50010;
int N, M;
int P[MAXN];
int A[MAXM], B[MAXM], C[MAXM];
int tot[MAXN];
int top[MAXN], bot[MAXN];

struct Edge {
    int u, w;
};

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &P[i]);
    }
    vector<vector<Edge>> adj(N+1);
    int totp = 0;
    for (int i = 1; i <= M; i++) {
        scanf("%d%d%d", &A[i], &B[i], &C[i]);
        tot[A[i]] += C[i];
        tot[B[i]] += C[i];
        adj[A[i]].push_back({B[i], C[i]});
        adj[B[i]].push_back({A[i], C[i]});
        totp += C[i];
    }

    for (int i = 1; i <= N; i++) {
        top[i] = 2*i - 1;
        bot[i] = top[i] + 1;
    }
    Dinic dinic(2*N+2, 2*M+3*N);
    const int src = 0, dst = 2*N+1;
    for (int i = 1; i <= N; i++) {
        dinic.addEdge(src, top[i], tot[i]);
        dinic.addEdge(top[i], bot[i], Dinic::inf);
        dinic.addEdge(bot[i], dst, 2*P[i]);
        for (const auto &e: adj[i]) {
            dinic.addEdge(top[i], bot[e.u], e.w);
        }
    }

    int flow = dinic.dinic(src, dst);
    int ans = (2*totp - flow) / 2;
    printf("%d", ans);

    return 0;
}
