// https://www.luogu.org/problem/show?pid=1288
// 取数游戏II
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> C(N);
    for (int i = 0; i < N; i++) {
        cin >> C[i];
    }
    int fwd = 0;
    for (; fwd < N; fwd++) {
        if (C[fwd] == 0) break;
    }
    int bwd = 0;
    for (; bwd < N; bwd++) {
        if (C[N-1-bwd] == 0) break;
    }
    cout << (fwd & 1 || bwd & 1 ? "YES" : "NO") << endl;
    return 0;
}
