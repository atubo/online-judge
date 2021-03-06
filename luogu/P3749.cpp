// https://www.luogu.org/problemnew/show/P3749
// [六省联考2017]寿司餐厅

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

const int MAXN = 105;
int N, M;
int A[MAXN], B[MAXN];
int D[MAXN][MAXN];
int ID[MAXN][MAXN];

int encode(int i, int j) {
    return i*N + j;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        B[i] = A[i];
    }
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            scanf("%d", &D[i][j]);
        }
    }

    sort(B, B+N);
    const int C = unique(B, B+N) - B;
    for (int i = 0; i < N; i++) {
        A[i] = lower_bound(B, B+C, A[i]) - B;
    }

    const int src = N*(N+1)/2+N+C;
    const int dst = src + 1;
    Dinic dinic(dst+1, dst*3);

    for (int i = 0; i < C; i++) {
        dinic.addEdge(N*(N+1)/2 + N + i, dst, M*B[i]*B[i]);
    }
    for (int i = 0; i < N; i++) {
        dinic.addEdge(N*(N+1)/2 + i, dst, B[A[i]]);
    }

    for (int i = 0, curr = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            ID[i][j] = curr++;
        }
    }

    int tot = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            int id = ID[i][j];
            if (D[i][j] > 0) {
                dinic.addEdge(src, id, D[i][j]);
                tot += D[i][j];
            } else {
                dinic.addEdge(id, dst, -D[i][j]);
            }
            if (i < j) {
                dinic.addEdge(id, ID[i+1][j], Dinic::inf);
                dinic.addEdge(id, ID[i][j-1], Dinic::inf);
            } else {
                dinic.addEdge(id, N*(N+1)/2+i, Dinic::inf);
                dinic.addEdge(id, N*(N+1)/2+N+A[i], Dinic::inf);
            }
        }
    }

    int flow = dinic.dinic(src, dst);
    printf("%d\n", tot-flow);

    return 0;
}
