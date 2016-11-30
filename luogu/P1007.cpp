// https://www.luogu.org/problem/show?pid=1007
// 独木桥
#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

int main() {
    int L, N;
    cin >> L >> N;
    int mintime = 0, maxtime = 0;
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        mintime = max(mintime, min(x, L+1-x));
        maxtime = max(maxtime, max(x, L+1-x));
    }
    printf("%d %d\n", mintime, maxtime);
    return 0;
}
