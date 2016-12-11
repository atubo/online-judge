// https://www.luogu.org/problem/show?pid=1087
// FBI树
#include <iostream>
#include <vector>
using namespace std;

char solve(int p, const string& s, string& ans) {
    const int N = s.length();
    if (2*p >= 2*N) {
        char c = s[p-N];
        ans.push_back(c == '0' ? 'B' : 'I');
    } else {
        char l = solve(2*p, s, ans);
        char r = solve(2*p+1, s, ans);
        if (l == r) {
            ans.push_back(l);
        } else {
            ans.push_back('F');
        }
    }
    return *ans.rbegin();
}

int main() {
    int N;
    string s;
    cin >> N;
    cin >> s;
    string ans;
    solve(1, s, ans);
    cout << ans << endl;
    return 0;
}
