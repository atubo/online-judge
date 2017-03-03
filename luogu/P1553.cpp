// https://www.luogu.org/problem/show?pid=1553
// 数字反转（升级版）

#include <bits/stdc++.h>
using namespace std;

string rev(const string& s) {
    if (s.empty()) return s;
    string ret;
    int p = s.length()-1;
    while (p >= 0 && s[p] == '0') p--;
    if (p < 0) return "0";
    while (p >= 0) ret.push_back(s[p--]);
    return ret;
}

void trim(string& s) {
    while (s.size() > 1 && s.back() == '0') s.pop_back();
}

string build(const string& s, int p) {
    string part1 = rev(s.substr(0, p));
    char c = s[p];
    string part2 = rev(s.substr(p+1));
    if (c == '.') trim(part2);
    return part1 + c + part2;
}

int main() {
    string s;
    cin >> s;
    string::size_type p = s.find_first_of("./%");
    if (p != string::npos) {
        cout << build(s, p) << endl;
    } else {
        cout << rev(s) << endl;
    }
    return 0;
}
