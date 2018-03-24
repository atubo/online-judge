// https://www.luogu.org/problemnew/show/P1781
// 宇宙总统

#include <bits/stdc++.h>
using namespace std;

struct Candidate {
    int id;
    string cnt;
    bool operator < (const Candidate &other) const {
        if (cnt.length() > other.cnt.length()) return true;
        if (cnt.length() < other.cnt.length()) return false;
        return cnt > other.cnt;
    }
};

int N;
Candidate candidates[22];

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        string s;
        cin >> s;
        candidates[i] = {i, s};
    }
    sort(candidates+1, candidates+N+1);
    cout << candidates[1].id << endl;
    cout << candidates[1].cnt << endl;
    return 0;
}
