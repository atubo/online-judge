// https://www.luogu.org/problemnew/show/P2761
// 软件补丁问题

#include <bits/stdc++.h>
using namespace std;

const int MAXN = (1<<20);
const int MAXM = 110;
int N, M;
int dist[MAXN], inq[MAXN];
unsigned int BM[MAXM], B[MAXM], F1[MAXM], F2[MAXM];
int T[MAXM];

int spfa() {
    memset(dist, 0x7F, sizeof(dist));
    const int src = (1<<N) - 1;
    const int dst = 0;
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    inq[src]++;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u]--;

        for (int i = 0; i < M; i++) {
            if ((u & BM[i]) != B[i]) continue;
            int v = (u | F2[i]) & (~F1[i]);
            if (dist[v] > dist[u] + T[i]) {
                dist[v] = dist[u] + T[i];
                if (!inq[v]) {
                    q.push(v);
                    inq[v]++;
                }
            }
        }
    }
    return (dist[dst] == 0x7F7F7F7F ? 0 : dist[dst]);
}

int main() {
    scanf("%d%d", &N, &M);
    char bs[25], fs[25];
    for (int i = 0; i < M; i++) {
        scanf("%d", &T[i]);
        scanf("%s%s", bs, fs);
        for (int j = 0; j < N; j++) {
            if (bs[j] == '0') continue;
            int x = (N-1-j);
            BM[i] |= (1<<x);
            if (bs[j] == '+') B[i] |= (1<<x);
        }
        for (int j = 0; j < N; j++) {
            if (fs[j] == '0') continue;
            int x = (N-1-j);
            if (fs[j] == '+') F2[i] |= (1<<x);
            else F1[i] |= (1<<x);
        }
    }

    printf("%d\n", spfa());

    return 0;
}
