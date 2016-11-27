// http://www.tyvj.cn/p/1912
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using PII = pair<int, int>;
private:
    int N;
    vector<PII> nbr;
public:
    Solution() {
        cin >> N;
        nbr.resize(N);
        for (int i = 0; i < N; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            nbr[i] = make_pair(a-1, b-1);
        }
    }

    vector<int> buildTarget() {
        vector<int> ret(N);
        ret[0] = 0;
        ret[N-1] = nbr[0].first;
        ret[1] = nbr[0].second;
        for (int i = 1; i < N; i++) {
            int left, right;
            tie(left, right) = nbr[ret[i]];
            if (left != ret[i-1]) swap(left, right);
            if (left != ret[i-1]) {
                ret.clear();
                return ret;
            }
            if (i < N-1) ret[i+1] = right;
            else if (right != ret[0]) {
                ret.clear();
                return ret;
            }
        }

        vector<int> tmp = ret;
        sort(tmp.begin(), tmp.end());
        for (int i = 0; i < N; i++) {
            if (tmp[i] != i) {
                ret.clear();
                return ret;
            }
        }
        return ret;
    }

    int calcMatch(const vector<int>& target) {
        map<int, int> count;
        for (int i = 0; i < N; i++) {
            int d = (target[i] - i + N) % N;
            count[d]++;
        }
        int ret = 0;
        for (const auto& pr: count) {
            ret = max(ret, pr.second);
        }
        return ret;
    }


    void solve() {
        vector<int> target = buildTarget();
        if (target.empty()) {
            cout << "-1" << endl;
            return;
        }

        int p = calcMatch(target);
        reverse(target.begin(), target.end());
        p = max(p, calcMatch(target));
        cout << N - p << endl;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
