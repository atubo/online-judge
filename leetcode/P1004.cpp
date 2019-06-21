// https://leetcode.com/problems/max-consecutive-ones-iii/
// 1004. Max Consecutive Ones III

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int longestOnes(vector<int> &A, int K) {
        const int n = A.size();
        if (count(A, n) <= K) return n;
        int lo = 0, hi = n;
        while (lo < hi-1) {
            int mid = (lo + hi) / 2;
            if (count(A, mid) > K) hi = mid;
            else lo = mid;
        }
        return lo;
    }
private:
    int count(const vector<int> &A, int len) {
        const int n = A.size();
        int nz = 0;
        for (int i = 0; i < len; i++) {
            nz += (A[i] == 0);
        }
        int ret = nz;
        for (int i = len; i < n; i++) {
            nz -= (A[i-len] == 0);
            nz += (A[i] == 0);
            ret = min(ret, nz);
        }
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
