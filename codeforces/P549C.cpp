// http://codeforces.com/problemset/problem/549/C
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int N, K;
    int odd, even;
public:
    Solution() {
        cin >> N >> K;
        odd = 0, even = 0;
        for (int i = 0; i < N; i++) {
            int a;
            scanf("%d", &a);
            if (a & 1) odd++;
            else even++;
        }
    }

    void solve() {
        bool stannis;
        int d = (N - K) / 2;
        if ((N - K) % 2 == 0) {
            if (K % 2 == 0) {
                if (N == K) stannis = (odd & 1);
                else stannis = false;
            } else {
                if (N == K) stannis = (odd & 1);
                else {
                    stannis = (even <= d);
                }
            }
        } else {
            if (K % 2 == 1) {
                stannis = (odd > d);
            } else {
                stannis = (odd > d && odd < N - d);
            }
        }
        cout << (stannis ? "Stannis" : "Daenerys") << endl;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
