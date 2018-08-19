// https://www.lintcode.com/problem/k-closest-points/description
// 612. K Closest Points

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

struct Point {
    int x, y;
    Point(): x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

class Solution {
    struct Data {
        int64_t dist;
        int x, y, id;
        bool operator < (const Data &other) const {
            if (dist < other.dist) return true;
            if (dist > other.dist) return false;
            if (x < other.x) return true;
            if (x > other.x) return false;
            if (y < other.y) return true;
            if (y > other.y) return false;
            return id < other.id;
        }
    };

public:
    vector<Point> kClosest(vector<Point> &points, Point &origin, int k) {
        vector<Data> data;
        for (int i = 0; i < (int)points.size(); i++) {
            int x = points[i].x, y = points[i].y;
            int64_t dx = x - origin.x, dy = y - origin.y;
            data.push_back({dx*dx + dy*dy, x, y, i});
        }
        sort(data.begin(), data.end());
        vector<Point> ret(k);
        for (int i = 0; i < k; i++) {
            ret[i] = points[data[i].id];
        }
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
