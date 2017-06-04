// https://www.luogu.org/problem/show?pid=2869
// [USACO07DEC]美食的食草动物Gourmet Grazers

#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;
using TIII = tuple<int, int, int>;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<int, int, less<int>, rb_tree_tag,
        tree_order_statistics_node_update> ordered_map;

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    vector<PII> cow(N);
    vector<PII> grass(M);
    vector<TIII> taste(N+M);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &cow[i].first, &cow[i].second);
        taste[i] = make_tuple(cow[i].second, 0, i);
    }
    for (int i = 0; i < M; i++) {
        scanf("%d%d", &grass[i].first, &grass[i].second);
        taste[N+i] = make_tuple(grass[i].second, 1, i);
    }

    sort(taste.begin(), taste.end(), greater<TIII>());

    int64_t ret = 0;
    ordered_map price;
    for (const TIII &t: taste) {
        int type, index;
        tie(ignore, type, index) = t;
        if (type == 1) {
            int p = grass[index].first;
            auto it = price.find(p);
            if (it == price.end()) {
                price[p] = 1;
            } else {
                it->second++;
            }
        } else {
            int p = cow[index].first;
            auto it = price.lower_bound(p);
            if (it == price.end()) {
                printf("-1\n");
                return 0;
            }
            ret += it->first;
            if (--it->second == 0) price.erase(it);
        }
    }

    printf("%lld\n", ret);

    return 0;
}
