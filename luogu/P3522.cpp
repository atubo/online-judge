// https://www.luogu.org/problemnew/show/P3522
// [POI2011]TEM-Temperature

#include <bits/stdc++.h>
using namespace std;

struct Data {
    int l, x;
};

int N;

int main() {
    scanf("%d", &N);
    deque<Data> q;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        int lo, hi;
        scanf("%d%d", &lo, &hi);
        while (!q.empty() && q.front().l > hi) q.pop_front();
        int x = i;
        while (!q.empty() && q.back().l <= lo) {
            x = q.back().x;
            q.pop_back();
        }
        q.push_back({lo, x});
        ans = max(ans, i-q.front().x+1);
    }
    printf("%d", ans);

    return 0;
}
