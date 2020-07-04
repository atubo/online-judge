// https://www.luogu.com.cn/problem/P2538
// [SCOI2008]城堡

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 52;
int N;
int M;
int K;

class FastDijkstra {
 public:
  static const int INF;

  typedef pair<int,int> PII;  // pair = (dist, vertex)

  FastDijkstra(int N_): N(N_), edges(N), dist(N, INF) {}

  void addEdge(int u, int v, int wt) {
    edges[u].push_back(make_pair(wt, v));
  }

  const vector<int>& getDist() const {
    return dist;
  }

  void solve(const vector<int>& perm) {
    // use priority queue in which top element has the "smallest" priority
    priority_queue<PII, vector<PII>, greater<PII> > Q;
    for (int i = 0; i < M + K; i++) {
      int p = perm[i];
      Q.push(make_pair(0, p));
      dist[p] = 0;
    }
    while (!Q.empty()){
      PII p = Q.top();
      Q.pop();

      int here = p.second;
      for (vector<PII>::const_iterator it=edges[here].begin();
          it!=edges[here].end(); it++){
        if (dist[here] + it->first < dist[it->second]){
          dist[it->second] = dist[here] + it->first;
          Q.push (make_pair (dist[it->second], it->second));
        }
      }
    }
  }

  void reset() {
    dist.assign(N, INF);
  }

 private:
  const int N;
  vector<vector<PII>> edges;
  vector<int> dist;
};

int calc(FastDijkstra& dij, const vector<int>& perm) {
  dij.reset();
  dij.solve(perm);
  const auto& dist = dij.getDist();
  int ans = 0;
  for (int i = 0; i < N; i++) {
    ans = max(ans, dist[i]);
  }
  return ans;
}

void sa(FastDijkstra& dij, vector<int>& perm, int& ans) {
  const double delta = 0.975;
  for (double t = 2000; t > 1e-14; t *= delta) {
    int x = rand() % K;
    int y = rand() % (N - M - K);
    swap(perm[M+x], perm[M+K+y]);
    int tmp = calc(dij, perm);
    int del = tmp - ans;
    if (del < 0) ans = tmp;
    else if (exp(-del/t) * RAND_MAX <= rand()) {
      swap(perm[M+x], perm[M+K+y]);
    }
  }
}

const int FastDijkstra::INF = 0x7FFFFFFF;

int main() {
  srand(time(0));
  srand(rand());
  srand(rand());
  scanf("%d%d%d", &N, &M, &K);
  FastDijkstra dij(N);
  vector<int> r(N), d(N);
  for (int i = 0; i < N; i++) {
    scanf("%d", &r[i]);
  }
  for (int i = 0; i < N; i++) {
    scanf("%d", &d[i]);
  }
  for (int i = 0; i < N; i++) {
    dij.addEdge(i, r[i], d[i]);
    dij.addEdge(r[i], i, d[i]);
  }
  vector<int> perm(N);
  for (int i = 0; i < N; i++) {
    perm[i] = i;
  }
  set<int> castle;
  for (int i = 0; i < M; i++) {
    int x;
    scanf("%d", &x);
    castle.insert(x);
  }
  partition(perm.begin(), perm.end(),
      [&castle](int x) {return castle.count(x) > 0;});
  int ans = calc(dij, perm);
  if (M + K == N) {
    printf("%d\n", ans);
    return 0;
  }
  while ((double)clock() / CLOCKS_PER_SEC <= 0.6) sa(dij, perm, ans);
  printf("%d\n", ans);
  return 0;
}
