#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool isHappy(int n) {
        set<int> vis;
        vis.insert(n);
        while (true) {
            int x = transit(n);
            if (x == 1) return true;
            if (vis.count(x) > 0) return false;
            vis.insert(x);
            n = x;
        }
        return false;
    }
private:
    int transit(int x) {
        int ans = 0;
        while (x > 0) {
            int d = x % 10;
            ans += d*d;
            x /= 10;
        }
        return ans;
    }
};

int main() {
    Solution solution;
    int n;
    cin >> n;
    printf("%d\n", solution.isHappy(n));
    return 0;
}
