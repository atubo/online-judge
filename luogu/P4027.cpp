// https://www.luogu.org/problemnew/show/P4027
// [NOI2007]货币兑换

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
const double EPS = 1e-9;

typedef tree<double, double, less<double>, rb_tree_tag,
        tree_order_statistics_node_update> ordered_map;

double slope(double x1, double y1, double x2, double y2) {
    double ret = (y1 - y2) / (x1 - x2);
    return -ret;
}

void buy(double c, double a, double b, double r, double &xa, double &xb) {
    xa = (r*c) / (r*a + b);
    xb = c / (r*a + b);
}

double sell(const pair<double, double>&p, double a, double b) {
    return p.first*a + p.second*b;
}

int bisearch(const ordered_map &cntr, double s) {
    // find the first j that slope(j, j+1) > s
    const int n = cntr.size();
    if (n == 1) return 0;
    pair<double, double> p1 = *cntr.find_by_order(n-2);
    pair<double, double> p2 = *cntr.find_by_order(n-1);
    if (slope(p1.first, p1.second, p2.first, p2.second) <= s) {
        return n-1;
    }

    int lo = -1, hi = n-2;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        p1 = *cntr.find_by_order(mid);
        p2 = *cntr.find_by_order(mid+1);
        if (slope(p1.first, p1.second, p2.first, p2.second) <= s) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    return hi;
}

pair<double, double> cross(const pair<double, double> &p,
                           double s, double r) {
    double x = (p.second + s*p.first)/(1.0/r + s);
    double y = x/r;
    return make_pair(x, y);
}

double direction(const pair<double, double> &p1,
                 const pair<double, double> &p2,
                 const pair<double, double> &p3) {
    double x1 = p2.first - p1.first;
    double y1 = p2.second  - p1.second;
    double x2 = p3.first - p2.first;
    double y2 = p3.second - p2.second;
    return x1*y2 - y1*x2;
}

bool same(const pair<double, double> &p,
          const pair<double, double> &q) {
    return fabs(p.first - q.first) < EPS &&
        fabs(p.second - q.second) < EPS;
}

void addPoint(ordered_map &cntr,
              const pair<double, double> &p) {
    int j = cntr.order_of_key(p.first) - 1;
    if (j >= 0) {
        auto q = *cntr.find_by_order(j);
        if (same(p, q)) return;
    }
    if (j < (int)cntr.size()-1) {
        auto q = *cntr.find_by_order(j+1);
        if (same(p, q)) return;
    }
    ordered_map::iterator it1, it2;
    if (j == -1) {
        it1 = cntr.find_by_order(0);
        if (p.first == it1->first) {
            if (p.second <= it1->second) return;
            it1->second = p.second;
        } else {
            cntr.insert(p);
        }
        while (cntr.size() > 2) {
            it1 = cntr.find_by_order(1);
            it2 = cntr.find_by_order(2);
            if (direction(p, *it1, *it2) < 0) break;
            cntr.erase(it1);
        }
    } else if (j == (int)cntr.size()-1) {
        cntr.insert(p);
        int k = j;
        while (k > 0) {
            it1 = cntr.find_by_order(k);
            it2 = cntr.find_by_order(k-1);
            if (direction(p, *it1, *it2) > 0) break;
            cntr.erase(it1);
            k--;
        }
    } else {
        it1 = cntr.find_by_order(j);
        it2 = cntr.find_by_order(j+1);
        if (direction(*it1, p, *it2) >= 0) return;
        if (p.first == it2->first) {
            it2->second = p.second;
        } else {
            cntr.insert(p);
        }
        int k = j;
        while (k > 0) {
            it1 = cntr.find_by_order(k);
            it2 = cntr.find_by_order(k-1);
            if (direction(p, *it1, *it2) > 0) break;
            cntr.erase(it1);
            k--;
        }
        while ((int)cntr.size() >= k+4) {
            it1 = cntr.find_by_order(k+2);
            it2 = cntr.find_by_order(k+3);
            if (direction(p, *it1, *it2) < 0) break;
            cntr.erase(it1);
        }
    }
}


void print(const ordered_map &cntr) {
    for (const auto &p: cntr) {
        printf("(%.2f %.2f) ", p.first, p.second);
    }
    printf("\n");
}

int N, S;

int main() {
    scanf("%d%d", &N, &S);
    double curr = S;
    ordered_map cntr;
    for (int i = 0; i < N; i++) {
        double a, b, r;
        scanf("%lf%lf%lf", &a, &b, &r);
        double xa, xb;
        buy(curr, a, b, r, xa, xb);
        if (cntr.empty()) {
            cntr.insert({xa, xb});
            continue;
        }
        addPoint(cntr, {xa, xb});
        int j = bisearch(cntr, a/b);
        auto p = *cntr.find_by_order(j);
        auto q = cross(p, a/b, r);
        ordered_map::iterator it1, it2;
        if (p.second / p.first > 1.0/r) {
            while (j+1 < (int)cntr.size() &&
                   (it1=cntr.find_by_order(j+1))->first <= q.first + EPS) {
                cntr.erase(it1);
            }
            while (j+1 < (int)cntr.size()-1) {
                it1 = cntr.find_by_order(j+1);
                it2 = cntr.find_by_order(j+2);
                if (direction(q, *it1, *it2) < 0) break;
                cntr.erase(it1);
            }
        } else {
            while (j-1 >= 0 &&
                   (it1=cntr.find_by_order(j-1))->first >= q.first - EPS) {
                cntr.erase(it1);
                j--;
            }
            while (j-1 > 0) {
                it1 = cntr.find_by_order(j-1);
                it2 = cntr.find_by_order(j-2);
                if (direction(q, *it1, *it2) > 0) break;
                cntr.erase(it1);
                j--;
            }
        }
        if (!same(p, q)) cntr.insert(q);
        curr = max(curr, sell(p, a, b));
    }
    printf("%.3f", curr);

    return 0;
}
