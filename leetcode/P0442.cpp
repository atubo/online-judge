// https://leetcode.com/problems/find-all-duplicates-in-an-array/#/description
// 442. Find All Duplicates in an Array

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findDuplicates(vector<int>& A) {
        const int N = A.size();
        for (int i = 0; i < N; i++) {
            A[i]--;
        }
        vector<int> ret;
        for (int i = 0; i < N; i++) {
            while (A[i] > -1 && A[i] != i && A[A[i]] != A[i]) {
                swap(A[i], A[A[i]]);
            }
            if (A[i] > -1 && A[i] != i) {
                ret.push_back(A[i]+1);
                A[i] = -1;
            }
        }
        return ret;
    }
};

int main() {
    auto A = getBracketedIntVector();
    Solution solution;
    auto v = solution.findDuplicates(A);
    printVector(v);
    return 0;
}
