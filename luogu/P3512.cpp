// https://www.luogu.org/problemnew/show/P3512
// [POI2010]PIL-Pilots

#include <bits/stdc++.h>
using namespace std;

int N, K;

struct Data {
    int x, a;
};

int main() {
    scanf("%d%d", &K, &N);
    deque<Data> top, bot;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        int a;
        scanf("%d", &a);
        while (!top.empty() && top.front().a > a*1LL + K) top.pop_front();
        while (!bot.empty() && bot.front().a < a*1LL - K) bot.pop_front();
        int x = i;
        while (!top.empty() && top.back().a <= a) {
            x = top.back().x;
            top.pop_back();
        }
        top.push_back({x, a});
        x = i;
        while (!bot.empty() && bot.back().a >= a) {
            x = bot.back().x;
            bot.pop_back();
        }
        bot.push_back({x, a});
        ans = max(ans, i-max(top.front().x, bot.front().x)+1);
    }
    printf("%d\n", ans);
    return 0;
}
