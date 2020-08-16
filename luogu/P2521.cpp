// https://www.luogu.com.cn/problem/P2521
// [HAOI2011]防线修建

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

struct Point {
  int x, y;
  bool operator < (const Point& other) const {
    if (x != other.x) return x < other.x;
    return y < other.y;
  }
};

using ordered_set = tree<Point, null_type, less<Point>, rb_tree_tag,
      tree_order_statistics_node_update>;
using Iter = ordered_set::point_iterator;

struct Query {
  int op, u;
};

int crossProd(int x1, int y1, int x2, int y2) {
  return x1 * y2 - x2 * y1;
}

int crossProd(const Point& p1, const Point& p2, const Point& p3) {
  return crossProd(p2.x - p1.x, p2.y - p1.y, p3.x - p2.x, p3.y - p2.y);
}

int crossProd(const ordered_set& ct, int i, int j, int k) {
  Point p1 = *ct.find_by_order(i);
  Point p2 = *ct.find_by_order(j);
  Point p3 = *ct.find_by_order(k);
  return crossProd(p1, p2, p3);
}

int crossProd(const ordered_set& ct, int i, const Point& p2, int j) {
  Point p1 = *ct.find_by_order(i);
  Point p3 = *ct.find_by_order(j);
  return crossProd(p1, p2, p3);
}

int crossProd(const ordered_set& ct, int i, int j, const Point& p3) {
  Point p1 = *ct.find_by_order(i);
  Point p2 = *ct.find_by_order(j);
  return crossProd(p1, p2, p3);
}

int crossProd(const ordered_set& ct, const Point& p1, int i, int j) {
  Point p2 = *ct.find_by_order(i);
  Point p3 = *ct.find_by_order(j);
  return crossProd(p1, p2, p3);
}

void remove(ordered_set& ct, int i) {
  ct.erase(ct.find_by_order(i));
}

double dist(const Point& p1, const Point& p2) {
  int xsq = (p1.x - p2.x) * (p1.x - p2.x);
  int ysq = (p1.y - p2.y) * (p1.y - p2.y);
  return sqrt(xsq + ysq);
}

double calcDist(const ordered_set& ct) {
  Point last{0, 0};
  double ans = 0;
  for (int i = 1; i < (int)ct.size(); i++) {
    Point now = *ct.find_by_order(i);
    ans += dist(last, now);
    last = now;
  }
  return ans;
}

double buildContour(ordered_set& ct) {
  int p = 2;
  while (p < (int)ct.size()) {
    while (p > 1 && crossProd(ct, p-2, p-1, p) >= 0) {
      remove(ct, p-1);
      p--;
    }
    p++;
  }
  return calcDist(ct);
}

double add(ordered_set& ct, const Point& pt, double len) {
  int p = ct.order_of_key(pt) - 1;
  int q = p + 1;
  if (crossProd(ct, p, pt, q) >= 0) return len;

  while (p > 0 && crossProd(ct, p-1, p, pt) >= 0) p--;
  while (q < (int)ct.size()-1 && crossProd(ct, pt, q, q+1) >= 0) q++;

  Point last = *ct.find_by_order(p);
  for (int i = p+1; i < q; i++) {
    Point now = *ct.find_by_order(i);
    len -= dist(last, now);
    last = now;
  }
  Point now = *ct.find_by_order(q);
  len -= dist(last, now);

  len += dist(pt, now);
  Point p0 = *ct.find_by_order(p);
  len += dist(pt, p0);

  for (int i = q-1; i > p; i--) {
    remove(ct, i);
  }

  ct.insert(pt);
  
  return len;
}

int main() {
  int n, x, y;
  scanf("%d%d%d", &n, &x, &y);
  int m;
  scanf("%d", &m);
  vector<bool> inProtection(m, true);
  vector<Point> cities;
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    cities.push_back(Point{a, b});
  }
  int q;
  scanf("%d", &q);
  vector<Query> queries;
  for (int i = 0; i < q; i++) {
    int op, u = -1;
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d", &u);
      u--;
      inProtection[u] = false;
    }
    queries.push_back(Query{op, u});
  }

  ordered_set ct;
  ct.insert(Point{0, 0});
  ct.insert(Point{n, 0});
  ct.insert(Point{x, y});

  for (int i = 0; i < m; i++) {
    if (inProtection[i]) {
      ct.insert(cities[i]);
    }
  }

  double len = buildContour(ct);

  vector<double> ans;
  for (int i = q-1; i >= 0; i--) {
    if (queries[i].op == 2) {
      ans.push_back(len);
    } else {
      len = add(ct, cities[queries[i].u], len);
    }
  }
  for (int i = ans.size()-1; i >= 0; i--) {
    printf("%.2f\n", ans[i]);
  }

  return 0;
}
