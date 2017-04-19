// http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemId=1788
// Panic Room

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30;
bool intruder[MAXN], toSecure[MAXN], breached[MAXN];
int M, N;

class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
private:
    static const int MAXN = 30;
    static const int MAXM = 5 * MAXN * MAXN;
    int head[MAXN], curr[MAXN];
    struct Edge {
        int to, next, cap;
    } E[MAXM];
    int e;

public:
    Dinic() {
        reset();
    }

    void reset() {
        e = 0;
        memset(head, -1, sizeof(head));
    }

    void addEdge(int x, int y, int w, int rw = 0) {
        E[e] = {y, head[x], w};
        head[x] = e++;
        E[e] = {x, head[y], rw};
        head[y] = e++;
    }

    void markToSecure() {
        vector<bool> vis(MAXN);
        queue<int> q;
        q.push(N);
        vis[N] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            toSecure[u] = true;
            for (int i = head[u]; i != -1; i = E[i].next) {
                int v = E[i].to;
                if (!vis[v] && E[i^1].cap) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }

    void markBreached() {
        vector<bool> vis(MAXN);
        queue<int> q;
        for (int i = 0; i < M; i++) {
            if (intruder[i]) {
                q.push(i);
                vis[i] = true;
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            breached[u] = true;
            for (int i = head[u]; i != -1; i = E[i].next) {
                int v = E[i].to;
                if (!vis[v] && E[i].cap) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }


private:
    int d[MAXN];

    bool bfs(int s, int t) {
        memset(d, -1, sizeof(d));
        queue<int> q;
        q.push(t);
        d[t] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = head[u]; i != -1; i = E[i].next) {
                int v = E[i].to;
                if (d[v] == -1 && E[i^1].cap) {
                    d[v] = d[u] + 1;
                    q.push(v);
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
            for (int i = 0; i < MAXN; i++) {
                curr[i] = head[i];
            }
            int k = dfs(s, inf, t);
            if (k > 0) ans += k;
        }
        return ans;
    }
};

int main() {
    int tests;
    scanf("%d", &tests);
    Dinic dinic;
    char str[10];
    while (tests--) {
        scanf("%d%d", &M, &N);
        dinic.reset();
        memset(intruder, 0, sizeof(intruder));
        memset(toSecure, 0, sizeof(toSecure));
        memset(breached, 0, sizeof(breached));
        for (int i = 0; i < M; i++) {
            int c;
            scanf("%s%d", str, &c);
            if (str[0] == 'I') intruder[i] = true;
            for (int j = 0; j < c; j++) {
                int v;
                scanf("%d", &v);
                dinic.addEdge(i, v, 1);
            }
        }

        bool prBreached = false;
        dinic.markToSecure();
        dinic.markBreached();
        for (int i = 0; i < M; i++) {
            if (toSecure[i] && breached[i]) {
                prBreached = true;
                break;
            }
        }
        if (prBreached) {
            printf("PANIC ROOM BREACH\n");
            continue;
        }

        const int S = M, T = M+1;
        for (int i = 0; i < M; i++) {
            if (toSecure[i]) {
                dinic.addEdge(S, i, Dinic::inf);
            }
            if (breached[i]) {
                dinic.addEdge(i, T, Dinic::inf);
            }
        }
        printf("%d\n", dinic.dinic(S, T));
    }
    return 0;
}
