// https://www.luogu.org/problemnew/show/P2762
// 太空飞行计划问题

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

const int MAXN = 110;
int M, N;
bool vis[MAXN];

void dfs(int u, const Dinic &dinic) {
    vis[u] = true;
    for (int eidx = dinic.head[u]; ~eidx; eidx = dinic.E[eidx].next) {
        int v = dinic.E[eidx].to;
        if (!vis[v] && dinic.E[eidx].cap) {
            dfs(v, dinic);
        }
    }
}

int main() {
    scanf("%d%d", &M, &N);
    Dinic dinic(M+N+2, M+N+M*N);
    const int src = 0, dst =M+N+1;

    int tot = 0;
    char tools[10000];
    for (int i = 1; i <= M; i++) {
        int pay;
        scanf("%d", &pay);
        tot += pay;
        dinic.addEdge(i+N, dst, pay);
        cin.getline(tools, 10000);
        int ulen = 0, tool;
        while (sscanf(tools+ulen, "%d", &tool) == 1) {
            dinic.addEdge(tool, i+N, Dinic::inf);
            if (tool == 0) ulen++;
            else {
                while (tool) {
                    tool /= 10;
                    ulen++;
                }
            }
            ulen++;
        }
    }

    for (int i = 1; i <= N; i++) {
        int c;
        scanf("%d", &c);
        dinic.addEdge(src, i, c);
    }

    int flow = dinic.dinic(src, dst);

    dfs(src, dinic);

    for (int i = 1; i <= M; i++) {
        if (!vis[i+N]) printf("%d ", i);
    }
    printf("\n");
    for (int i = 1; i <= N; i++) {
        if (!vis[i]) printf("%d ", i);
    }
    printf("\n");

    printf("%d", tot-flow);

    return 0;
}
