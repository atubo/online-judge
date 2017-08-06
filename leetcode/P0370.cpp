// https://leetcode.com/problems/range-addition/description/
// 370. Range Addition

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> ps(length+1);
        for (const auto& u: updates) {
            ps[u[0]] += u[2];
            ps[u[1]+1] -= u[2];
        }

        vector<int> ret(length);
        ret[0] = ps[0];
        for (int i = 1; i < length; i++) {
            ret[i] = ret[i-1] + ps[i];
        }
        return ret;
    }
};

int main() {
    return 0;
}
