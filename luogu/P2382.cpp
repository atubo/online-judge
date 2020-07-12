// https://www.luogu.com.cn/problem/P2382
// 化学分子式

#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> PT;

pair<int, int> parseNum(const string& s, int p, int q) {
  assert(p <= q);
  if (p == q || !isdigit(s[p])) return make_pair(1, p);
  int i = p;
  while (i < q && isdigit(s[i])) i++;
  int ans = stoi(s.substr(p, i-p));
  return make_pair(ans, i);
}

pair<string, int> parseAtom(const string& s, int p, int q) {
  assert(isupper(s[p]));
  int i = p+1;
  while (i < q && islower(s[i])) i++;
  return make_pair(s.substr(p, i-p), i);
}

int link(const string& s, int p, int q) {
  assert(s[p] == '(');
  int cnt = 1;
  int i = p+1;
  for (; i < q; i++) {
    if (s[i] == '(') cnt++;
    if (s[i] == ')') cnt--;
    if (cnt == 0) return i;
  }
  assert(false);
  return -1;
}

int parse(const string& s, int p, int q) {
  if (p == q) return 0;
  if (s[p] == '(') {
    int i = link(s, p, q);
    int count, j;
    tie(count, j) = parseNum(s, i+1, q);
    int part1 = parse(s, p+1, i);
    int part2 = parse(s, j, q);
    if (part1 == -1 || part2 == -1) return -1;
    return part1 * count + part2;
  }
  string atom;
  int i;
  tie(atom, i) = parseAtom(s, p, q);
  if (PT.count(atom) == 0) return -1;
  int count, j;
  tie(count, j) = parseNum(s, i, q);
  int wt = PT.at(atom) * count;
  int remain = parse(s, j, q);
  if (remain == -1) return -1;
  return wt + remain;
}

int main() {
  while (true) {
    string s;
    int mass;
    cin >> s;
    if (s == "END_OF_FIRST_PART") break;
    cin >> mass;
    PT[s] = mass;
  }
  while (true) {
    string s;
    cin >> s;
    if (s == "0") break;
    int ans = parse(s, 0, s.length());
    if (ans != -1) printf("%d\n", ans);
    else printf("UNKNOWN\n");
  }
  return 0;
}
