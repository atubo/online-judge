// https://www.lintcode.com/problem/max-points-on-a-line/description
// 186. Max Points on a Line

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"
#include "../utils/Point.h"

class Solution {
private:
    int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a%b);
    }

    pair<int, int> calc(const Point &p1, const Point &p2) {
        if (p1.x == p2.x && p1.y == p2.y) return make_pair(0, 0);
        if (p1.x == p2.x) return make_pair(0, 1);
        int a = p2.x - p1.x, b = p2.y - p1.y;
        if (a < 0) {
            a = -a;
            b = -b;
        }
        int g = gcd(abs(a), abs(b));
        return make_pair(a/g, b/g);
    }
public:
    int maxPoints(vector<Point> &points) {
        const int n = points.size();
        if (n == 0) return 0;
        int ans = 1;
        for (int i = 0; i < n-1; i++) {
            int cnt = 1, mx = 0;
            map<pair<int, int>, int> m;
            for (int j = i+1; j < n; j++) {
                pair<int, int> slope = calc(points[i], points[j]);
                if (slope == make_pair(0, 0)) cnt++;
                else mx = max(mx, ++m[slope]);
            }
            ans = max(ans, mx + cnt);
        }
        return ans;
    }
};

int main() {
    Solution solution;
    vector<Point> points;
    cin >> points;
    cout << solution.maxPoints(points) << endl;
    return 0;
}
