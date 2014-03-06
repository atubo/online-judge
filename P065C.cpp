#include <vector>
#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;

struct Point {
    Point():x(0), y(0), z(0) {}
    Point(double x_, double y_, double z_): x(x_), y(y_), z(z_) {}
    double x;
    double y;
    double z;
};

Point midPt(const Point& p1, const Point& p2) {
    return Point((p1.x + p2.x)/2, (p1.y + p2.y)/2, (p1.z + p2.z)/2);
}

double dist(const Point& p1, const Point& p2) {
    return sqrt((p1.x-p2.x) * (p1.x-p2.x) +
                (p1.y-p2.y) * (p1.y-p2.y) +
                (p1.z-p2.z) * (p1.z-p2.z));
}

pair<bool, double> canCatch(const Point& pCurr, const Point& pNext,
                            const Point& p0, int vs, int vp, double t0) {
    double t1 = dist(pCurr, pNext)/vs + t0;
    double t2 = dist(p0, pNext)/vp;
    return make_pair(t1 >= t2, t1);
}

Point findPos(const Point& pCurr, const Point& pNext,
              const Point& p0, int vs, int vp, double t0) {
    Point p1 = pCurr;
    Point p2 = pNext;
    while (dist(p1, p2) >= 1e-8) {
        Point p3 = midPt(p1, p2);
        pair<bool, double> rt = canCatch(pCurr, p3, p0, vs, vp, t0);
        if (rt.first) {
            p2 = p3;
        } else {
            p1 = p3;
        }
    }
    return p1;
}

void printResult(double tx, const Point& px) {
    cout << "YES" << endl;
    printf("%.7f\n", tx);
    printf("%.7f %.7f %.7f\n", px.x, px.y, px.z);
}

int main() {
    int n;
    cin >> n;
    vector<Point> pts;
    for (int i = 0; i < n+1; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        pts.push_back(Point(x, y, z));
    }

    int vs, vp;
    cin >> vs >> vp;

    int x, y, z;
    cin >> x >> y >> z;
    Point p0(x, y, z);

    if (dist(p0, pts[0]) == 0) {
        printResult(0, p0);
        return 0;
    }

    bool found = false;
    double tau = 0;
    for (int i = 1; i < n+1; i++) {
        pair<bool, double> rt = canCatch(pts[i-1], pts[i], p0, vs, vp, tau);
        if (rt.first) {
            Point px = findPos(pts[i-1], pts[i], p0, vs, vp, tau);
            double tx = dist(p0, px)/vp;
            printResult(tx, px);
            found = true;
            break;
        }
        tau = rt.second;
    }

    if (!found) {
        cout << "NO" << endl;
    }

    return 0;
}

