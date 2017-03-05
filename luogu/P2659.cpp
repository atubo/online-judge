// https://www.luogu.org/problem/show?pid=2659
// 美丽的序列

#include <bits/stdc++.h>
using namespace std;

int N;
int A[2000010];

int main() {
    scanf("%d", &N);
    A[0] = -2;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    A[N+1] = -1;

    int64_t ret = 0;
    stack<int> st;
    st.push(0);
    for (int i = 1; i <= N+1; i++) {
        while (A[st.top()] >= A[i]) {
            int64_t h = A[st.top()];
            st.pop();
            int64_t area = h * (i - st.top() - 1);
            ret = max(ret, area);
        }
        st.push(i);
    }

    printf("%lld\n", ret);

    return 0;
}
