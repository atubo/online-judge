// https://www.luogu.com.cn/problem/P3106
// [USACO14OPEN]Dueling GPSs S

#include <bits/stdc++.h>
using namespace std;

class FastDijkstra {
 public:
  static const int64_t INF;

  typedef pair<int64_t,int> PII;  // pair = (dist, vertex)

  FastDijkstra(int N_): N(N_), edges(N), dist(N, INF), dad(N, -1) {}

  void addEdge(int u, int v, int64_t wt) {
    edges[u].push_back(make_pair(wt, v));
  }

  const vector<int64_t>& getDist() const {
    return dist;
  }

  const vector<int>& getDad() const {
    return dad;
  }

  void solve(int s) {
    // use priority queue in which top element has the "smallest" priority
    priority_queue<PII, vector<PII>, greater<PII> > Q;
    Q.push (make_pair (0, s));
    dist[s] = 0;
    while (!Q.empty()){
      PII p = Q.top();
      // break here if we want to stop when we find a target node
      Q.pop();

      int here = p.second;
      for (vector<PII>::const_iterator it=edges[here].begin();
          it!=edges[here].end(); it++){
        if (dist[here] + it->first < dist[it->second]){
          dist[it->second] = dist[here] + it->first;
          dad[it->second] = here;
          Q.push (make_pair (dist[it->second], it->second));
        }
      }
    }
  }

  void reset() {
    dist.assign(N, INF);
    dad.assign(N, -1);
  }

 private:
  const int N;
  vector<vector<PII>> edges;
  vector<int64_t> dist;
  vector<int> dad;
};

const int64_t FastDijkstra::INF = 0x7FFFFFFFFFFFFFFF;

const int MAXM = 50010;
struct Road {
  int a, b, p, q;
} R[MAXM];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  FastDijkstra dij1(n), dij2(n);
  vector<pair<int, int>> edges;
  for (int i = 0; i < m; i++) {
    int a, b, p, q;
    scanf("%d%d%d%d", &a, &b, &p, &q);
    a--; b--;
    dij1.addEdge(b, a, p);
    dij2.addEdge(b, a, q);
    R[i] = {a, b, p, q};
  }
  dij1.solve(n-1);
  dij2.solve(n-1);

  auto dist1 = dij1.getDist();
  auto dist2 = dij2.getDist();
  FastDijkstra dij3(n);
  for (int i = 0; i < m; i++) {
    int w = 0;
    int a = R[i].a;
    int b = R[i].b;
    int p = R[i].p;
    int q = R[i].q;
    if (dist1[a] != dist1[b] + p) w++;
    if (dist2[a] != dist2[b] + q) w++;
    dij3.addEdge(a, b, w);
  }
  dij3.solve(0);
  printf("%ld\n", dij3.getDist()[n-1]);

  return 0;
}
