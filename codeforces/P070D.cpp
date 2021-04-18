// https://codeforces.com/problemset/problem/70/D
// Professor's task

#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;

  bool operator < (const Point& other) const {
    if (x != other.x) return x < other.x;
    return y < other.y;
  }

  friend Point operator - (const Point& p1, const Point& p2) {
    return Point{p1.x - p2.x, p1.y - p2.y};
  }

  friend int64_t operator * (const Point& p1, const Point& p2) {
    return 1LL * p1.x * p2.y - 1LL * p1.y * p2.x;
  }
};

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, Point, less<int>, rb_tree_tag,
             tree_order_statistics_node_update> ordered_set;
typedef ordered_set::iterator Iter;

int64_t cross(const Point& p1, const Point& p2, const Point& p3) {
  Point p = p2 - p1;
  Point q = p3 - p2;
  return p * q;
}

void process(ordered_set& convex, int x, int y) {
  if (convex.empty()) {
    convex.insert(make_pair(x, Point{x, y}));
    return;
  }
  if (convex.size() == 1) {
    Point& p0 = convex.find_by_order(0)->second;
    if (p0.x == x) {
      p0.y = min(p0.y, y);
      return;
    }
    convex.insert(make_pair(x, Point{x, y}));
    return;
  }
  const int n = convex.size();
  int l = convex.order_of_key(x) - 1;
  int r = l + 1;
  Point p{x, y};
  if (l >= 0 && r < n) {
    Point p1 = convex.find_by_order(l)->second;
    Point p2 = convex.find_by_order(r)->second;
    if (cross(p1, p, p2) <= 0) return;
  }
  vector<Iter> td;
  for (int i = r; i < n-1; i++) {
    Iter it = convex.find_by_order(i);
    Point p1 = it->second;
    Point p2 = convex.find_by_order(i+1)->second;
    if (cross(p, p1, p2) > 0) break;
    td.push_back(it);
  }
  for (int i = l; i >= 1; i--) {
    Iter it = convex.find_by_order(i);
    Point p1 = it->second;
    Point p2 = convex.find_by_order(i-1)->second;
    if (cross(p, p1, p2) < 0) break;
    td.push_back(it);
  }
  if (r == n-1) {
    Iter it = convex.find_by_order(r);
    if (it->second.x == p.x && it->second.y >= p.y) {
      td.push_back(it);
    }
  }
  for (const auto& it : td) {
    convex.erase(it);
  }
  convex.insert(make_pair(x, p));
}

bool above(const ordered_set& convex, int x, int y) {
  const int n = convex.size();
  if (n == 0) return false;
  int l = convex.order_of_key(x) - 1;
  int r = l + 1;
  if (l < 0) {
    Point pr = convex.find_by_order(r)->second;
    return x == pr.x && y >= pr.y;
  }
  if (r == n) return false;
  Point pl = convex.find_by_order(l)->second;
  Point pr = convex.find_by_order(r)->second;
  const Point p{x, y};
  return cross(pl, p, pr) <= 0;
}

void solve(const ordered_set& upper, const ordered_set& lower, int x, int y) {
  bool ok = above(upper, x, -y) && above(lower, x, y);
  printf(ok ? "YES\n" : "NO\n");
}

int main() {
  int q;
  scanf("%d", &q);
  ordered_set upper, lower;
  for (int i = 0; i < q; i++) {
    int t, x, y;
    scanf("%d%d%d", &t, &x, &y);
    if (t == 1) {
      process(upper, x, -y);
      process(lower, x, y);
    } else {
      solve(upper, lower, x, y);
    }
  }
  return 0;
}
