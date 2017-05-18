// https://www.luogu.org/problem/show?pid=2781
// 传教

#include <bits/stdc++.h>
using namespace std;

int64_t count(const map<int, int> &op, int l, int r) {
    map<int, int>::const_iterator it = op.begin();
    int64_t x = 0;
    while (it != op.end() && it->first <= l) {
        x += it->second;
        ++it;
    }
    int64_t ret = 0;
    int prev = l;
    while (it != op.end() && it->first < r) {
        ret += x * (it->first - prev);
        x += it->second;
        prev = it->first;
        ++it;
    }
    ret += x * (r - prev + 1);
    if (it != op.end() && it->first == r) {
        ret += it->second;
    }
    return ret;
}


int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    map<int, int> op;
    for (int i = 0; i < M; i++) {
        int t, l, r, k;
        scanf("%d%d%d", &t, &l, &r);
        if (t == 1) {
            scanf("%d", &k);
            op[l] += k;
            op[r+1] -= k;
        } else {
            printf("%lld\n", count(op, l, r));
        }
    }
    return 0;
}
