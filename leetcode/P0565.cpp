// https://leetcode.com/problems/array-nesting/#/description
// 565. Array Nesting

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int arrayNesting(vector<int>& A) {
        const int N = A.size();
        if (N == 0) return 0;
        vector<bool> visited(N);
        int ret = 0;
        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                ret = max(ret, trace(A, i, visited));
            }
        }
        return ret;
    }

    int trace(const vector<int>& A, int s, vector<bool>& visited) {
        int ret = 1;
        visited[s] = true;
        while (!visited[A[s]]) {
            s = A[s];
            visited[s] = true;
            ret++;
        }
        return ret;
    }
};

int main() {
    auto v = getBracketedIntVector();
    Solution solution;
    cout << solution.arrayNesting(v) << endl;
    return 0;
}
