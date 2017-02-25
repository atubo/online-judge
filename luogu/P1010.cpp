// https://www.luogu.org/problem/show?pid=1010
// 幂次方

#include <bits/stdc++.h>
using namespace std;

string pwr(int n) {
    vector<string> items;
    if (n & 1) {
        items.push_back("2(0)");
        n = n - 1;
    }
    if (n & 2) {
        items.push_back("2");
        n = n - 2;
    }
    for (int s = 2; s <= 20; s++) {
        if (n == 0) break;
        int d = (1 << s);
        if (n & d) {
            items.push_back("2(" + pwr(s) + ")");
            n = n - d;
        }
    }
    string ret;
    for (int i = (int)items.size()-1; i >= 0; i--) {
        if (i < (int)items.size()-1) ret += "+";
        ret += items[i];
    }
    return ret;
}

int main() {
    int n;
    cin >> n;
    cout << pwr(n) << endl;
    return 0;
}
