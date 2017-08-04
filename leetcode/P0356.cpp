// https://leetcode.com/problems/line-reflection/description/
// 356. Line Reflection

#include <bits/stdc++.h>
using namespace std;

class Solution {
    using PII = pair<int, int>;
public:
    bool isReflected(vector<PII>& pts) {
        map<int, vector<int>> byX;
        int minx = INT_MAX, maxx = INT_MIN;
        for (const auto& pt: pts) {
            byX[pt.first].push_back(pt.second);
            minx = min(minx, pt.first);
            maxx = max(maxx, pt.first);
        }
        for (auto it = byX.begin(); it != byX.end(); it++) {
            vector<int>& v = it->second;
            sort(v.begin(), v.end());
            v.erase(unique(v.begin(), v.end()), v.end());
        }

        int ps = minx + maxx;
        bool ret = true;
        for (auto it = byX.begin(); it != byX.end(); it++) {
            int x1 = it->first;
            int x2 = ps - x1;
            if (x1 == x2) continue;
            if (byX.count(x2) == 0 || byX[x1] != byX[x2]) {
                ret = false;
                break;
            }
        }
        return ret;
    }
};

int main() {
    return 0;
}
