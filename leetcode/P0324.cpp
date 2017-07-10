// https://leetcode.com/problems/wiggle-sort-ii/#/description
// 324. Wiggle Sort II

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void wiggleSort(vector<int>& A) {
        const int N = A.size();
        int median = find(A, 0, N, N/2);
        part3(A, median);
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

    void part3(vector<int>& A, int pivot) {
        const int N = A.size();
        int lt = 0, gt = N-1, i = 0;
        auto f = [N](int j) {
            if (N&1) return (2*j+1)%N;
            else return 2*j+1 < N ? 2*j+1: (2*j)%N;
        };
        while (i <= gt) {
            if (A[f(i)] > pivot) {
                swap(A[f(lt)], A[f(i)]);
                lt++;
                i++;
            } else if (A[f(i)] < pivot) {
                swap(A[f(gt)], A[f(i)]);
                gt--;
            } else {
                i++;
            }
        }
    }
};

int main() {
    auto v = getBracketedIntVector();
    Solution solution;
    solution.wiggleSort(v);
    printVector(v);
    return 0;
}
