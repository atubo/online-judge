// https://www.luogu.org/problemnew/show/P1214
// [USACO1.4]等差数列 Arithmetic Progressions

#include <bits/stdc++.h>
using namespace std;

int N, M;
bool A[125010];
int main() {
    scanf("%d%d", &N, &M);
    vector<int> ds;
    for (int i = 0; i <= M; i++) {
        for (int j = 0; j <= M; j++) {
            ds.push_back(i*i+j*j);
        }
    }
    sort(ds.begin(), ds.end());
    ds.erase(unique(ds.begin(), ds.end()), ds.end());
    for (int x: ds) {
        A[x] = true;
    }

    vector<pair<int, int>> ans;
    for (int i = 0; i < (int)ds.size()-1; i++) {
        for (int j = i+1; j < (int)ds.size(); j++) {
            int a0 = ds[i], a1 = ds[j];
            int d = a1 - a0;
            if (a0 + (N-1)*d > 2*M*M) break;
            bool ok = true;
            for (int k = N-1; k > 1; k--) {
                if (!A[a0+k*d]) {
                    ok = false;
                    break;
                }
            }
            if (ok) ans.push_back(make_pair(d, a0));
        }
    }

    if (ans.empty()) {
        printf("NONE\n");
        return 0;
    }
    sort(ans.begin(), ans.end());
    for (auto p: ans) {
        printf("%d %d\n", p.second, p.first);
    }

    return 0;
}
