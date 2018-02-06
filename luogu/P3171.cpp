// https://www.luogu.org/problemnew/show/P3171
// [CQOI2015]网络吞吐量

#include <bits/stdc++.h>
using namespace std;

class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
private:
    static const int MAXM = 202000;
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
        head = new int[N];
        curr = new int[N];
        E    = new Edge[MAXM];
        d    = new int[N];
        q    = new int[N];
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

int innode(int i) {return i*2;}
int outnode(int i) {return i*2 + 1;}

int N, M;
int main() {
    scanf("%d%d", &N, &M);
    Dinic dinic(2*N);
    for (int i = 0; i < M; i++) {
        int a, b, d;
        scanf("%d%d%d", &a, &b, &d);
        a--; b--;
        dinic.addEdge(outnode(a), innode(b), Dinic::inf);
        dinic.addEdge(outnode(b), innode(a), Dinic::inf);
    }
    for (int i = 0; i < N; i++) {
        int c;
        scanf("%d", &c);
        if (i == 0 || i == N-1) {
            dinic.addEdge(innode(i), outnode(i), Dinic::inf);
        } else {
            dinic.addEdge(innode(i), outnode(i), c);
        }
    }

    printf("%d\n", dinic.dinic(innode(0), outnode(N-1)));

    return 0;
}
