// https://www.luogu.com.cn/problem/P4518
// [JSOI2018]绝地反击

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

const double PI = acos(-1);
const double EPS = 0.00000005;
const int MAXN = 310;
struct Point {
  double x, y;
} P[MAXN];
int N;
int R;

double solve(Dinic& dinic, double t) {
  double lo = 0.0, hi = 300;
  const int S = 2*N, T = 2*N+1;
  while (lo < hi - 0.000001) {
    double mid = (lo + hi) / 2;
    double ms = mid * mid;
    dinic.reset();
    for (int i = 0; i < N; i++) {
      dinic.addEdge(S, i, 1);
      dinic.addEdge(i+N, T, 1);
    }

    for (int i = 0; i < N; i++) {
      double ti = t + (2*PI/N) * i;
      double px = R * sin(ti), py = R * cos(ti);
      for (int j = 0; j < N; j++) {
        double dx = P[j].x - px;
        double dy = P[j].y - py;
        if (dx * dx + dy * dy <= ms) {
          dinic.addEdge(i, j+N, 1);
        }
      }
    }
    int m = dinic.dinic(S, T);
    if (m == N) hi = mid;
    else lo = mid;
  }
  return hi;
}

int main() {
  scanf("%d%d", &N, &R);
  for (int i = 0; i < N; i++) {
    scanf("%lf%lf", &P[i].x, &P[i].y);
  }
  Dinic dinic(2*N+2, N*N+2*N);
  double t = 0.0, tf = solve(dinic, t), ans = tf;
  for (double d = PI/N; d >= EPS; d *= 0.5) {
    double newt = t + d, newtf = solve(dinic, newt);
    ans = min(ans, newtf);
    if (newtf < tf) {
      t = newt;
      tf = newtf;
    } else {
      newt = t - d;
      newtf = solve(dinic, newt);
      ans = min(ans, newtf);
      if (newtf <= tf) {
        t = newt;
        tf = newtf;
      }
    }
  }
  printf("%.9lf\n", ans);
  return 0;
}
