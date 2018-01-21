// https://www.luogu.org/problemnew/show/P1949
// 聪明的打字员_NOI导刊2011提高（10）

#include <bits/stdc++.h>
using namespace std;

const int M = 1000000;
bool vis[6*M];
int SRC, DST;

int PWR[6] = {1, 10, 100, 1000, 10000, 100000};

int encode(int pos, int x) {
    return pos * M + x;
}

void decode(int c, int &pos, int &x) {
    x = c % M;
    pos = c / M;
}

struct Item {
    int c, d;
};
queue<Item> q;

int calc(int x, int i) {
    return (x / PWR[5-i]) % 10;
}

void add(int pos, int x, int d) {
    int code = encode(pos, x);
    if (!vis[code]) {
        q.push({code, d});
        vis[code] = true;
    }
}

void swap0(int pos, int x, int d) {
    if (pos == 0) return;
    int d0 = calc(x, 0);
    int dp = calc(x, pos);
    int y = x + (dp - d0) * PWR[5] + (d0 - dp) * PWR[5-pos];
    add(pos, y, d+1);
}

void swap1(int pos, int x, int d) {
    if (pos == 5) return;
    int d5 = calc(x, 5);
    int dp = calc(x, pos);
    int y = x + (dp - d5) * PWR[0] + (d5 - dp) * PWR[5-pos];
    add(pos, y, d+1);
}

void up(int pos, int x, int d) {
    int dp = calc(x, pos);
    if (dp == 9) return;
    int y = x + PWR[5-pos];
    add(pos, y, d+1);
}

void down(int pos, int x, int d) {
    int dp = calc(x, pos);
    if (dp == 0) return;
    int y = x - PWR[5-pos];
    add(pos, y, d+1);
}

void left(int pos, int x, int d) {
    if (pos == 0) return;
    add(pos-1, x, d+1);
}

void right(int pos, int x, int d) {
    if (pos == 5) return;
    add(pos+1, x, d+1);
}

int bfs() {
    int code = encode(0, SRC);
    q.push({code, 0});
    vis[code] = true;
    while (!q.empty()) {
        Item item = q.front();
        q.pop();
        code = item.c;
        int d = item.d;
        int pos, x;
        decode(code, pos, x);
        if (x == DST) return d;
    
        swap0(pos, x, d);
        swap1(pos, x, d);
        up(pos, x, d);
        down(pos, x, d);
        left(pos, x, d);
        right(pos, x, d);
    }
    assert(0);
    return 0;
}

int main() {
    string s;
    cin >> s;
    SRC = stoi(s);
    cin >> s;
    DST = stoi(s);
    printf("%d", bfs());
    return 0;
}
