// https://codeforces.com/problemset/problem/51/D
// Geometrical problem

#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
  assert(a >= 0 && b >= 0);
  if (b == 0) return a;
  return gcd(b, a%b);
}

int sign(int x) {
  return x > 0 ? 1 : (x == 0 ? 0 : -1);
}

struct Ratio {
  Ratio(int x, int y) {
    if (y == 0) {
      a = 0;
      b = 1;
      return;
    }
    if (x == 0) {
      a = 1;
      b = 0;
      return;
    }
    int g = gcd(abs(x), abs(y));
    a = abs(x) / g;
    b = abs(y) / g;
    if (sign(x) != sign(y)) a = -a;
  }

  bool operator == (const Ratio& other) const {
    return b != 0 && a == other.a && b == other.b;
  }

  bool operator != (const Ratio& other) const {
    return !(*this == other);
  }

  int a, b;
};

bool checkFix(const vector<int>& a) {
  const int n = a.size();
  if (n == 2) return true;
  Ratio r0(a[0], a[1]);
  for (int i = 1; i < n-1; i++) {
    Ratio r(a[i], a[i+1]);
    if (r != r0) return false;
  }

  return true;
}

vector<int> removeOne(const vector<int>& a, int idx) {
  assert(idx < (int)a.size());
  vector<int> b(a.size()-1);
  for (int i = 0; i < idx; i++) {
    b[i] = a[i];
  }
  for (int i = idx; i < (int)a.size()-1; i++) {
    b[i] = a[i+1];
  }
  return b;
}

int checkNonFix(const vector<int>& a) {
  const int n = a.size();
  int idx = -1;
  for (int i = 0; i < n-2; i++) {
    if (Ratio(a[i], a[i+1]) != Ratio(a[i+1], a[i+2])) {
      idx = i;
      break;
    }
  }
  if (idx == -1) {
    return 0;
  }
  vector<int> b = removeOne(a, idx);
  if (checkFix(b)) return 1;
  b = removeOne(a, idx+1);
  if (checkFix(b)) return 1;
  b = removeOne(a, idx+2);
  return checkFix(b) ? 1 : 2;
}

int main() {
  int n;
  scanf("%d", &n);
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  if (a.size() == 2) {
    if (a[0] == 0) printf("%d\n", a[1] == 0 ? 0 : 1);
    else printf("0\n");
    return 0;
  }
  printf("%d\n", checkNonFix(a));
  return 0;
}
