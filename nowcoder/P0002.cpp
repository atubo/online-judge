// 二维数组中的查找

#include <bits/stdc++.h>
#include "Util.h"
using namespace std;

class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        const int M = array.size();
        if (M == 0) return false;
        const int N = array[0].size();
        if (N == 0) return false;
        int r = 0, c = N - 1;
        while (r < M && c >= 0) {
            if (array[r][c] == target) return true;
            else if (array[r][c] < target) r++;
            else c--;
        }
        return false;
    }
};

int main() {
    auto m = getMatrix();
    int target;
    cin >> target;
    Solution solution;
    cout << solution.Find(target, m) << endl;
    return 0;
}
