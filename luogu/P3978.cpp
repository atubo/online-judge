// https://www.luogu.org/problemnew/show/P3978
// [TJOI2015]概率论

#include <bits/stdc++.h>
using namespace std;

int main() {
    double n;
    scanf("%lf", &n);
    printf("%.12lf", (n*(n+1))/(2*(2*n-1)));
    return 0;
}
