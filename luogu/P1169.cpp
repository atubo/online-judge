// https://www.luogu.org/problem/show?pid=1169
// [ZJOI2007]棋盘制作

#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;

const int MAXN = 2010;
char grid[MAXN][MAXN];
int H[MAXN];
int V[MAXN];
int N, M;
int maxSq = 0, maxRc = 0;

void tie(const PII& p, int& x, int& y) {
    x = p.first;
    y = p.second;
}

void update(int w, int h) {
    int s = min(w, h);
    maxRc = max(maxRc, w * h);
    maxSq = max(maxSq, s * s);
}

void popAll(stack<PII>& st, int p) {
    while (!st.empty()) {
        int x, h;
        tie(st.top(), x, h);
        st.pop();
        update(p-x+1, h);
    }
}


int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int x;
            scanf("%d", &x);
            grid[i][j] = x;
        }
    }
    for (int i = 0; i < N; i++) {
        stack<PII> st;
        for (int j = 0; j < M; j++) {
            if (i == 0) {
                V[j] = 1;
            } else {
                V[j] = (grid[i][j] == grid[i-1][j] ? 1 : V[j]+1);
            }
            if (j == 0) {
                H[j] = 1;
            } else {
                H[j] = (grid[i][j] == grid[i][j-1] ? 1 : H[j-1]+1);
            }

            if (j > 0 && grid[i][j] == grid[i][j-1]) {
                popAll(st, j-1);
            }

            while (!st.empty() && st.top().second > V[j]) {
                int x, h;
                tie(st.top(), x, h);
                st.pop();
                update(j-x, h);
                update(j-x+1, V[j]);
            }
            if (st.empty() || V[j] > st.top().second) {
                st.push(make_pair(j, V[j]));
            }
        }
        popAll(st, M-1);
    }

    printf("%d\n%d\n", maxSq, maxRc);

    return 0;
}
