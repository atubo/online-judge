// https://www.luogu.org/problemnew/show/P3939
// 数颜色

#include <bits/stdc++.h>
using namespace std;

int ch;
inline void read(int &a) {
    a = 0;
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') a = a * 10 + ch - '0', ch = getchar();
}

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    vector<vector<int>> A(N);
    vector<int> C(N);
    vector<int> colorMap(300001, -1);
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        int x;
        read(x);
        if (colorMap[x] == -1) {
            colorMap[x] = cnt++;
        }
        A[colorMap[x]].push_back(i);
        C[i] = colorMap[x];
    }

    for (int i = 0; i < M; i++) {
        int cmd;
        read(cmd);
        if (cmd == 1) {
            int l, r, c;
            read(l); read(r); read(c);
            l--; r--;
            if (colorMap[c] == -1) {
                cout << 0 << endl;
                continue;
            }
            const vector<int>& v = A[colorMap[c]];
            int lo = lower_bound(v.begin(), v.end(), l) - v.begin();
            int hi = upper_bound(v.begin(), v.end(), r) - v.begin();
            cout << hi - lo << endl;
        } else {
            int x;
            read(x);
            x--;
            int c1 = C[x];
            int c2 = C[x+1];
            if (c1 != c2) {
                vector<int>& v1 = A[c1];
                vector<int>& v2 = A[c2];
                int p1 = lower_bound(v1.begin(), v1.end(), x) - v1.begin();
                int p2 = lower_bound(v2.begin(), v2.end(), x+1) - v2.begin();
                swap(v1[p1], v2[p2]);
                swap(C[x], C[x+1]);
            }
        }
    }
    return 0;
}
