// http://codeforces.com/problemset/problem/610/A

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    cout << (N & 1 ? 0 : max(0, (N - 2) / 4)) << endl;
    return 0;
}
