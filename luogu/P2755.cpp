// https://www.luogu.org/problem/show?pid=2755
// 洗牌问题

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    N = N * 2;
    int p = 1;
    int ret = 0;
    do {
        p <<= 1;
        if (p >= N+1) p -= (N+1);
        ret++;
    } while (p != 1);
    cout << ret << endl;
    return 0;
}
