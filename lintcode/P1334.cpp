// https://www.lintcode.com/problem/rotate-array/description
// 1334. Rotate Array

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<int> rotate(vector<int> &nums, int k) {
        const int n = nums.size();
        if (n == 0) return nums;
        k = ((k%n) + n) % n;
        reverse(nums, 0, n);
        reverse(nums, 0, k);
        reverse(nums, k, n);
        return nums;
    }

    void reverse(vector<int> &a, int b, int e) {
        int p = b, q = e-1;
        while (p < q) {
            swap(a[p++], a[q--]);
        }
    }
};

int main() {
    Solution solution;
    return 0;
}
