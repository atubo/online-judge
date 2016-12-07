// https://www.luogu.org/problem/show?pid=2161
// [SHOI2009]Booking 会场预约
#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
typedef tree<int, int, less<int>, rb_tree_tag,
        tree_order_statistics_node_update> ordered_set;

void remove(ordered_set& s, int p, int q) {
    ordered_set::iterator it = s.find_by_order(p);
    for (int i = 0; i < q-p; i++) {
        it = s.erase(it);
    }
}

int main() {
    int N;
    scanf("%d", &N);
    ordered_set right, left;
    char str[10];
    int a, b;
    for (int i = 0; i < N; i++) {
        scanf("%s %d %d", str, &a, &b);
        if (str[0] == 'A') {
            int l = right.order_of_key(a);
            int r = left.order_of_key(b+1);
            printf("%d\n", r-l);
            remove(left, l, r);
            remove(right, l, r);
            left.insert(make_pair(a, 0));
            right.insert(make_pair(b, 0));
        } else {
            printf("%d\n", left.size());
        }
    }

    return 0;
}
