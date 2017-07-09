// https://leetcode.com/problems/valid-triangle-number/#/description
// 611. Valid Triangle Number

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int triangleNumber(vector<int>& A) {
        sort(A.begin(), A.end());
        const int N = A.size();
        int ret = 0;
        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {
                ret += max(0, findIdx(A, A[i]+A[j]) - (j+1));
            }
        }
        return ret;
    }

    int findIdx(const vector<int>& A, int x) {
        return lower_bound(A.begin(), A.end(), x) - A.begin();
    }
};

int main() {
    auto v = getBracketedIntVector();
    Solution solution;
    cout << solution.triangleNumber(v) << endl;
    return 0;
}
