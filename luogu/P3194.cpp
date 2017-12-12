// https://www.luogu.org/problemnew/show/P3194
// [HNOI2008]水平可见直线

#include <bits/stdc++.h>
using namespace std;
using PIF = pair<int, double>;

const int MAXN = 50010;
int A[MAXN], B[MAXN];
int N;

double solve(int i, int j) {
    return (double(B[j]) - B[i]) / (A[i] - A[j]);
}

int main() {
    scanf("%d", &N);
    vector<int> t1(N), t2;
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &A[i], &B[i]);
        t1[i] = i;
    }
    sort(t1.begin(), t1.end(), [](int i, int j) -> bool {
         return make_pair(A[i], -B[i]) < make_pair(A[j], -B[j]);
         });
    for (int i = 0; i < N; i++) {
        if (i == 0 || A[t1[i]] != A[t1[i-1]]) t2.push_back(t1[i]);
    }

    stack<PIF> st;
    st.push(make_pair(t2[0], -1e30));
    for (int i = 1; i < (int)t2.size(); i++) {
        double x;
        while ((x = solve(st.top().first, t2[i])) <= st.top().second) st.pop();
        st.push(make_pair(t2[i], x));
    }

    vector<int> ret;
    while (!st.empty()) {
        ret.push_back(st.top().first);
        st.pop();
    }
    sort(ret.begin(), ret.end());
    for (int x: ret) {
        printf("%d ", x+1);
    }
    printf("\n");

    return 0;
}
