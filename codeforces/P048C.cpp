// https://codeforces.com/problemset/problem/48/C
// The Race

#include <bits/stdc++.h>
using namespace std;

int64_t gcd(int64_t a, int64_t b) {
  if (b == 0) return a;
  return gcd(b, a%b);
}

struct Ratio {
  Ratio(int64_t x1, int64_t y1) : x(x1), y(y1) {
    int64_t g = gcd(x, y);
    x /= g;
    y /= g;
  }
  int64_t x, y;
  bool operator < (const Ratio& other) const {
    return x * other.y < y * other.x;
  }
  bool operator == (const Ratio& other) const {
    return x * other.y == y * other.x;
  }
};

struct Range {
  Ratio x, y;
  bool isOpen;
  void merge(const Range& other) {
    x = max(x, other.x);
    if (other.y < y) {
      y = other.y;
      isOpen = other.isOpen;
    } else if (y == other.y) {
      isOpen |= other.isOpen;
    }
  }
};

int64_t calc(const Ratio& r, int n, int a) {
  return r.x*n/r.y + n*a;
}

int main() {
  int n;
  scanf("%d", &n);
  int a;
  scanf("%d", &a);
  Range range{.x = Ratio{0, 1}, .y = {1, 1}, .isOpen = true};
  for (int i = 2; i <= n; i++) {
    int t;
    scanf("%d", &t);
    int x = t - i*a;
    Range o{.x = Ratio{x, i}, .y = {x+1, i}, .isOpen = true};
    range.merge(o);
  }

  if (!range.isOpen) {
    if (range.x.x*(n+1)/range.x.y == range.y.x*(n+1)/range.y.y) {
      cout << "unique" << endl;
      cout << calc(range.x, n+1, a) << endl;
    } else {
      cout << "not unique" << endl;
    }
  } else {
    if (range.x.x*(n+1)/range.x.y == range.y.x*(n+1)/range.y.y) {
      cout << "unique" << endl;
      cout << calc(range.x, n+1, a) << endl;
    } else if (range.x.x*(n+1)/range.x.y == range.y.x*(n+1)/range.y.y-1 &&
        range.y.x*(n+1) % range.y.y == 0) {
      cout << "unique" << endl;
      cout << calc(range.x, n+1, a) << endl;
    } else {
      cout << "not unique" << endl;
    }
  }
      
  return 0;
}
