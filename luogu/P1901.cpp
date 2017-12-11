// https://www.luogu.org/problemnew/show/P1901
// 发射站

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
int H[MAXN];
int64_t V[MAXN];
int64_t R[MAXN];
int N;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d%lld", &H[i], &V[i]);
    }
    stack<int> st;
    for (int i = 0; i < N; i++) {
        while (!st.empty() && H[st.top()] <= H[i]) st.pop();
        if (!st.empty()) {
            R[st.top()] += V[i];
        }
        st.push(i);
    }
    while (!st.empty()) st.pop();
    for (int i = N-1; i >= 0; i--) {
        while (!st.empty() && H[st.top()] <= H[i]) st.pop();
        if (!st.empty()) {
            R[st.top()] += V[i];
        }
        st.push(i);
    }
    int64_t ret = 0;
    for (int i = 0; i < N; i++) ret = max(ret, R[i]);
    printf("%lld\n", ret);
    return 0;
}
