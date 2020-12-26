// https://www.luogu.com.cn/problem/P3805
// 【模板】manacher算法

#include <bits/stdc++.h>
using namespace std;

struct Manacher {
    const int length_;
    int *p;
    char *s;
    int *maxlen;

    Manacher(const string &sin):length_(sin.length()) {
        alloc();

        // put special charaters at the begining and between letters
        s[0] = '$';
        s[1] = '#';
        for (int i = 0; i < (int)sin.length(); i++) {
            s[i*2+2] = sin[i];
            s[i*2+3] = '#';
        }

        int mx = 0, id = 0;
        for (int i = 1; s[i] != '\0'; i++) {
            p[i] = mx > i ? min(p[2*id-i], mx-i) : 1;
            while (s[i+p[i]] == s[i-p[i]]) p[i]++;
            if (i + p[i] > mx) {
                mx = i + p[i];
                id = i;
            }
        }
    }

    ~Manacher() {
        dealloc();
    }
private:
    void alloc() {
        p = new int[2*length_+3]{};
        s = new char[2*length_+3]{};
        maxlen = new int[length_+1]{};
    }

    void dealloc() {
        delete[] p;
        delete[] s;
        delete[] maxlen;
    }
};

int main() {
  string s;
  cin >> s;
  const int n = s.length();
  Manacher manacher(s);
  int ans = 0;
  for (int i = 1; i < 2*n+3; i++) {
    ans = max(ans, manacher.p[i]-1);
  }
  printf("%d\n", ans);
  return 0;
}
