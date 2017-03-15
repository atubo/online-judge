// https://www.luogu.org/problem/show?pid=2239
// 螺旋矩阵

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, I, J;
    cin >> N >> I >> J;
    int d = min(min(I, N+1-I), min(J, N+1-J));
    int s = 0;
    for (int i = 0; i < d-1; i++) {
        s += N - 1 - 2*i;
    }
    s = s * 4;
    int ret = 0;
    if (I == d) {
        ret = J - d + s;
    } else if (J == N+1-d) {
        ret = s + N + 1 - 2*d + (I - d);
    } else if (I == N+1-d) {
        ret = s + 2*N + 2 - 4*d + (N+1-d-J);
    } else {
        ret = s + 3*N + 3 - 6*d + (N+1-d-I);
    }
    cout << ret + 1 << endl;
    return 0;
}
