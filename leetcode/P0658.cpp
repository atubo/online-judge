// https://leetcode.com/problems/find-k-closest-elements/
// 658. Find K Closest Elements

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<int> findClosestElements(vector<int> &arr, int k, int x) {
        const int n = arr.size();
        int p = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        int q = p - 1;
        while (q >= 0 && p < n && (p-q-1) < k) {
            if (arr[p] - x < x - arr[q]) p++;
            else q--;
        }
        if (q == -1) p = k;
        else if (p == n) q = n-1-k;
        vector<int> ret;
        for (int i = q+1; i < p; i++) {
            ret.push_back(arr[i]);
        }
        return ret;
    }
};

int main() {
    Solution solution;
    auto v = getBracketedIntVector();
    int k, x;
    cin >> k >> x;
    auto ret = solution.findClosestElements(v, k, x);
    for (int r: ret) {
        printf("%d ", r);
    }
    printf("\n");
    return 0;
}
