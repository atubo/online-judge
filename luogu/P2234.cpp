// https://www.luogu.org/problem/show?pid=2234
// [HNOI2002]营业额统计

#include <bits/stdc++.h>
using namespace std;


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,
        tree_order_statistics_node_update> ordered_set;

int main() {
    ordered_set s;
    s.insert(-2000000);
    s.insert( 2000000);
    int N;
    scanf("%d", &N);
    int64_t ret;
    scanf("%lld", &ret);
    s.insert(ret);
    for (int i = 1; i < N; i++) {
        int x;
        scanf("%d", &x);
        int k = s.order_of_key(x);
        int y1 = *s.find_by_order(k-1);
        int y2 = *s.find_by_order(k);
        ret += min(x - y1, y2 - x);
        s.insert(x);
    }
    printf("%lld\n", ret);
    return 0;
}
