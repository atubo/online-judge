// https://www.luogu.org/problem/show?pid=1030
// 求先序排列
#include <cassert>
#include <iostream>
using namespace std;

void solve(const string& in, const string& post,
           int i, int j, int p, int q,
           string& ans) {
    assert(j-i == q-p);
    if (j < i) return;
    if (i == j) {
        ans.push_back(in[i]);
        return;
    }

    char c = post[q];
    ans.push_back(c);
    int k;
    for (k = i; k <= j; k++) {
        if (in[k] == c) break;
    }
    solve(in, post, i, k-1, p, p+k-1-i, ans);
    solve(in, post, k+1, j, p+k-i, q-1, ans);
}

int main() {
    string in, post;
    cin >> in >> post;
    int N = in.length();
    string ans;
    solve(in, post, 0, N-1, 0, N-1, ans);
    cout << ans << endl;
    return 0;
}
