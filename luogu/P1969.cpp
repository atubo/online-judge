// https://www.luogu.org/problemnew/show/P1969
// 积木大赛

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int H[MAXN];
int N;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &H[i]);
    }
    stack<int> s;
    s.push(0);
    int ret = 0;
    for (int i = 0; i < N; i++) {
        int h = H[i];
        if (h > s.top()) {
            ret += h - s.top();
            s.push(h);
        } else {
            while (s.top() > h) s.pop();
            s.push(h);
        }
    }
    printf("%d\n", ret);
    return 0;
}
