// https://www.luogu.org/problemnew/show/P3842
// [TJOI2007]线段

#include <bits/stdc++.h>
using namespace std;

struct Data {
    int pos, cost;
};

int calc(const Data &prev, int l, int r, int e) {
    int x = prev.pos;
    int cost = 1;
    if (e == r) {
        if (x <= l) cost += r - x;
        else cost += (x-l) + (r-l);
    } else {
        if (x >= r) cost += x - l;
        else cost += (r-x) + (r-l);
    }
    return prev.cost + cost;
}

int main() {
    int n;
    scanf("%d", &n);
    vector<Data> dp1(2), dp2(2);
    dp1[0] = dp1[1] = {1, -1};
    for (int i = 1; i <= n; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        dp2[0] = {l, min(calc(dp1[0], l, r, l),
                         calc(dp1[1], l, r, l))};
        dp2[1] = {r, min(calc(dp1[0], l, r, r),
                         calc(dp1[1], l, r, r))};
        swap(dp1, dp2);
    }
    printf("%d\n", min(dp1[0].cost+n-dp1[0].pos,
                       dp1[1].cost+n-dp1[1].pos));
    return 0;
}
