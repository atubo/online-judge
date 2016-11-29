// http://codeforces.com/problemset/problem/567/D
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int N, K, A;
    int M;
    vector<int> X;
public:
    Solution() {
        cin >> N >> K >> A;
        cin >> M;
        X.resize(M);
        for (int i = 0; i < M; i++) {
            scanf("%d", &X[i]);
            X[i]--;
        }
    }

    void solve() {
        cout << firstCheat() << endl;
    }

    int countShips(int x) {
        return (x + 1) / (A + 1);
    }

    bool isLegit(int len) {
        assert(len > 0);
        vector<int> shots(len);
        copy(X.begin(), X.begin() + len, shots.begin());
        sort(shots.begin(), shots.end());
        int count = 0;
        int p = -1;
        for (int q: shots) {
            count += countShips(q - p - 1);
            p = q;
        }
        count += countShips(N - p - 1);
        return count >= K;
    }

    int firstCheat() {
        if (isLegit(M)) return -1;
        int lo = 0;
        int hi = M;
        while (lo < hi - 1) {
            int mid = (lo + hi) / 2;
            if (isLegit(mid)) lo = mid;
            else hi = mid;
        }
        return hi;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
