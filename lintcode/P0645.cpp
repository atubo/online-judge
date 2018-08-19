// https://www.lintcode.com/problem/find-the-celebrity/description
// 645. Find the Celebrity

#include <bits/stdc++.h>
using namespace std;

bool knows(int a, int b) {
    return false;
}

class Solution  {
public:
    int findCelebrity(int n) {
        vector<int> candidates(n);
        iota(candidates.begin(), candidates.end(), 0);
        while (candidates.size() > 1) {
            vector<int> tmp;
            for (int i = 0; i < (int)candidates.size()-1; i += 2) {
                int a = candidates[i], b = candidates[i+1];
                bool ab = knows(a, b);
                bool ba = knows(b, a);
                if (ab && !ba) tmp.push_back(b);
                if (!ab && ba) tmp.push_back(a);
            }
            if (candidates.size() & 1) tmp.push_back(candidates.back());
            candidates.swap(tmp);
        }
        if (candidates.empty()) return -1;
        int u = candidates[0];
        for (int i = 0; i < n; i++) {
            if (i == u) continue;
            if (knows(u, i) || !knows(i, u)) return -1;
        }
        return u;
    }
};

int main() {
    return 0;
}

