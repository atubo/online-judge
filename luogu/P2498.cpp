// https://www.luogu.org/problem/P2498
// [SDOI2012]拯救小云公主

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
    const int N;
    int* rank;
    int* parent;

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parent[k] = k;
        rank[k] = 0;
    }

    int link(int u, int v) {
        if (u == v) return u;
        if (rank[u] > rank[v]) {
            parent[v] = u;
            return u;
        } else {
            parent[u] = v;
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
            return v;
        }
    }

    void alloc() {
      rank = new int[N]{};
      parent = new int[N]{};
    }

    void dealloc() {
      delete[] rank;
      delete[] parent;
    }
public:
    UnionFind(int n): N(n) {
      alloc();
      reset();
    }

    ~UnionFind() {
      dealloc();
    }

    void reset() {
        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    int find(int k) {
        if (parent[k] == k) return k;
        int root = find(parent[k]);
        return parent[k] = root;
    }

    int join(int u, int v) {
        return link(find(u), find(v));
    }
};

const int MAXN = 3010;
const double EPS = 1e-3;
int N;
int X, Y;
struct Point {
  int x, y;
} P[MAXN];

bool feasible(double d, UnionFind& uf) {
  uf.reset();
  double th = 4*d*d;
  for (int i = 0; i < N; i++) {
    if (P[i].y < d || X-P[i].x < d) {
      uf.join(i, N);
    }
    if (P[i].x < d || Y-P[i].y < d) {
      uf.join(i, N+1);
    }
    for (int j = i+1; j < N; j++) {
      double dx = abs(P[i].x - P[j].x);
      double dy = abs(P[i].y - P[j].y);
      if (dx*dx + dy*dy < th) {
        uf.join(i, j);
      }
    }
  }
  return uf.find(N) != uf.find(N+1);
}

int main() {
  scanf("%d%d%d", &N, &X, &Y);
  X--; Y--;
  double dmax = INT_MAX;
  for (int i = 0; i < N; i++) {
    scanf("%d%d", &P[i].x, &P[i].y);
    P[i].x--; P[i].y--;
    dmax = min(
        dmax,
        double(max(min(P[i].x, Y-P[i].y), min(P[i].y, X-P[i].x))));
  }
  if (dmax < 0.01) {
    printf("0.00\n");
    return 0;
  }
  UnionFind uf(N+2);
  double lo = 0, hi = dmax;
  while (hi-lo > EPS) {
    double mid = (lo + hi) / 2;
    if (feasible(mid, uf)) lo = mid;
    else hi = mid;
  }
  printf("%.2f\n", lo);

  return 0;
}
