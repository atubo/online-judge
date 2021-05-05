// https://codeforces.com/problemset/problem/282/C
// XOR and OR

#include <bits/stdc++.h>
using namespace std;

int main() {
  string s, t;
  cin >> s >> t;
  int c1 = 0, c2 = 0;
  if (s.length() != t.length()) {
    printf("NO\n");
    return 0;
  }
  for (int i = 0; i < (int)s.length(); i++) {
    c1 += (s[i] == '1');
    c2 += (t[i] == '1');
  }
  if ((c1 == 0 && c2 == 0) || (c1 > 0 && c2 > 0)) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }
  return 0;
}
