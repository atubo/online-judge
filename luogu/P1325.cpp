// https://www.luogu.org/problem/show?pid=1325
// 雷达安装

#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;
using Pt = tuple<double, int, int>; // pos, type, id

int main() {
    int N, D;
    scanf("%d%d", &N, &D);
    vector<Pt> A;
    vector<bool> done(N);
    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (y > D) {
            printf("-1\n");
            return 0;
        }
        double d = sqrt((double)D * D - y * y);
        double x1 = x - d, x2 = x + d;
        A.push_back(make_tuple(x1, 0, i));
        A.push_back(make_tuple(x2, 1, i));
    }

    sort(A.begin(), A.end());

    int ans = 0;
    bool open = false;
    vector<int> opened;
    for (const Pt& p: A) {
        double x;
        int type, id;
        tie(x, type, id) = p;
        if (type == 0) {
            if (!open) {
                open = true;
                assert(opened.empty());
            }
            opened.push_back(id);
        } else {
            if (!done[id]) {
                assert(open && !opened.empty());
                ans++;
                for (int q: opened) {
                    done[q] = true;
                }
                opened.clear();
                open = false;
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}
