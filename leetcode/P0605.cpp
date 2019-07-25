// https://leetcode.com/problems/can-place-flowers/
// 605. Can Place Flowers

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        const int sz = flowerbed.size();
        int p = 0, q = 0, ans = 0;
        while (true) {
            while (p < sz && flowerbed[p] == 1) p++;
            if (p == sz) break;
            q = p;
            while (q < sz && flowerbed[q] == 0) q++;
            ans += solve(p, q-1, sz);
            p = q;
        }
        return n <= ans;
    }

    int solve(int p, int q, int sz) {
        if (p == 0 && q == sz-1) return (q-p+2)/2;
        if (p == 0 || q == sz-1) return (q-p+1)/2;
        return (q-p)/2;
    }
};

int main() {
    Solution solution;
    return 0;
}
