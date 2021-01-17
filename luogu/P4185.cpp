// https://www.luogu.com.cn/problem/P4185
// [USACO18JAN]MooTube G

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
 const int N;
 vector<int> rank;
 vector<int> parent;
 vector<int> size;

 void makeSet(int k) {
   assert(0 <= k && k < N);

   parent[k] = k;
   rank[k] = 0;
   size[k] = 1;
 }

 int link(int u, int v) {
   if (u == v) return u;
   if (rank[u] > rank[v]) {
     parent[v] = u;
     size[u] += size[v];
     return u;
   } else {
     parent[u] = v;
     size[v] += size[u];
     if (rank[u] == rank[v]) {
       rank[v]++;
     }
     return v;
   }
 }

public:
 UnionFind(int n): N(n) {
   rank.resize(N);
   parent.resize(N);
   size.resize(N);

   reset();
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

 int count(int u) {
   return size[find(u)];
 }
};

struct Event {
  Event(int op1, int p1, int q1, int r1, int id1)
      : op(op1), p(p1), q(q1), r(r1), id(id1) {}
  int op, p, q, r, id;
  bool operator > (const Event& other) const {
    if (r != other.r) return r > other.r;
    return op > other.op;
  }
};

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  vector<Event> events;
  for (int i = 0; i < n-1; i++) {
    int u, v, r;
    scanf("%d%d%d", &u, &v, &r);
    u--; v--;
    events.emplace_back(1, u, v, r, -1);
  }
  for (int i = 0; i < q; i++) {
    int k, v;
    scanf("%d%d", &k, &v);
    v--;
    events.emplace_back(0, v, v, k, i);
  }
  sort(events.begin(), events.end(), greater<Event>());
  vector<int> ans(q);
  UnionFind uf(n);
  for (const auto& e : events) {
    if (e.op == 1) {
      uf.join(e.p, e.q);
    } else {
      ans[e.id] = uf.count(e.p) - 1;
    }
  }
  for (int i = 0; i < q; i++) {
    printf("%d\n", ans[i]);
  }

  return 0;
}
