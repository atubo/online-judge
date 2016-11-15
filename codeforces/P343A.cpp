// http://codeforces.com/problemset/problem/343/A

#include <iostream>

using namespace std;

int64_t solve(int64_t a, int64_t b) {
    if (a == 0 || b == 0) return 0;
    if (a > b) return a/b + solve(a%b, b);
    else return b/a + solve(a, b % a);
}

int main() {
    int64_t a, b;
    cin >> a >> b;
    cout << solve(a, b) << endl;
    return 0;
}
