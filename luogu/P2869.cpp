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

struct Taste {
    int taste;
    int type;
    int index;

    bool operator < (const Taste &other) const {
        if (taste > other.taste) return true;
        if (taste < other.taste) return false;
        return (type > other.type);
    }
};

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    vector<PII> cow(N);
    vector<PII> grass(M);
    vector<Taste> taste(N+M);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &cow[i].first, &cow[i].second);
        taste[i].taste = cow[i].second;
        taste[i].type = 0;
        taste[i].index =i;
    }
    for (int i = 0; i < M; i++) {
        scanf("%d%d", &grass[i].first, &grass[i].second);
        taste[N+i].taste = grass[i].second;
        taste[N+i].type = 1;
        taste[N+i].index = i;
    }

    sort(taste.begin(), taste.end());

    int64_t ret = 0;
    ordered_map price;
    for (const auto &t: taste) {
        int type = t.type;
        int index = t.index;
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
