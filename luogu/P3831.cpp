// https://www.luogu.com.cn/problem/P3831
// [SHOI2012]回家的路

#include <bits/stdc++.h>
using namespace std;

class FastDijkstra {
 public:
  static const int64_t INF;

  typedef pair<int64_t,int> PII;  // pair = (dist, vertex)

  FastDijkstra(int N_): N(N_), edges(N), dist(N, INF), dad(N, -1) {}

  void addEdge(int u, int v, int64_t wt) {
    //printf("add edge %d->%d w=%ld\n", u, v, wt);
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
const int MAXM = 100000;
int N, M;

struct Point {
  int r, c;
  int rid, cid;
  int ridx, cidx;
} P[MAXM];

int main() {
  vector<int> sr, sc;
  scanf("%d%d", &N, &M);
  for (int i = 0; i < M; i++) {
    int r, c;
    scanf("%d%d", &r, &c);
    P[i] = {.r = r, .c = c};
    sr.push_back(r);
    sc.push_back(c);
  }
  int x1, y1, x2, y2;
  scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
  if (x1 == x2) {
    printf("%d\n", 2*abs(y1-y2));
    return 0;
  }
  if (y1 == y2) {
    printf("%d\n", 2*abs(x1-x2));
    return 0;
  }
  sr.push_back(x1);
  sr.push_back(x2);
  sc.push_back(y1);
  sc.push_back(y2);
  sort(sr.begin(), sr.end());
  sort(sc.begin(), sc.end());
  sr.erase(unique(sr.begin(), sr.end()), sr.end());
  sc.erase(unique(sc.begin(), sc.end()), sc.end());
  vector<vector<int>> rows(sr.size());
  vector<vector<int>> cols(sc.size());
  for (int i = 0; i < M; i++) {
    int rid = lower_bound(sr.begin(), sr.end(), P[i].r) - sr.begin();
    int cid = lower_bound(sc.begin(), sc.end(), P[i].c) - sc.begin();
    P[i].rid = rid;
    P[i].cid = cid;
    rows[rid].push_back(i);
    cols[cid].push_back(i);
  }
  for (int i = 0; i < (int)rows.size(); i++) {
    sort(rows[i].begin(), rows[i].end(),
        [](int p, int q) {return P[p].cid < P[q].cid;});
  }
  for (int i = 0; i < (int)cols.size(); i++) {
    sort(cols[i].begin(), cols[i].end(),
        [](int p, int q) {return P[p].rid < P[q].rid;});
  }

  FastDijkstra dij(2*M+6);

  for (int i = 0; i < (int)rows.size(); i++) {
    for (int j = 0; j < (int)rows[i].size(); j++) {
      int u = rows[i][j];
      if (j > 0) {
        int v = rows[i][j-1];
        int d = sc[P[u].cid] - sc[P[v].cid];
        dij.addEdge(u, v, 2*d);
      }
      if (j < (int)rows[i].size()-1) {
        int v = rows[i][j+1];
        int d = sc[P[v].cid] - sc[P[u].cid];
        dij.addEdge(u, v, 2*d);
      }
    }
  }
  for (int i = 0; i < (int)cols.size(); i++) {
    for (int j = 0; j < (int)cols[i].size(); j++) {
      int u = cols[i][j];
      if (j > 0) {
        int v = cols[i][j-1];
        int d = sr[P[u].rid] - sr[P[v].rid];
        dij.addEdge(u+M, v+M, 2*d);
      }
      if (j < (int)cols[i].size()-1) {
        int v = cols[i][j+1];
        int d = sr[P[v].rid] - sr[P[u].rid];
        dij.addEdge(u+M, v+M, 2*d);
      }
    }
  }
  int ns = -1, nt = -1;
  for (int i = 0; i < M; i++) {
    if (P[i].r == x1 && P[i].c == y1) ns = i;
    if (P[i].r == x2 && P[i].c == y2) nt = i;
    int u = i, v = u+M;
    dij.addEdge(u, v, 1);
    dij.addEdge(v, u, 1);
  }
  if (ns != -1) {
    dij.addEdge(2*M+4, ns, 0);
    dij.addEdge(2*M+4, ns+M, 0);
  } else {
    int rid = lower_bound(sr.begin(), sr.end(), x1) - sr.begin();
    if (!rows[rid].empty()) {
      int cid = lower_bound(rows[rid].begin(), rows[rid].end(), y1,
          [](int i, int c) {return P[i].c < c;}) - rows[rid].begin();
      assert(cid == (int)rows[rid].size() || P[rows[rid][cid]].c != y1);
      if (cid > 0) {
        int d = y1 - sc[P[rows[rid][cid-1]].cid];
        dij.addEdge(rows[rid][cid-1], 2*M, 2*d);
        dij.addEdge(2*M, rows[rid][cid-1], 2*d);
      }
      if (cid < (int)rows[rid].size()) {
        int d = sc[P[rows[rid][cid]].cid] - y1;
        dij.addEdge(rows[rid][cid], 2*M, 2*d);
        dij.addEdge(2*M, rows[rid][cid], 2*d);
      }
    }

    int cid = lower_bound(sc.begin(), sc.end(), y1) - sc.begin();
    if (!cols[cid].empty()) {
      rid = lower_bound(cols[cid].begin(), cols[cid].end(), x1,
          [](int i, int r) {return P[i].r < r;}) - cols[cid].begin();
      assert(rid == (int)cols[cid].size() || P[cols[cid][rid]].r != x1);
      if (rid > 0) {
        int d = x1 - sr[P[cols[cid][rid-1]].rid];
        dij.addEdge(cols[cid][rid-1]+M, 2*M+1, 2*d);
        dij.addEdge(2*M+1, cols[cid][rid-1]+M, 2*d);
      }
      if (rid  < (int)cols[cid].size()) {
        int d = sr[P[cols[cid][rid]].rid] - x1;
        dij.addEdge(cols[cid][rid]+M, 2*M+1, 2*d);
        dij.addEdge(2*M+1, cols[cid][rid]+M, 2*d);
      }
    }
    dij.addEdge(2*M+4, 2*M, 0);
    dij.addEdge(2*M+4, 2*M+1, 0);
  }
  if (nt != -1) {
    dij.addEdge(nt, 2*M+5, 0);
    dij.addEdge(nt+M, 2*M+5, 0);
  } else {
    int rid = lower_bound(sr.begin(), sr.end(), x2) - sr.begin();
    if (!rows[rid].empty()) {
      int cid = lower_bound(rows[rid].begin(), rows[rid].end(), y2,
          [](int i, int c) {return P[i].c < c;}) - rows[rid].begin();
      assert(cid == (int)rows[rid].size() || P[rows[rid][cid]].c != y2);
      if (cid > 0) {
        int d = y2 - sc[P[rows[rid][cid-1]].cid];
        dij.addEdge(rows[rid][cid-1], 2*M+2, 2*d);
        dij.addEdge(2*M+2, rows[rid][cid-1], 2*d);
      }
      if (cid < (int)rows[rid].size()) {
        int d = sc[P[rows[rid][cid]].cid] - y2;
        dij.addEdge(rows[rid][cid], 2*M+2, 2*d);
        dij.addEdge(2*M+2, rows[rid][cid], 2*d);
      }
    }

    int cid = lower_bound(sc.begin(), sc.end(), y2) - sc.begin();
    if (!cols[cid].empty()) {
      rid = lower_bound(cols[cid].begin(), cols[cid].end(), x2,
          [](int i, int r) {return P[i].r < r;}) - cols[cid].begin();
      assert(rid == (int)cols[cid].size() || P[cols[cid][rid]].r != x2);
      if (rid > 0) {
        int d = x2 - sr[P[cols[cid][rid-1]].rid];
        dij.addEdge(cols[cid][rid-1]+M, 2*M+3, 2*d);
        dij.addEdge(2*M+3, cols[cid][rid-1]+M, 2*d);
      }
      if (rid < (int)cols[cid].size()) {
        int d = sr[P[cols[cid][rid]].rid] - x2;
        dij.addEdge(cols[cid][rid]+M, 2*M+3, 2*d);
        dij.addEdge(2*M+3, cols[cid][rid]+M, 2*d);
      }
    }
    dij.addEdge(2*M+2, 2*M+5, 0);
    dij.addEdge(2*M+3, 2*M+5, 0);
  }

  dij.solve(2*M+4);
  int64_t d = dij.getDist()[2*M+5];
  printf("%ld\n", d == FastDijkstra::INF ? -1 : d);

  return 0;
}
