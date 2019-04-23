// https://www.luogu.org/problemnew/show/P3068
// [USACO13JAN]派对邀请函Party Invitations

#include <bits/stdc++.h>
using namespace std;

using Set = unordered_set<int>;

const int MAXG = 250010;
int N, G;

int main() {
    scanf("%d%d", &N, &G);
    vector<Set> cows(N);
    vector<Set> groups(G);
    for (int i = 0; i < G; i++) {
        int s;
        scanf("%d", &s);
        for (int j = 0; j < s; j++) {
            int x;
            scanf("%d", &x);
            x--;
            groups[i].insert(x);
            cows[x].insert(i);
        }
    }

    vector<bool> inq(N, false);
    queue<int> q;
    q.push(0);
    inq[0] = true;
    for (int i = 0; i < G; i++) {
        auto &group = groups[i];
        if (group.size() == 1) {
            int x = *group.begin();
            if (!inq[x]) {
                q.push(x);
                inq[x] = true;
            }
        }
    }

    int ans = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ans++;
        for (int i: cows[u]) {
            auto &group = groups[i];
            group.erase(u);
            if (group.size() == 1) {
                int v = *group.begin();
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }
    printf("%d\n", ans);

    return 0;
}
