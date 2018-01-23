// https://www.luogu.org/problemnew/show/P2585
// [ZJOI2006]三色二叉树

#include <bits/stdc++.h>
using namespace std;
int N;
char s[500010];
int pos;

int id(int i, int j) {
    return (i % 3) * 3 + (j % 3);
}

struct Item {
    Item() {
        memset(x, 0, sizeof(x));
        memset(y, 0, sizeof(y));
    }
    int x[9], y[9];
};

Item parse() {
    assert(pos < N);
    Item ret;
    if (s[pos] == '0') {
        for (int i = 0; i < 3; i++) {
            ret.x[id(i, i)] = ret.y[id(i, i)] = 1;
        }
        pos++;
    } else if (s[pos] == '1') {
        pos++;
        Item child = parse();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                ret.x[id(i, j)] = max(child.x[id(i+1, j)],
                                      child.x[id(i+2, j)]) + (j == i);
                ret.y[id(i, j)] = min(child.y[id(i+1, j)],
                                      child.y[id(i+2, j)]) + (j == i);
            }
        }
    } else {
        pos++;
        Item left = parse();
        Item right = parse();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                ret.x[id(i, j)] = max(left.x[id(i+1, j)] + right.x[id(i+2, j)],
                                      left.x[id(i+2, j)] + right.x[id(i+1, j)])
                    + (j == i);
                ret.y[id(i, j)] = min(left.y[id(i+1, j)] + right.y[id(i+2, j)],
                                      left.y[id(i+2, j)] + right.y[id(i+1, j)])
                    + (j == i);
            }
        }
    }
    return ret;
}

int min3(int x, int y, int z) {
    return min(x, min(y, z));
}

int max3(int x, int y, int z) {
    return max(x, max(y, z));
}

int main() {
    scanf("%s", s);
    N = strlen(s);

    Item item = parse();
#if 0
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", item.x[id(i, j)]);
        }
        printf("\n");
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", item.y[id(i, j)]);
        }
        printf("\n");
    }
#endif
    printf("%d %d\n", max3(item.x[0], item.x[1], item.x[2]),
           min3(item.y[0], item.y[1], item.y[2]));
    return 0;
}
