// https://www.luogu.org/problem/show?pid=1060
// 开心的金明
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
typedef pair<int, int> PII;

int main() {
    int N, m;
    cin >> N >> m;
    vector<int> dpPrev(N+1, 0), dpCurr(N+1, 0);
    vector<PII> purchase(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        purchase[i] = make_pair(a, b);
    }

    for (int i = 0; i < m; i++) {
        for (int w = 0; w <= N; w++) {
            dpCurr[w] = dpPrev[w];
            int v = purchase[i].first;
            int p = purchase[i].second;
            if (w >= v) {
                dpCurr[w] = max(dpCurr[w], dpPrev[w-v] + v * p);
            }
        }
        swap(dpPrev, dpCurr);
    }
    cout << dpPrev[N] << endl;
    return 0;
}
