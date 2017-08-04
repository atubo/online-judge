// https://leetcode.com/problems/sort-transformed-array/description/
// 360. Sort Transformed Array

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> sortTransformedArray(vector<int>& A, int a, int b, int c) {
        vector<int> ret;
        const int N = A.size();
        if (a == 0) {
            for (int x: A) {
                ret.push_back(f(x, a, b, c));
            }
            if (b < 0) reverse(ret.begin(), ret.end());
            return ret;
        }

        double mid = - (double)b/(2*a);
        int p = N - 1;
        for (; p >= 0; p--) {
            if (A[p] < mid) break;
        }
        int q = p + 1;
        while (p >= 0 && q < N) {
            if (mid - A[p] < A[q] - mid) {
                ret.push_back(f(A[p--], a, b, c));
            } else {
                ret.push_back(f(A[q++], a, b, c));
            }
        }
        while (p >= 0) ret.push_back(f(A[p--], a, b, c));
        while (q < N) ret.push_back(f(A[q++], a, b, c));
        if (a < 0) reverse(ret.begin(), ret.end());
        return ret;
    }

    int f(int x, int a, int b, int c) {
        return a*x*x + b*x + c;
    }
};

int main() {
    return 0;
}
