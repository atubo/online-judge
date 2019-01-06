// https://www.luogu.org/problemnew/show/P2107
// 小Z的AK计划

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+10;
int N;
int64_t M;
struct Cafe {
    int64_t x;
    int t;
    bool operator < (const Cafe &other) const {
        if (x < other.x) return true;
        if (x > other.x) return false;
        return t < other.t;
    }
} cafe[MAXN];

int solve() {
    priority_queue<int> pq;
    int64_t cap = M;
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        int64_t x = cafe[i].x - cafe[i-1].x;
        int t = cafe[i].t;
        cap -= x;
        while (cap < 0 && !pq.empty()) {
            int c = pq.top();
            pq.pop();
            cap += c;
        }
        if (cap < 0) return ans;
        if (cap >= t) {
            pq.push(t);
            cap -= t;
            ans = max(ans, (int)pq.size());
        } else if (!pq.empty()) {
            int c = pq.top();
            if (c > t) {
                pq.pop();
                pq.push(t);
                cap += c - t;
            }
        }
    }
    return ans;
}

int main() {
    scanf("%d%ld", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%ld%d", &cafe[i].x, &cafe[i].t);
    }
    sort(cafe+1, cafe+N+1);
    printf("%d\n", solve());
    return 0;
}
