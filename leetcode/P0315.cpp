// https://leetcode.com/problems/count-of-smaller-numbers-after-self/#/description
// 315. Count of Smaller Numbers After Self

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> countSmaller(vector<int>& A) {
        const int N = A.size();
        vector<int> pos1(N), pos2(N);
        vector<int> tmp(N);
        vector<int> ret(N);
        iota(pos1.begin(), pos1.end(), 0);
        mergesort(A, tmp, pos1, pos2, 0, N, ret);
        return ret;
    }

    void mergesort(vector<int>& A, vector<int>& tmp,
                   vector<int>& pos1, vector<int>& pos2,
                   int lo, int hi, vector<int>& ret) {
        if (hi - lo <= 1) return;
        int mid = (lo + hi) / 2;
        mergesort(A, tmp, pos1, pos2, lo, mid, ret);
        mergesort(A, tmp, pos1, pos2, mid, hi, ret);

        int p = lo, q = mid, i = lo;
        while (p < mid && q < hi) {
            if (A[p] <= A[q]) {
                tmp[i] = A[p];
                pos2[i] = pos1[p];
                ret[pos1[p]] += q - mid;
                p++;
            } else {
                tmp[i] = A[q];
                pos2[i] = pos1[q];
                q++;
            }
            i++;
        }

        while (p < mid) {
            tmp[i] = A[p];
            pos2[i] = pos1[p];
            ret[pos1[p]] += hi - mid;
            p++;
            i++;
        }
        while (q < hi) {
            tmp[i] = A[q];
            pos2[i] = pos1[q];
            q++;
            i++;
        }

        for (i = lo; i < hi; i++) {
            A[i] = tmp[i];
            pos1[i] = pos2[i];
        }
    }
};

int main() {
    auto v = getVector();
    Solution solution;
    auto ret = solution.countSmaller(v);
    printVector(ret);
    return 0;
}
