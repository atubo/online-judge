// https://www.luogu.org/problemnew/show/P3419
// [POI2005]SAM-Toy Cars

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
const int MAXP = 500010;
int N, K, P;
bool inq[MAXN];
int last[MAXN];
int A[MAXP], nxt[MAXP];

struct Data {
    int x, nxt;
    bool operator < (const Data& other) const {
        if (nxt != other.nxt) return nxt < other.nxt;
        return x < other.x;
    }
};

int main() {
    scanf("%d%d%d", &N, &K, &P);
    for (int i = 1; i <= P; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 1; i <= N; i++) last[i] = P+1;
    for (int i = P; i >= 1; i--) {
        int x = A[i];
        nxt[i] = last[x];
        last[x] = i;
    }

    int ans = 0;
    set<Data> pq;
    for (int i = 1; i <= P; i++) {
        if (inq[A[i]]) {
            auto it = pq.find({A[i], last[A[i]]});
            pq.erase(it);
            pq.insert({A[i], nxt[i]});
            last[A[i]] = nxt[i];
            continue;
        }
        if ((int)pq.size() == K) {
            auto it = pq.rbegin();
            int x = it->x;
            inq[x] = false;
            pq.erase(*it);
        }
        ans++;
        pq.insert({A[i], nxt[i]});
        inq[A[i]] = true;
        last[A[i]] = nxt[i];
    }
    printf("%d", ans);

    return 0;
}
