// https://www.luogu.org/problemnew/show/P2601
// [ZJOI2009]对称的正方形

#include <bits/stdc++.h>
using namespace std;

const int START = 1e9+1;
const int BETWN = 1e9+2;
const int END   = 1e9+3;
const int MAXN = 1010;

namespace Manacher {

// note place before the first char is 1, first char is 2
// second char is 4, etc.
int p[2*MAXN+10];
int s[2*MAXN+10];
int maxlen[MAXN+10];

void manacher() {
    memset(p, 0, sizeof(p));

    int mx = 0, id = 0;
    for (int i = 1; s[i] != END; i++) {
        p[i] = mx > i ? min(p[2*id-i], mx-i) : 1;
        while (s[i+p[i]] == s[i-p[i]]) p[i]++;
        if (i + p[i] > mx) {
            mx = i + p[i];
            id = i;
        }
    }
}

// some utility functions
// find for each position the maximum lenght of the palindrom start there
// note the index starts from 0
void calcMaxlen() {
    memset(maxlen, 0, sizeof(maxlen));
    for (int i = 1; s[i] != END; i++) {
        int pos = (i - p[i]) / 2;
        maxlen[pos] = max(maxlen[pos], p[i]-1);
    }
    for (int i = 1; s[i] != END; i++) {
        maxlen[i] = max(maxlen[i-1]-2, maxlen[i]);
    }
}
}

int N, M;
int matrix[MAXN][MAXN];
int maxh[2*MAXN][2*MAXN], maxv[2*MAXN][2*MAXN];
int max1[MAXN][MAXN], max2[MAXN][MAXN];
struct Item {
    int x, maxl;
} items[MAXN];
int front;

int radius(int i, int x) {
    return min(abs(items[i].x - x), (items[i].maxl - 1) / 2);
}

bool check(int i, int x) {
    return (items[i].maxl - 1) / 2 >= abs(items[i+1].x - x) + 1;
}

int search(int x) {
    if (check(0, x)) return radius(0, x);
    int lo = 0, hi = front-1;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (check(mid, x)) hi = mid;
        else               lo = mid;
    }
    return radius(hi, x);
}

int search2(int x) {
    if (items[front-1].maxl < 3) return 0;
    else return search(x);
}

void print() {
    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= 2*M; j++) {
            printf("%2d ", maxh[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 1; i <= 2*N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%2d ", maxv[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%2d ", max1[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%2d ", max2[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    for (int i = 0; i < N; i++) {
        Manacher::s[0] = START;
        Manacher::s[1] = BETWN;
        for (int j = 0; j < M; j++) {
            Manacher::s[2*j+2] = matrix[i][j];
            Manacher::s[2*j+3] = BETWN;
        }
        Manacher::s[2*M+2] = END;
        Manacher::manacher();
        for (int j = 1; j <= 2*M; j++) {
            maxh[i][j] = Manacher::p[j];
        }
    }

    for (int i = 0; i < M; i++) {
        Manacher::s[0] = START;
        Manacher::s[1] = BETWN;
        for (int j = 0; j < N; j++) {
            Manacher::s[2*j+2] = matrix[j][i];
            Manacher::s[2*j+3] = BETWN;
        }
        Manacher::s[2*N+2] = END;
        Manacher::manacher();
        for (int j = 1; j <= 2*N; j++) {
            maxv[j][i] = Manacher::p[j];
        }
    }

    for (int i = 2; i <= 2*N; i+=2) {
        front = 0;
        for (int j = 0; j < M; j++) {
            int last = j;
            while (front > 0 && maxv[i][j] <= items[front-1].maxl) {
                last = items[front-1].x;
                front--;
            }
            items[front++] = {last, maxv[i][j]};
            max1[i/2-1][j] = search(j);
        }
        front = 0;
        for (int j = M-1; j >= 0; j--) {
            int last = j;
            while (front > 0 && maxv[i][j] <= items[front-1].maxl) {
                last = items[front-1].x;
                front--;
            }
            items[front++] = {last, maxv[i][j]};
            max1[i/2-1][j] = min(max1[i/2-1][j], search(j));
        }
    }
    for (int i = 2; i <= 2*M; i+=2) {
        front = 0;
        for (int j = 0; j < N; j++) {
            int last = j;
            while (front > 0 && maxh[j][i] <= items[front-1].maxl) {
                last = items[front-1].x;
                front--;
            }
            items[front++] = {last, maxh[j][i]};
            max2[j][i/2-1] = search(j);
        }
        front = 0;
        for (int j = N-1; j >= 0; j--) {
            int last = j;
            while (front > 0 && maxh[j][i] <= items[front-1].maxl) {
                last = items[front-1].x;
                front--;
            }
            items[front++] = {last,maxh[j][i]};
            max2[j][i/2-1] = min(max2[j][i/2-1], search(j));
        }
    }
    //print();

    int64_t ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            ans += min(max1[i][j], max2[i][j]) + 1;
        }
    }
    //printf("%lld\n", ans);

    for (int i = 3; i <= 2*N+1; i+=2) {
        front = 0;
        for (int j = 0; j < M; j++) {
            int last = j;
            while (front > 0 && maxv[i][j] <= items[front-1].maxl) {
                last = items[front-1].x;
                front--;
            }
            items[front++] = {last, maxv[i][j]};
            max1[i/2-1][j] = search2(j+1);
        }
        max1[i/2-1][M-1] = 0;
        front = 0;
        for (int j = M-1; j >= 1; j--) {
            int last = j;
            while (front > 0 && maxv[i][j] <= items[front-1].maxl) {
                last = items[front-1].x;
                front--;
            }
            items[front++] = {last, maxv[i][j]};
            max1[i/2-1][j-1] = min(max1[i/2-1][j-1], search2(j-1));
        }
    }
    for (int i = 3; i <= 2*M+1; i+=2) {
        front = 0;
        for (int j = 0; j < N; j++) {
            int last = j;
            while (front > 0 && maxh[j][i] <= items[front-1].maxl) {
                last = items[front-1].x;
                front--;
            }
            items[front++] = {last, maxh[j][i]};
            max2[j][i/2-1] = search2(j+1);
        }
        max2[N-1][i/2-1] = 0;
        front = 0;
        for (int j = N-1; j >= 1; j--) {
            int last = j;
            while (front > 0 && maxh[j][i] <= items[front-1].maxl) {
                last = items[front-1].x;
                front--;
            }
            items[front++] = {last,maxh[j][i]};
            max2[j-1][i/2-1] = min(max2[j-1][i/2-1], search2(j-1));
        }
    }
    //print();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            ans += min(max1[i][j], max2[i][j]);
        }
    }
    printf("%lld\n", ans);



    return 0;
}
