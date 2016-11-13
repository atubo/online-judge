// http://codeforces.com/problemset/problem/388/C
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int N;
    vector<vector<int>> piles;
public:
    Solution() {
        cin >> N;
        piles.resize(N);
        for (int i = 0; i < N; i++) {
            int s;
            cin >> s;
            piles[i].resize(s);
            for (int j = 0; j < s; j++) {
                cin >> piles[i][j];
            }
        }
    }

    void solve() {
        int ciel = 0, jiro = 0;
        vector<int> oddPileIndices;
        for (int i = 0; i < N; i++) {
            auto mid = piles[i].begin() + piles[i].size()/2;
            if (piles[i].size() % 2 == 0) {
                ciel += accumulate(piles[i].begin(), mid, 0);
                jiro += accumulate(mid, piles[i].end(), 0);
            } else {
                ciel += accumulate(piles[i].begin(), mid, 0);
                jiro += accumulate(mid + 1, piles[i].end(), 0);
                oddPileIndices.push_back(i);
            }
        }
        auto f = [this](int i, int j) {
            return piles[i][piles[i].size()/2] > piles[j][piles[j].size()/2];
        };
        sort(oddPileIndices.begin(), oddPileIndices.end(), f);
        for (int p = 0; p < (int)oddPileIndices.size(); p++) {
            int i = oddPileIndices[p];
            if (p % 2 == 0) {
                ciel += piles[i][piles[i].size()/2];
            } else {
                jiro += piles[i][piles[i].size()/2];
            }
        }
        printf("%d %d\n", ciel, jiro);
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
