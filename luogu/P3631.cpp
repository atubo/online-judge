// https://www.luogu.com.cn/problem/P3631
// [APIO2011]方格染色

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
    const int N;
    vector<int> rank;
    vector<int> parent;

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

public:
    UnionFind(int n): N(n) {
        rank.resize(N);
        parent.resize(N);

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
};

const int MOD = 1e9;
const int MAXK = 100010;
int N, M, K;
struct Cell {
  int x, y, c;
  bool operator < (const Cell& other) const {
    if (x != other.x) return x < other.x;
    return y < other.y;
  }
} C[MAXK];

struct Part {
  int y, c;
  bool operator < (const Part& other) const {
    if (y != other.y) return y < other.y;
    return c < other.c;
  }
  Part flip(bool f) const {
    return Part{y, c^f};
  }
};

struct Line {
  int x;
  vector<Part> even, odd;
  int count() const {
    return even.size() + odd.size();
  }
  bool merge(const Line& other, int mask) {
    // mask: 0 - all same, 1 - odd flip, 2 - even split, 3 - both flip
    if (!mergeParts(even, other.even, mask & 2)) return false;
    return mergeParts(odd, other.odd, mask & 1);
  }

  static bool mergeParts(
      vector<Part>& parts, const vector<Part>& other, bool flip) {
    int i = 0, j = 0;
    vector<Part> m;
    while (i < (int)parts.size() && j < (int)other.size()) {
      int y1 = parts[i].y, y2 = other[j].y;
      if (y1 < y2) m.push_back(parts[i++]);
      else if (y1 > y2) m.push_back(other[j++].flip(flip));
      else {
        if ((parts[i].c ^ flip) != other[j].c) return false;
        m.push_back(parts[i]);
        i++; j++;
      }
    }
    while (i < (int)parts.size()) m.push_back(parts[i++]);
    while (j < (int)other.size()) m.push_back(other[j++].flip(flip));
    parts = std::move(m);
    return true;
  }

  int get(int y) const {
    return (y & 1) ? get(odd, y) : get(even, y);
  }

  static int get(const vector<Part>& parts, int y) {
    return lower_bound(parts.begin(), parts.end(), Part{y, 0})->c;
  }
};

int qpow(int n) {
  int64_t ret = 1;
  int64_t x = 2;
  while (n > 0) {
    if (n & 1) {
      ret = (ret * x) % MOD;
    }
    x = (x * x) % MOD;
    n >>= 1;
  }
  return ret;
}

int main() {
  scanf("%d%d%d", &N, &M, &K);
  set<pair<int, int>> seen;
  vector<int> ypos;
  for (int i = 0; i < K; i++) {
    int x, y, c;
    scanf("%d%d%d", &x, &y, &c);
    x--; y--;
    if (seen.find(make_pair(x, y)) != seen.end()) {
      assert(0);
    }
    seen.insert(make_pair(x, y));
    C[i] = {x, y, c};
    ypos.push_back(y);
  }
  sort(C, C+K);
  sort(ypos.begin(), ypos.end());
  ypos.erase(unique(ypos.begin(), ypos.end()), ypos.end());
  vector<Line> lines;
  {
    int p = 0;
    while (p < K) {
      int q = p + 1;
      while (q < K && C[q].x == C[p].x) q++;
      lines.push_back(Line{});
      auto& line = lines.back();
      line.x = C[p].x;
      for (int i = p; i < q; i++) {
        int y = C[i].y;
        int c = C[i].c;
        if (y & 1) {
          line.odd.push_back({y, c});
        } else {
          line.even.push_back({y, c});
        }
      }
      p = q;
    }
  }
  const int nl = lines.size();
#if 0
  printf("nl = %d\n", nl);
  for (const auto& line : lines) {
    printf("line %d: ", line.x);
    printf("even: ");
    for (const auto& part : line.even) {
      printf("(%d %d) ", part.y, part.c);
    }
    printf("odd: ");
    for (const auto& part : line.odd) {
      printf("(%d %d) ", part.y, part.c);
    }
    printf("\n");
  }
#endif

  map<int, vector<int>> yToLines;
  for (int i = 0; i < (int)lines.size(); i++) {
    for (const auto& part : lines[i].even) {
      yToLines[part.y].push_back(i);
    }
    for (const auto& part : lines[i].odd) {
      yToLines[part.y].push_back(i);
    }
  }

#if 0
  for (const auto& [y, ids] : yToLines) {
    printf("y=%d: ", y);
    for (int x : ids) {
      printf("%d ", x);
    }
    printf("\n");
  }
#endif

  UnionFind uf(nl);
  for (const auto& [y, ids] : yToLines) {
    if (ids.size() < 2) continue;
    int p = ids[0];
    for (int i = 1; i < (int)ids.size(); i++) {
      int q = ids[i];
      int u = uf.find(p);
      int v = uf.find(q);
      bool ok = true;
      if (u != v) {
        if (abs(lines[u].x - lines[v].x) & 1) {
          if (y & 1) {
            if (lines[u].get(y) != lines[v].get(y)) {
              ok = lines[u].merge(lines[v], 1);
            } else {
              ok = lines[u].merge(lines[v], 2);
            }
          } else {
            if (lines[u].get(y) != lines[v].get(y)) {
              ok = lines[u].merge(lines[v], 2);
            } else {
              ok = lines[u].merge(lines[v], 1);
            }
          }
        } else {
          if (lines[u].get(y) != lines[v].get(y)) {
            ok = lines[u].merge(lines[v], 3);
          } else {
            ok = lines[u].merge(lines[v], 0);
          }
        }
        if (!ok) {
          printf("0\n");
          return 0;
        }

        int w = uf.join(u, v);
        swap(lines[w], lines[u]);
      }
    }
  }

  set<int> processed;
  int total = 0;
  int cnt = 0;
  for (int i = 0; i < (int)lines.size(); i++) {
    int u = uf.find(i);
    if (processed.count(u) > 0) continue;
    processed.insert(u);
    total += lines[u].count();
    cnt++;
  }
#if 0
  printf("total=%d cnt=%d nl=%d\n", total, cnt, nl);
#endif

  printf("%d\n", qpow(N+M-total+cnt-nl-1));
  return 0;
}
