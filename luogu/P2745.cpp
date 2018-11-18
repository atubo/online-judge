// https://www.luogu.org/problemnew/show/P2745
// [USACO5.3]窗体面积Window Area

#include <bits/stdc++.h>
using namespace std;

struct Rect {
    int x1, y1, x2, y2;
    int idx;
    void print() const {
        printf("%d %d %d %d\n", x1, y1, x2, y2);
    }
} A[64];

int order[64];
int sz;
int ans;

int id(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('a' <= c && c <= 'z') return c - 'a' + 10;
    return c - 'A' + 36;
}

vector<int> split(const string &s) {
    vector<int> ret;
    int p = 0;
    for (int i = 0; i < 3; i++) {
        int q = s.find_first_of(',', p);
        ret.push_back(stoi(s.substr(p, q-p)));
        p = q+1;
    }
    ret.push_back(stoi(s.substr(p)));
    return ret;
}

void rotateRight(int x) {
    int t = order[x];
    for (int i = x; i >= 1; i--) {
        order[i] = order[i-1];
        A[order[i]].idx = i;
    }
    order[0] = t;
    A[t].idx = 0;
}

void rotateLeft(int x) {
    int t = order[x];
    for (int i = x; i < sz-1; i++) {
        order[i] = order[i+1];
        A[order[i]].idx = i;
    }
    order[sz-1] = t;
    A[t].idx = sz-1;
}

int calc(int x1, int x2, int x) {
    if (x <= x1) return x1;
    if (x >= x2) return x2;
    return x;
}

void dfs(int x1, int y1, int x2, int y2, int k) {
    //printf("%d %d %d %d %d\n", x1, y1, x2, y2, k);
    if (x1 >= x2 || y1 >= y2) return;
    if (k < 0) return;
    int x3 = calc(x1, x2, A[order[k]].x1);
    int y3 = calc(y1, y2, A[order[k]].y1);
    int x4 = calc(x1, x2, A[order[k]].x2);
    int y4 = calc(y1, y2, A[order[k]].y2);
    ans += (x4-x3) * (y4-y3);
    dfs(x1, y1, x3, y4, k-1);
    dfs(x3, y1, x2, y3, k-1);
    dfs(x4, y3, x2, y2, k-1);
    dfs(x1, y4, x4, y2, k-1);
}



void process(const string &s) {
    char c = s[0];
    if (c == 'w') {
        int x = id(s[2]);
        auto numbers = split(s.substr(4, s.length()-5));
        int x1 = numbers[0], y1 = numbers[1];
        int x2 = numbers[2], y2 = numbers[3];
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        A[x] = {x1, y1, x2, y2, sz};
        order[sz] = x;
        rotateRight(sz);
        sz++;
#if 0
        for (int i = 0; i < sz; i++) {
            A[order[i]].print();
        }
#endif
    } else if (c == 't') {
        int x = id(s[2]);
        rotateRight(A[x].idx);
    } else if (c == 'b') {
        int x = id(s[2]);
        rotateLeft(A[x].idx);
    } else if (c == 'd') {
        int x = id(s[2]);
        rotateLeft(A[x].idx);
        sz--;
    } else {
        int x = id(s[2]);
        ans = 0;
        dfs(A[x].x1, A[x].y1, A[x].x2, A[x].y2, A[x].idx-1);
        int tot = (A[x].x2 - A[x].x1) * (A[x].y2 - A[x].y1);
        printf("%.3f\n", 100.0*(tot-ans)/tot);
    }
}

int main() {
    string s;
    while (cin >> s) {
        process(s);
    }
    return 0;
}
