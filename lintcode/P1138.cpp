// https://www.lintcode.com/problem/can-place-flowers/description
// 1138. Can Place Flowers

#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canPlaceFlowers(vector<int> &flower, int n) {
        int m = maxfit(flower);
        return n <= m;
    }

    int maxfit(const vector<int> &a) {
        int p = -1;
        const int n = a.size();
        int ans = 0;
        while (p < n) {
            int q = p + 1;
            while (q < n && a[q] == 1) q++;
            if (q == n) break;
            p = q - 1;
            while (q < n && a[q] == 0) q++;
            if (q == n) q++;
            ans += (q - p - 1) / 2;
            p = q;
        }
        return ans;
    }
};

int main() {
    Solution solution;
    auto a = getVector();
    int n;
    cin >> n;
    cout << solution.canPlaceFlowers(a, n) << endl;
    return 0;
}
