// https://www.luogu.org/problem/show?pid=2869
// [USACO07DEC]美食的食草动物Gourmet Grazers

#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;
using TIII = tuple<int, int, int>;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<PII, null_type, less<PII>, rb_tree_tag,
        tree_order_statistics_node_update> ordered_set;

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
    ordered_set price;
    int counter = 0;
    for (const TIII &t: taste) {
        counter++;
        int type, index;
        tie(ignore, type, index) = t;
        if (type == 1) {
            price.insert(make_pair(grass[index].first, counter));
        } else {
            int order = price.order_of_key(make_pair(cow[index].first, 0));
            if (order == (int)price.size()) {
                printf("-1\n");
                return 0;
            }
            auto it = price.find_by_order(order);
            ret += it->first;
            price.erase(it);
        }
    }

    printf("%lld\n", ret);

    return 0;
}
