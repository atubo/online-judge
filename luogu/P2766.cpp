// https://www.luogu.org/problemnew/show/P2766
// 最长不下降子序列问题

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

const int MAXN = 510;
int N;
int A[MAXN];
int dp[MAXN];
int top[2*MAXN], bot[2*MAXN];

int solve1() {
    dp[0] = 1;
    int ans = 1;
    for (int i = 1; i < N; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (A[j] <= A[i]) {
                dp[i] = max(dp[i], dp[j]+1);
            }
        }
        ans = max(ans, dp[i]);
    }
    return ans;
}

int solve2(Dinic &dinic, int l) {
    const int src = 2*N, dst = src+1;
    for (int i = 0; i < N; i++) {
        dinic.addEdge(top[i], bot[i], 1);
        if (dp[i] == 1) {
            dinic.addEdge(src, top[i], 1);
        }
        if (dp[i] == l) {
            dinic.addEdge(bot[i], dst, 1);
        }
        for (int j = i+1; j < N; j++) {
            if (dp[j] == dp[i] + 1 && A[j] >= A[i]) {
                dinic.addEdge(bot[i], top[j], 1);
            }
        }
    }
    return dinic.dinic(src, dst);
}

int solve3(Dinic &dinic, int l) {
    if (l == 1) return N;
    dinic.reset();
    const int src = 2*N, dst = src+1;
    for (int i = 0; i < N; i++) {
        int cap = (i == 0 || i == N-1) ? Dinic::inf : 1;
        dinic.addEdge(top[i], bot[i], cap);
        if (dp[i] == 1) {
            dinic.addEdge(src, top[i], cap);
        }
        if (dp[i] == l) {
            dinic.addEdge(bot[i], dst, cap);
        }
        for (int j = i+1; j < N; j++) {
            if (dp[j] == dp[i] + 1 && A[j] >= A[i]) {
                dinic.addEdge(bot[i], top[j], 1);
            }
        }
    }
    return dinic.dinic(src, dst);
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        top[i] = 2*i;
        bot[i] = top[i] + 1;
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    int ans = solve1();
    printf("%d\n", ans);
    Dinic dinic(2*N+2, 3*N+N*(N-1)/2);
    printf("%d\n", solve2(dinic, ans));
    printf("%d\n", solve3(dinic, ans));
    return 0;
}
