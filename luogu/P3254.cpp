// https://www.luogu.org/problem/show?pid=3254
// 圆桌问题

#include <bits/stdc++.h>
using namespace std;

class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
public:
    static const int MAXM = 90000;
    const int N;
    int *head, *curr;
    struct Edge {
        int to, next, cap;
    };
    Edge *E;
    int e;

public:
    Dinic(int N_): N(N_) {
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
            if (d[v] == d[x] - 1) {
                int k = dfs(v, min(low-ret, E[i].cap), t);
                if (k > 0) {
                    E[i].cap -= k;
                    E[i^1].cap += k;
                    ret += k;
                }
            }
        }
        return ret;
    }

public:
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
};

int M, N;

int main() {
    scanf("%d%d", &M, &N);
    const int S = 0, T = M+N+1;
    Dinic dinic(T+1);
    int total = 0;
    for (int i = 1; i <= M; i++) {
        int r;
        scanf("%d", &r);
        dinic.addEdge(S, i, r);
        total += r;
    }
    for (int i = 1; i <= N; i++) {
        int c;
        scanf("%d", &c);
        dinic.addEdge(M+i, T, c);
    }
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            dinic.addEdge(i, M+j, 1);
        }
    }
    int maxflow = dinic.dinic(S, T);
    if (maxflow == total) {
        printf("1\n");
        for (int i = 1; i <= M; i++) {
            for (int eidx = dinic.head[i]; ~eidx; eidx = dinic.E[eidx].next) {
                int v = dinic.E[eidx].to;
                int c = dinic.E[eidx].cap;
                if (c == 0) printf("%d ", v - M);
            }
            printf("\n");
        }
    } else {
        printf("0\n");
    }

    return 0;
}
