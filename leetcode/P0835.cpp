// https://leetcode.com/problems/image-overlap/description/
// 835. Image Overlap

#include <bits/stdc++.h>
#include "Util.h"
using namespace std;

class Solution {
public:
    int largestOverlap(vector<vector<int>> &A, vector<vector<int>> &B) {
        const int N = A.size();
        int res = 0;
        for (int dx = -(N-1); dx <= N-1; dx++) {
            for (int dy = -(N-1); dy <= N-1; dy++) {
                res = max(res, overlap(A, B, dx, dy));
            }
        }
        return res;
    }

    int overlap(vector<vector<int>> &A, vector<vector<int>> &B, int dx, int dy) {
        const int N = A.size();
        int ans = 0;
        for (int i = max(0, -dx); i < min(N-dx, N); i++) {
            for (int j = max(0, -dy); j < min(N-dy, N); j++) {
                ans += A[i][j] & B[i+dx][j+dy];
            }
        }
        return ans;
    }
};

int main() {
    auto A = getMatrix();
    auto B = getMatrix();
    Solution solution;
    cout << solution.largestOverlap(A, B) << endl;
    return 0;
}
