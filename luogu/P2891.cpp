// https://www.luogu.org/problemnew/show/P2891
// [USACO07OPEN]吃饭Dining

#include <bits/stdc++.h>
using namespace std;

class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
private:
    static const int MAXM = 42000;
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
int N, F, D;
int S, T;

int foodid(int i) {return i;}
int cowin(int i) {return F + 2*i - 1;}
int cowout(int i) {return F + 2*i;}
int drinkid(int i) {return F + 2*N + i;}

int main() {
    scanf("%d%d%d", &N, &F, &D);
    S = 0, T = F + 2*N + D + 1;
    Dinic dinic(T+1);

    for (int i = 1; i <= F; i++) {
        dinic.addEdge(S, foodid(i), 1);
    }
    for (int i = 1; i <= D; i++) {
        dinic.addEdge(drinkid(i), T, 1);
    }

    for (int i = 1; i <= N; i++) {
        dinic.addEdge(cowin(i), cowout(i), 1);
        int fi, di;
        scanf("%d%d", &fi, &di);
        for (int j = 0; j < fi; j++) {
            int f;
            scanf("%d", &f);
            dinic.addEdge(foodid(f), cowin(i), 1);
        }
        for (int j = 0; j < di; j++) {
            int d;
            scanf("%d", &d);
            dinic.addEdge(cowout(i), drinkid(d), 1);
        }
    }

    printf("%d\n", dinic.dinic(S, T));

    return 0;
}
