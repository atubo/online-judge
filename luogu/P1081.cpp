// https://www.luogu.org/problemnew/show/P1081
// 开车旅行

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N, M;
int H[MAXN], A[MAXN], B[MAXN];

using Pii = pair<int, int>;
using Tiii = tuple<int, int, int>;

void findDestination(int u, set<Pii> &cities) {
    auto it = cities.find(make_pair(H[u], u));
    vector<Tiii> candidates;
    auto it1 = it;
    it1++;
    if (it1 != cities.end()) {
        int d = it1->first - H[u];
        candidates.push_back(make_tuple(d, 1, it1->second));
        it1++;
        if (it1 != cities.end()) {
            d = it1->first - H[u];
            candidates.push_back(make_tuple(d, 1, it1->second));
        }
    }
    it1 = it;
    if (it1 != cities.begin()) {
        it1--;
        int d = H[u] - it1->first;
        candidates.push_back(make_tuple(d, -1, it1->second));
        if (it1 != cities.begin()) {
            it1--;
            d = H[u] - it1->first;
            candidates.push_back(make_tuple(d, -1, it1->second));
        }
    }

    sort(candidates.begin(), candidates.end());
    if (candidates.size() >= 2) A[u] = get<2>(candidates[1]);
    if (candidates.size() >= 1) B[u] = get<2>(candidates[0]);

    cities.erase(it);
}

struct Trip {
    int64_t dist_a, dist_b;
    int next;
};

Trip trip[MAXN][18];

void generateTrips() {
    for (int i = 0; i < N; i++) {
        int p = A[i];
        if (p == -1) {
            trip[i][0] = {0, 0, -1};
            continue;
        }
        int da = abs(H[p] - H[i]);
        int q = B[p];
        if (q == -1) {
            trip[i][0] = {da, 0, -1};
            continue;
        }
        int db = abs(H[q] - H[p]);
        trip[i][0] = {da, db, q};
    }

    for (int k = 1; k < 18; k++) {
        for (int i = 0; i < N; i++) {
            Trip t = trip[i][k-1];
            if (t.next == -1) {
                trip[i][k] = t;
                continue;
            }
            Trip t2 = trip[t.next][k-1];
            trip[i][k].dist_a = t.dist_a + t2.dist_a;
            trip[i][k].dist_b = t.dist_b + t2.dist_b;
            trip[i][k].next = t2.next;
        }
    }
}

void calcDistance(int s, int xmax, int &xa, int &xb) {
    int p = s;
    int64_t x = 0;
    xa = 0, xb = 0;
    while (true) {
        int k = 0;
        for (; k < 18; k++) {
            if (trip[p][k].next == -1 ||
                x + trip[p][k].dist_a + trip[p][k].dist_b > xmax) {
                break;
            }
        }
        if (k == 0) {
            if (x + trip[p][0].dist_a <= xmax) xa += trip[p][0].dist_a;
            if (x + trip[p][0].dist_a + trip[p][0].dist_b <= xmax) {
                xb += trip[p][0].dist_b;
            }
            break;
        }
        xa += trip[p][k-1].dist_a;
        xb += trip[p][k-1].dist_b;
        x = xa + xb;
        p = trip[p][k-1].next;
    }
}

void calcMinRatio(int x0) {
    int hmin = H[0], imin = 0;
    int xa, xb;
    calcDistance(0, x0, xa, xb);
    int xamin = xa, xbmin = xb;
    for (int i = 1; i < N; i++) {
        calcDistance(i, x0, xa, xb);
        if (xbmin == 0) {
            if (xb > 0 || H[i] > hmin) {
                xamin = xa;
                xbmin = xb;
                hmin = H[i];
                imin = i;
            }
        } else {
            int64_t p1 = (int64_t)xamin * xb;
            int64_t p2 = (int64_t)xa * xbmin;
            if (xb > 0  && (p1 > p2 || (p1 == p2 && H[i] > hmin))) {
                xamin = xa;
                xbmin = xb;
                hmin = H[i];
                imin = i;
            }
        }
    }
    printf("%d\n", imin+1);
}

int main() {
    memset(A, -1, sizeof(A));
    memset(B, -1, sizeof(B));
    set<Pii> cities;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &H[i]);
        cities.insert({H[i], i});
    }
    for (int i = 0; i < N; i++) {
        findDestination(i, cities);
    }
#if 0
    for (int i = 0; i < N; i++) {
        printf("%d %d\n", A[i], B[i]);
    }
#endif
    generateTrips();

#if 0
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < 2; k++) {
            printf("(%d %d %d) ", trip[i][k].dist_a, trip[i][k].dist_b, trip[i][k].next);
        }
        printf("\n");
    }
#endif
    int x0;
    scanf("%d", &x0);
    calcMinRatio(x0);

    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int s, x;
        scanf("%d%d", &s, &x);
        int xa, xb;
        calcDistance(s-1, x, xa, xb);
        printf("%d %d\n", xa, xb);
    }
    return 0;
}
