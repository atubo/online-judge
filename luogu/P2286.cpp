// https://www.luogu.org/problemnew/show/P2286
// [HNOI2004]宠物收养场

#include <bits/stdc++.h>
using namespace std;

int N;
int ret;
const int MOD = 1000000;
const int INF = 1e9;

set<int> S;

void process(int a) {
    using Iter = set<int>::iterator;
    Iter it1 = S.lower_bound(a);
    Iter it2 = it1--;
    if (a - *it1 <= *it2 - a && *it1 != -INF) {
        ret += a - *it1;
        S.erase(it1);
    } else {
        ret += *it2 - a;
        S.erase(it2);
    }
    ret %= MOD;
}

int main() {
    S.insert(-INF); S.insert(INF);
    scanf("%d", &N);
    int curr;
    for (int i = 0; i < N; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (S.size() == 2) {
            curr = a;
            S.insert(b);
        } else if (curr == a) {
            S.insert(b);
        } else {
            process(b);
        }
    }
    printf("%d\n", ret);
    return 0;
}
