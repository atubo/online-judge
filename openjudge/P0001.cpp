// http://nnsznoi.openjudge.cn/greedy/0014/
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    typedef pair<int, int> PII;
    typedef set<int, greater<int> >::iterator Iter;
    int N;
    cin >> N;
    vector<PII> tasks(N);
    set<int, greater<int> > slots;
    int d, w;
    for (int i = 0; i < N; i++) {
        cin >> d >> w;
        tasks[i] = make_pair(w, d);
        slots.insert(i+1);
    }
    sort(tasks.begin(), tasks.end(), greater<PII>());
    int ans = 0;
    for (int i = 0; i < N; i++) {
        w = tasks[i].first;
        d = tasks[i].second;
        Iter it = slots.lower_bound(d);
        if (it == slots.end()) {
            ans += w;
            slots.erase(slots.begin());
        } else {
            slots.erase(it);
        }
    }
    cout << ans << endl;
    return 0;
}
