// https://www.luogu.org/problem/show?pid=2320
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

void solve(int x, int n, vector<int>& ans) {
    if (n == 0) {
        assert(x == 1);
        ans.push_back(1);
        return;
    }

    int i = x - (1 << n);
    ans.push_back((i+1)/2 + (1 << (n-1)));
    solve((1 << (n-1)) + i/2, n-1, ans);
}

int main() {
    int m;
    cin >> m;
    vector<int> ans;
    int n;
    for (n = 31; n >= 0; n--) {
        if ((m >> n) > 0) {
            break;
        }
    }
    solve(m, n, ans);
    cout << n+1 << endl;
    for (int i = (int)ans.size()-1; i >= 0; i--) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
