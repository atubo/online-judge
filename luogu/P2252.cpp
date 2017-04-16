// https://www.luogu.org/problem/show?pid=2252
// 取石子游戏

#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    if (a > b) swap(a, b);
    int d = b - a;
    int ret = (a != int(d * (1 + sqrt(5.0)) / 2));
    printf("%d\n", ret);
    return 0;
}
