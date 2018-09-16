// https://www.lintcode.com/problem/water-and-jug-problem/description
// 1277. Water and Jug Problem

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        if (x > y) swap(x, y);
        int g = gcd(x, y);
        return z <= (x+y) && (z%g) == 0;
    }

    int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a%b);
    }
};

int main() {
    Solution solution;
    return 0;
}
