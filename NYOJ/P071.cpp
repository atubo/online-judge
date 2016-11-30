// http://acm.nyist.edu.cn/JudgeOnline/problem.php?pid=71
// 独木舟上的旅行
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int W, N;
    vector<int> wts;
public:
    Solution() {
        cin >> W >> N;
        wts.resize(N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &wts[i]);
        }
    }

    int pickFirst(vector<bool>& picked) {
        int u = find(picked.begin(), picked.end(), false) - picked.begin();
        picked[u] = true;
        return u;
    }

    int pickSecond(int wt, vector<bool>& picked) {
        int u = -1;
        int maxComb = 0;
        for (int i = 0; i < N; i++) {
            if (!picked[i] && (wt + wts[i] > maxComb) && (wt + wts[i] <= W)) {
                maxComb = wt + wts[i];
                u = i;
            }
        }
        if (u >= 0) picked[u] = true;
        return u;
    }

    void solve() {
        vector<bool> picked(N, false);
        int ret = 0, count = 0;
        while (count < N) {
            int u = pickFirst(picked);
            int v = pickSecond(wts[u], picked);
            count += (v >= 0 ? 2 : 1);
            ret++;
        }
        cout << ret << endl;
    }
};

int main() {
    int S;
    cin >> S;
    for (int i = 0; i < S; i++) {
        Solution solution;
        solution.solve();
    }
    return 0;
}
