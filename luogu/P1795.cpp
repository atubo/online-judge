// https://www.luogu.org/problem/show?pid=1795
// 无穷的序列_NOI导刊2010提高（05）

#include <bits/stdc++.h>
using namespace std;

bool isSq(int64_t x) {
    int64_t s = sqrt(x);
    return x == s * s;
}

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        printf("%d\n", (isSq(8L*x-7) ? 1:0));
    }
    return 0;
}
