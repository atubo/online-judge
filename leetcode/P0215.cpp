// https://leetcode.com/problems/kth-largest-element-in-an-array/#/description
// 215. Kth Largest Element in an Array

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& A, int k) {
        const int N = A.size();
        k = N - k;
        return find(A, 0, N, k);
    }

    int find(vector<int>& A, int lo, int hi, int k) {
        if (lo == hi - 1) return A[lo];
        int v = A[lo];
        int lt = lo, gt = hi-1, i = lo;
        while (i <= gt) {
            if (A[i] < v) {
                swap(A[lt], A[i]);
                lt++;
                i++;
            } else if (A[i] > v) {
                swap(A[gt], A[i]);
                gt--;
            } else {
                i++;
            }
        }
        if (k < lt - lo) return find(A, lo, lt, k);
        else if (k <= gt - lo) return v;
        else return find(A, gt+1, hi, k-gt+lo-1);
    }
};

int main() {
    auto v = getVector();
    int k;
    cin >> k;
    Solution solution;
    cout << solution.findKthLargest(v, k) << endl;
    return 0;
}
