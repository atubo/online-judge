// https://leetcode.com/problems/3sum-smaller/#/description
// 259. 3Sum Smaller

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int threeSumSmaller(vector<int>& A, int target) {
        sort(A.begin(), A.end());
        const int N = A.size();
        int ret = 0;
        for (int i = 0; i <= N-3; i++) {
            for (int j = i+1; j <= N-2; j++) {
                int r = N-1;
                while (r >= j+1 && A[i]+A[j]+A[r] >= target) r--;
                ret += r - j;
            }
        }
        return ret;
    }
};

int main() {
    auto v = getBracketedIntVector();
    int n;
    cin >> n;
    Solution solution;
    cout << solution.threeSumSmaller(v, n) << endl;
    return 0;
}
