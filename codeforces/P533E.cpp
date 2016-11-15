// http://codeforces.com/problemset/problem/533/E
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;
    string S, T;
    cin >> S >> T;
    int i = 0;
    while (S[i] == T[i]) i++;
    int j = N - 1;
    while (S[j] == T[j]) j--;
    int ret = 0;
    if (S.substr(i, j-i) == T.substr(i+1, j-i)) ret++;
    if (T.substr(i, j-i) == S.substr(i+1, j-i)) ret++;
    cout << ret << endl;
    return 0;
}
