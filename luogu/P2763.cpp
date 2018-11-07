// https://www.luogu.org/problemnew/show/P2763
// 试题库问题

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

int K, N, M;

void dfs(const Dinic &dinic, vector<vector<int>> &sol) {
    for (int eidx = dinic.head[0]; ~eidx; eidx = dinic.E[eidx].next) {
        if (dinic.E[eidx].cap == 0) {
            int u = dinic.E[eidx].to;
            for (int e = dinic.head[u]; ~e; e = dinic.E[e].next) {
                if (dinic.E[e].cap == 0) {
                    int v = dinic.E[e].to;
                    sol[v-N-1].push_back(u-1);
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &K, &N);
    vector<int> req(K);
    vector<vector<int>> cat(N);
    for (int i = 0; i < K; i++) {
        scanf("%d", &req[i]);
        M += req[i];
    }
    int totp = 0;
    for (int i = 0; i < N; i++) {
        int p;
        scanf("%d", &p);
        cat[i].resize(p);
        for (int j = 0; j < p; j++) {
            scanf("%d", &cat[i][j]);
            cat[i][j]--;
        }
        sort(cat[i].begin(), cat[i].end());
        cat[i].erase(unique(cat[i].begin(), cat[i].end()), cat[i].end());
        p = cat[i].size();
        totp += p;
    }

    Dinic dinic(N+K+2, N+K+totp);
    const int S = 0, T = N+K+1;
    for (int i = N-1; i >= 0; i--) {
        dinic.addEdge(S, i+1, 1);
    }
    for (int i = 0; i < K; i++) {
        dinic.addEdge(N+1+i, T, req[i]);
    }
    for (int i = N-1; i >= 0; i--) {
        for (int j: cat[i]) {
            dinic.addEdge(i+1, N+1+j, 1);
        }
    }

    int ans = dinic.dinic(S, T);
    if (ans < M) {
        printf("No Solution!\n");
        return 0;
    }

    vector<vector<int>> sol(K);
    dfs(dinic, sol);

    for (int i = 0; i < K; i++) {
        printf("%d: ", i+1);
        sort(sol[i].begin(), sol[i].end());
        for (int x: sol[i]) {
            printf("%d ", x+1);
        }
        printf("\n");
    }

    return 0;
}
