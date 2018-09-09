// https://www.lintcode.com/problem/search-in-rotated-sorted-array/description?_from=ladder&&fromId=23
// 62. Search in Rotated Sorted Array

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int search(vector<int> &A, int target) {
        if (A.empty()) return -1;
        int pivot = searchPivot(A);
        return searchTarget(A, pivot, target);
    }

    int searchPivot(const vector<int> &A) {
        const int n = A.size();
        if (A[0] < A[n-1]) return 0;
        int lo = 0, hi = n-1;
        while (lo < hi - 1) {
            int mid = (lo + hi) / 2;
            if (A[mid] > A[n-1]) lo = mid;
            else hi = mid;
        }
        return hi;
    }

    int searchTarget(const vector<int> &A, int pivot, int target) {
        const int n = A.size();
        int ret = binarySearch(A, pivot, n, target);
        if (ret != -1) return ret;
        ret = binarySearch(A, 0, pivot, target);
        return ret;
    }

    int binarySearch(const vector<int> &A, int b, int e, int target) {
        if (b == e) return -1;
        if (target < A[b] || target > A[e-1]) return -1;
        if (target == A[e-1]) return e-1;
        int lo = b, hi = e-1;
        while (lo < hi - 1) {
            int mid = (lo + hi) / 2;
            if (A[mid] <= target) lo = mid;
            else hi = mid;
        }
        return A[lo] == target ? lo : -1;
    }
};

int main() {
    Solution solution;
    auto A = getVector();
    int x;
    cin >> x;
    cout << solution.search(A, x) << endl;
    return 0;
}
