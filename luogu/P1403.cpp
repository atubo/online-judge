// https://www.luogu.org/problem/show?pid=1403
// P1403 [AHOI2005]约数研究

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> f(N+1);
    int total = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j += i) {
            f[i]++;
        }
        total += f[i];
    }
    cout << total << endl;
    return 0;
}
