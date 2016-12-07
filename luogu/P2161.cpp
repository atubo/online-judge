// https://www.luogu.org/problem/show?pid=2161
// [SHOI2009]Booking 会场预约
#include <limits.h>
#include <cstdio>
#include <set>
#include <utility>
using namespace std;
typedef pair<int, int> PII;
typedef set<PII>::iterator Iter;

int main() {
    int N;
    scanf("%d", &N);
    set<PII> segs;
    char str[10];
    int a, b;
    for (int i = 0; i < N; i++) {
        scanf("%s", str);
        if (str[0] == 'A') {
            scanf("%d %d", &a, &b);
            Iter it = segs.lower_bound(make_pair(a, INT_MIN));
            int cnt = 0;
            while (it != segs.end()) {
                if (it->second > b) break;
                cnt++;
                segs.erase(it++);
            }
            segs.insert(make_pair(b, a));
            printf("%d\n", cnt);
        } else {
            printf("%d\n", segs.size());
        }
    }

    return 0;
}
