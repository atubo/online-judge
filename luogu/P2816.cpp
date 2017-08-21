// https://www.luogu.org/problem/show?pid=2816
// 宋荣子搭积木

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    scanf("%d", &N);
    multiset<int> s;
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        s.insert(x);
    }

    int ret =  0;
    while (!s.empty()) {
        ret++;
        int cnt = 0;
        auto it = s.begin();
        cnt++;
        s.erase(it);
        while ((it = s.lower_bound(cnt)) != s.end()) {
            cnt++;
            s.erase(it);
        }
    }
    printf("%d\n", ret);
    return 0;
}
