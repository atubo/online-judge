// https://www.luogu.org/problemnew/show/P2168
// [NOI2015]荷马史诗

#include <bits/stdc++.h>
using namespace std;
using Tuple = tuple<int64_t, int, int>;

int K;
int maxd;
int64_t ans;

struct Node {
    vector<int> ch;
    int64_t wt;
    int ht;
    Node(int64_t weight = 0): wt(weight), ht(0) {}
} V[300010];


void dfs(int id, int d) {
    Node &v = V[id];
    if (v.ch.empty()) {
        maxd = max(maxd, d);
        ans += v.wt * d;
        return;
    }

    for (int c: v.ch) {
        dfs(c, d+1);
    }
}

int main() {
    priority_queue<Tuple, vector<Tuple>, greater<Tuple>> pq;

    int n;
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; i++) {
        int64_t w;
        scanf("%ld", &w);
        V[i].wt = w;
        pq.push(make_tuple(w, 0, i));
    }
    int idx = n+1;
    int r = n % (K-1);
    if (r != 1) {
        for (int i = 1; i <= (K-r) % (K-1); i++) {
            V[idx].wt = 0;
            pq.push(make_tuple(0, 0, idx));
            idx++;
        }
    }
    while (pq.size() > 1) {
        int cnt = 0;
        while (!pq.empty() && cnt < K) {
            int64_t wt;
            int ht, id;
            tie(wt, ht, id) = pq.top();
            pq.pop();
            V[idx].wt += wt;
            V[idx].ht = max(V[idx].ht, 1+ht);
            V[idx].ch.push_back(id);
            cnt++;
        }
        pq.push(make_tuple(V[idx].wt, V[idx].ht, idx));
        idx++;
    }

    dfs(idx-1, 0);
    printf("%ld\n", ans);
    printf("%d\n", maxd);

    return 0;
}
