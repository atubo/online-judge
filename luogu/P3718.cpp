// https://www.luogu.org/problem/show?pid=3718
// [AHOI2017初中组]alter

#include <bits/stdc++.h>
using namespace std;

int N, K;
string S;
vector<int> T;

bool feasible1() {
    for (int d = 0; d < 2; d++) {
        int r = 0;
        for (int i = 0; i < (int)S.length(); i++) {
            if ((i%2 == d && S[i] == 'N') ||
                (i%2 != d && S[i] == 'F')) r++;
        }
        if (r <= K) return true;
    }

    return false;
}

void build() {
    char curr = '\0';
    for (char c: S) {
        if (c != curr) {
            T.push_back(1);
            curr = c;
        } else {
            T.back()++;
        }
    }
}

bool feasible(int m) {
    int ret = 0;
    for (int p: T) {
        ret += p/(m+1);
    }
    return ret <= K;
}


int main() {
    cin >> N >> K >> S;
    if (feasible1()) {
        cout << 1 << endl;
        return 0;
    }
    build();
    int lo = 1, hi = N;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (feasible(mid)) hi = mid;
        else lo = mid;
    }
    cout << hi << endl;
    return 0;
}
