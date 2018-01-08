// https://www.luogu.org/problemnew/show/P2897
// [USACO08JAN]人工湖Artificial Lake

#include <bits/stdc++.h>
using namespace std;

const int MAXH = 2000000;
const int MAXN = 100010;
int N, top = -1;
int W[MAXN], H[MAXN];
int64_t ans[MAXN];

struct Item {
    int x, h, w;
} items[MAXN];

void print() {
    for (int i = 0; i <= top; i++) printf("(%d %d %d) ", items[i].x, items[i].h,
                                          items[i].w);
    printf("\n");
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d%d", &W[i], &H[i]);
    }
    W[0] = 0; H[0] = MAXH;
    W[N+1] = 0; H[N+1] = MAXH;
    int posmin = 1, hmin = H[1];
    for (int i = 2; i <= N; i++) {
        if (H[i] < hmin) {
            hmin = H[i];
            posmin = i;
        }
    }

    items[++top] = {posmin-1, H[posmin-1], W[posmin-1]};
    items[++top] = {posmin, hmin, W[posmin]};
    int64_t curr = 0;
    while (!(top == 1 && items[0].h == MAXH && items[1].h == MAXH)) {
        //print();
        int p;
        if (items[top-1].x < items[top].x) p = items[top].x+1;
        else p = items[top].x-1;
        int h = H[p];
        int area = 0;
        bool reverse = false;
        while (h > items[top].h) {
            if (top == 0) {
                reverse = true;
                break;
            }
            int i = items[top].x;
            area += items[top].w;
            ans[i] = curr + area;
            curr += (int64_t)area * (min(h, items[top-1].h) - items[top].h);
            top--;
        }
        if (!reverse) items[++top] = {p, h, area + W[p]};
        else {
            items[top].w += area;
            items[++top] = {p, h, W[p]};
            swap(items[top], items[top-1]);
            assert(top == 1);
        }
    }
    //print();
    for (int i = 1; i <= N; i++) {
        printf("%lld\n", ans[i]);
    }

    return 0;
}
