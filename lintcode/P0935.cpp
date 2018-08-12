// https://www.lintcode.com/problem/cartesian-product/description
// 935. Cartesian Product

#include <bits/stdc++.h>
using namespace std;

#include "../utils/Util.h"

class Solution {
public:
    vector<vector<int>> getSet(vector<vector<int>> &setList) {
        vector<vector<int>> ret;
        ret.push_back(vector<int>());
        dfs(setList, 0, ret);
        return ret;
    }

private:
    void dfs(const vector<vector<int>> &setList, int depth,
             vector<vector<int>> &ret) {
        if (depth == (int)setList.size()) return;
        vector<vector<int>> tmp;
        for (int x: setList[depth]) {
            for (auto v: ret) {
                v.push_back(x);
                tmp.push_back(v);
            }
        }
        ret.swap(tmp);
        dfs(setList, depth+1, ret);
    }
};

int main() {
    int n;
    cin >> n;
    vector<vector<int>> setList(n);
    for (int i = 0; i < n; i++) {
        setList[i] = getVector();
    }
    Solution solution;
    auto ret = solution.getSet(setList);
    for (auto v: ret) {
        printVector(v);
    }
    return 0;
}

