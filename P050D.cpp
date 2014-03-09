#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cassert>
using namespace std;

double calcProb(const vector<double>& qArray, int r) {
    int m = qArray.size();
    assert(r <= m);
    vector<double> dpPrev(m+1, 0.0);
    vector<double> dpCurr(m+1, 0.0);
    dpPrev[0] = 1 - qArray[0];
    dpPrev[1] = qArray[0];
    for (int i = 1; i < m; i++) {
        double p = 1 - qArray[i];
        double q = qArray[i];
        dpCurr[0] = p * dpPrev[0];
        for (int j = 1; j <= i+1; j++) {
            dpCurr[j] = p * dpPrev[j] + q * dpPrev[j-1];
        }
        dpPrev = dpCurr;
    }
    double result = 0;
    for (int i = r; i <= m; i++) {
        result += dpPrev[i];
    }
    
    return result;
}

struct Point {
    Point(): x(0), y(0){}
    Point(int x_, int y_): x(x_), y(y_) {}
    int x;
    int y;
};

int distSq(const Point& p1, const Point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) +
           (p1.y - p2.y) * (p1.y - p2.y);
}

class DistComp {
public:
    DistComp(const Point& p0_): p0(p0_) {}
    bool operator() (const Point& p1, const Point& p2) {
        return distSq(p1, p0) < distSq(p2, p0);
    }
private:
    Point p0;
};

class Solution {
public:
    Solution() {
        cin >> N;
        cin >> K;
        cin >> epslon;
        epslon /= 1000;

        int x0, y0;
        cin >> x0 >> y0;
        p0.x = x0;
        p0.y = y0;

        for (int i = 0; i < N; i++) {
            int x, y;
            cin >> x >> y;
            targets.push_back(Point(x, y));
        }
        sort(targets.begin(), targets.end(), DistComp(p0));
    }

    void solve() {
        double r1 = 0;
        double r2 = sqrt(distSq(p0, targets.back()));
        while (r2 - r1 > 1e-7) {
            double rm = (r1 + r2)/2;
            if (success(rm*rm)) {
                r2 = rm;
            } else {
                r1 = rm;
            }
        }
        printf("%.6f\n", r1);
    }

private:
    int N;
    int K;
    double epslon;

    Point p0;
    vector<Point> targets;

    vector<double> hitProb;

    void calcHitProb(double rSquare) {
        hitProb.clear();
        for (Point p: targets) {
            int ds = distSq(p0, p);
            if (ds <= rSquare) continue;
            hitProb.push_back(exp(1-double(ds)/rSquare));
        }
    }

    bool success(double rSquare) {
        calcHitProb(rSquare);
        int inRange = N - hitProb.size();
        if (inRange >= K) return true;
        return calcProb(hitProb, K - inRange) >= 1 - epslon;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
