// https://www.luogu.org/problem/show?pid=2968
// [USACO09DEC]雪橇Bobsledding

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using PQ = __gnu_pbds::priority_queue<PII, greater<PII>>;

int main() {
    int L, N;
    scanf("%d%d", &L, &N);
    vector<PII> turns(N+1);
    turns[0] = make_pair(0, 1);
    for (int i = 1; i <= N; i++) {
        int t, s;
        scanf("%d%d", &t, &s);
        turns[i] = make_pair(t, s);
    }
    sort(turns.begin(), turns.end());

    PQ pq;

    vector<PQ::point_iterator> pointers(N+1);
    for (int i= 0; i <= N; i++) {
        pointers[i] = pq.push(make_pair(turns[i].second, i));
    }

    vector<bool> valid(N+1, true);

    while (!pq.empty()) {
        const PII &pr = pq.top();
        int p = pr.second, s = pr.first;
        pq.pop();
        valid[p] = false;
        if (p > 0 && valid[p-1]) {
            turns[p-1].second = min(turns[p-1].second,
                                    s + turns[p].first - turns[p-1].first);
            pq.modify(pointers[p-1], make_pair(turns[p-1].second, p-1));
        }
        if (p < N && valid[p+1]) {
            turns[p+1].second = min(turns[p+1].second,
                                    s + turns[p+1].first - turns[p].first);
            pq.modify(pointers[p+1], make_pair(turns[p+1].second, p+1));
        }
    }

    int ret = 0;
    for (int i = 0; i <= N-1; i++) {
        int x1, y1, x2, y2;
        tie(x1, y1) = turns[i];
        tie(x2, y2) = turns[i+1];
        int y = y1 + (y2 - y1 + x2 - x1)/2;
        ret = max(ret, y);
    }

    ret = max(ret, turns[N].second + L - turns[N].first);
    printf("%d\n", ret);
    return 0;
}
