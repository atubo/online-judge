// https://www.luogu.org/problemnew/show/P2622
// 关灯问题II

#include <bits/stdc++.h>
using namespace std;

int N, M;
int on[110], off[110];
bool vis[2048];

int bfs() {
    queue<pair<int, int>> q;
    int s = (1<<N) - 1;
    q.push(make_pair(s, 0));
    vis[s] = true;
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        s = p.first;
        int d = p.second;
        if (s == 0) {
            return d;
        }
        for (int i = 0; i < M; i++) {
            int t = (s | on[i]) & off[i];
            if (!vis[t]) {
                q.push(make_pair(t, d+1));
                vis[t] = true;
            }
        }
    }
    return -1;
}


int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        off[i] = (1<<N) - 1;
        for (int j = 0; j < N; j++) {
            int x;
            scanf("%d", &x);
            if (x == 1) off[i] &= ~(1<<j);
            if (x == -1) on[i] |= (1<<j);
        }
    }

    int ans = bfs();
    printf("%d", ans);

    return 0;
}
