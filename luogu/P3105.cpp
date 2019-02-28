// https://www.luogu.org/problemnew/show/P3105
// [USACO14OPEN]公平的摄影Fair Photography

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N;
int ans;

struct Datum {
    int cnt, idx;
    bool operator < (const Datum &other) const {
        if (cnt != other.cnt) return cnt > other.cnt;
        return idx < other.idx;
    }
};

struct Cow {
    int pos, color;
    bool operator < (const Cow &other) const {
        return pos < other.pos;
    }
} cows[MAXN];

void solve(vector<Datum> &data, int cnt, int idx) {
    auto it = lower_bound(data.begin(), data.end(), Datum{cnt, -1});
    if (it != data.end()) {
        ans = max(ans, cows[idx].pos - cows[it->idx+1].pos);
    }
    if (data.empty() || cnt < data.back().cnt) {
        data.push_back({cnt, idx});
    }
}

int main() {
    scanf("%d", &N);
    char color[10];
    for (int i = 1; i <= N; i++) {
        int x;
        scanf("%d%s", &x, color);
        if (color[0] == 'S') cows[i] = {x, -1};
        else cows[i] = {x, 1};
    }
    sort(cows+1, cows+N+1);

    vector<Datum> odd, even;
    even.push_back({0, 0});
    int cnt = 0;
    for (int i = 1; i <= N; i++) {
        cnt += cows[i].color;
        if (cnt & 1) solve(odd, cnt, i);
        else solve(even, cnt, i);
    }
    printf("%d", ans);

    return 0;
}
