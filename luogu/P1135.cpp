// https://www.luogu.org/problem/show?pid=1135
// 奇怪的电梯

#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;

bool visited[210];
int N, A, B;
int K[210];

int main() {
    scanf("%d %d %d", &N, &A, &B);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &K[i]);
    }

    queue<PII> q;
    q.push(make_pair(A, 0));
    visited[A] = true;
    int ans = -1;
    while (!q.empty()) {
        int u = q.front().first;
        int d = q.front().second;
        q.pop();
        if (u == B) {
            ans = d;
            break;
        }
        for (int s = -1; s <= 1; s += 2) {
            int v = u + s * K[u];
            if (v <= 0 || v > N) continue;
            if (!visited[v]) {
                q.push(make_pair(v, d+1));
                visited[v] = true;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
