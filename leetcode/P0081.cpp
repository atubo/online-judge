// https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
// 81. Search in Rotated Sorted Array II

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        if (nums.empty()) return false;
        int pivot = search_pivot(nums, 0, nums.size()-1);
        return search(nums, pivot, target);
    }

    int search_pivot(const vector<int> &A, int l, int r) {
        if (A[l] == A[r]) return linear_search(A, l, r);
        if (l >= r-1) return (A[l] < A[r] ? l : r);
        if (A[l] < A[r]) return l;
        int mid = (l + r) / 2;
        if (A[mid] >= A[l]) return search_pivot(A, mid+1, r);
        return search_pivot(A, l, mid);
    }

    bool search(const vector<int> &A, int pivot, int target) {
        const int n = A.size();
        int l = 0, r = n-1;
        if (A[l+pivot] == target || A[(r+pivot)%n] == target) return true;
        if (A[l+pivot] > target || A[(r+pivot)%n] < target) return false;
        while (l < r-1) {
            int mid = (l + r) / 2;
            int x = A[(mid+pivot)%n];
            if (x == target) return true;
            if (x > target) r = mid;
            else l = mid;
        }
        return false;
    }

    int linear_search(const vector<int> &A, int l, int r) {
        for (int i = l+1; i <= r; i++) {
            if (A[i] < A[i-1]) return i;
        }
        return l;
    }
};

int main() {
    Solution solution;
    return 0;
}
