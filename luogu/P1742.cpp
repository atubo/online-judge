// https://www.luogu.com.cn/problem/P1742
// 最小圆覆盖

#include <bits/stdc++.h>
using namespace std;

struct Vec {
  double x, y;
  Vec(double x0 = 0, double y0 = 0): x(x0), y(y0) {}
  Vec operator + (const Vec& other) const {
    return Vec(x + other.x, y + other.y);
  }
  Vec operator - (const Vec& other) const {
    return Vec(x - other.x, y - other.y);
  }
  Vec operator * (double t) const {
    return Vec(x * t, y * t);
  }
  Vec operator / (double t) const {
    return Vec(x / t, y / t);
  }
  double lenSq() const {return x*x + y*y;}
  double len() const {return sqrt(lenSq());}
  Vec norm() const {
    return *this/len();
  }
  Vec rotate() const {
    return Vec(y, -x);
  }
};

double distSq(const Vec& a, const Vec& b) {
  return (a-b).lenSq();
}

double dot(const Vec& a, const Vec& b) {
  return a.x * b.x + a.y * b.y;
}

double cross(const Vec& a, const Vec& b) {
  return a.x * b.y - a.y * b.x;
}

Vec intersect(const Vec& p0, const Vec& v0, const Vec& p1, const Vec& v1) {
  double t = cross(p1-p0, v1) / cross(v0, v1);
  return p0 + v0 * t;
}

Vec circle(const Vec& a, const Vec& b, const Vec& c) {
  return intersect((a+b)/2, (b-a).rotate(), (a+c)/2, (c-a).rotate());
}

const int MAXN = 100010;
int N;
Vec P[MAXN];

int main() {
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    scanf("%lf%lf", &P[i].x, &P[i].y);
  }
  random_shuffle(P, P+N);
  Vec o;
  double r2 = 0;
  for (int i = 0; i < N; i++) {
    if (distSq(P[i], o) > r2) {
      o = P[i];
      r2 = 0;
      for (int j = 0; j < i; j++) {
        if (distSq(P[j], o) > r2) {
          o = (P[i] + P[j]) / 2;
          r2 = distSq(P[j], o);
          for (int k = 0; k < j; k++) {
            if (distSq(P[k], o) > r2) {
              o = circle(P[i], P[j], P[k]);
              r2 = distSq(P[k], o);
            }
          }
        }
      }
    }
  }
  printf("%.10lf\n", sqrt(r2));
  printf("%.10lf %.10lf\n", o.x, o.y);

  return 0;
}
