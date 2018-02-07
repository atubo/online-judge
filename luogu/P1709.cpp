// https://www.luogu.org/problemnew/show/P1709
// [USACO5.5]隐藏口令Hidden Password

#include <bits/stdc++.h>
using namespace std;

int minimumRepresentation(const char *s, int l) {
    int i = 0, j = 1, k = 0;
    while (i < l && j < l) {
        k = 0;
        while (s[i+k] == s[j+k] && k < l) k++;
        if (k == l) break;
        if (s[i+k] > s[j+k]) i = max(i+k+1, j+1);
        else j = max(j+k+1, i+1);
    }
    return min(i, j);
}

int main() {
    int n;
    scanf("%d", &n);
    string s;
    char line[80];
    while ((int)s.length() < n) {
        scanf("%s", line);
        s += line;
    }
    s += s;
    printf("%d\n", minimumRepresentation(s.c_str(), n));
    return 0;
}
