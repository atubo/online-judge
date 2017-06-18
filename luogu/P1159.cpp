// https://www.luogu.org/problem/show?pid=1159
// 排行榜

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<string> names(N);
    vector<bool> marked(N, false);
    vector<int> ups, downs;
    vector<int> result(N);

    string ch;
    for (int i = 0; i < N; i++) {
        cin >> names[i] >> ch;
        switch (ch[0]) {
            case 'U':
                ups.push_back(i);
                break;
            case 'D':
                downs.push_back(i);
                break;
            default:
                marked[i] = true;
                result[i] = i;
                break;
        }
    }

    for (int i = 0, j= 0; i < (int)downs.size(); i++) {
        int d = downs[i];
        while (marked[j]) j++;
        result[j] = d;
        marked[j] = true;
    }
    for (int i = 0, j = 0; i < (int)ups.size(); i++) {
        int u = ups[i];
        while (marked[j]) j++;
        result[j] = u;
        marked[j] = true;
    }

    for (int x: result) {
        cout << names[x] << endl;
    }
    return 0;
}
