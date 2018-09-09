// https://www.lintcode.com/problem/search-for-a-range/description?_from=ladder&&fromId=23
// 61. Search for a Range

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<int> searchRange(vector<int> &A, int target) {
        const int n = A.size();
        if (n == 0) return {-1, -1};
        int lo = lowerBound(A, target);
        int hi = upperBound(A, target);
        if (lo == n || A[lo] != target) return {-1, -1};
        return {lo, hi-1};
    }

    int lowerBound(const vector<int> &A, int target) {
        const int n = A.size();
        int lo = 0, hi = n-1;
        if (A[lo] >= target) return lo;
        if (A[hi] < target) return hi+1;
        while (lo < hi - 1) {
            int mid = (lo + hi) / 2;
            if (A[mid] < target) lo = mid;
            else hi = mid;
        }
        return hi;
    }

    int upperBound(const vector<int> &A, int target) {
        const int n = A.size();
        int lo = 0, hi = n-1;
        if (A[lo] > target) return lo;
        if (A[hi] <= target) return  hi+1;
        while (lo < hi - 1) {
            int mid = (lo + hi) / 2;
            if (A[mid] <= target) lo = mid;
            else hi = mid;
        }
        return hi;
    }
};

int main() {
    Solution solution;
    auto A = getVector();
    int x;
    cin >> x;
    printVector(solution.searchRange(A, x));
    return 0;
}
