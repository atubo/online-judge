// https://www.luogu.org/problemnew/show/P2186
// 小Z的栈函数

#include <bits/stdc++.h>
using namespace std;

const int64_t MAX = 1000000000;
int64_t st[2048];
int top;

struct Error : public exception {
} ERROR;

struct Op {
    virtual void op() const = 0;
};

struct Num : public Op {
    int64_t x_;
    Num(int64_t x): x_(x) {}
    virtual void op() const {
        if (x_ > MAX) throw ERROR;
        st[top++] = x_;
    }
};

struct Pop : public Op {
    virtual void op() const {
        if (top == 0) throw ERROR;
        top--;
    }
};

struct Inv : public Op {
    virtual void op() const {
        if (top == 0) throw ERROR;
        st[top-1] = -st[top-1];
    }
};

struct Dup : public Op {
    virtual void op() const {
        if (top == 0) throw ERROR;
        st[top] = st[top-1];
        top++;
    }
};

struct Swp : public Op {
    virtual void op() const {
        if (top < 2) throw ERROR;
        swap(st[top-1], st[top-2]);
    }
};

struct Add : public Op {
    virtual void op() const {
        if (top < 2) throw ERROR;
        int64_t x = st[top-1] + st[top-2];
        if (abs(x) > MAX) throw ERROR;
        st[top-2] = x;
        top--;
    }
};

struct Sub : public Op {
    virtual void op() const {
        if (top < 2) throw ERROR;
        int64_t x = st[top-2] - st[top-1];
        if (abs(x) > MAX) throw ERROR;
        st[top-2] = x;
        top--;
    }
};

struct Mul : public Op {
    virtual void op() const {
        if (top < 2) throw ERROR;
        int64_t x = st[top-2] * st[top-1];
        if (abs(x) > MAX) throw ERROR;
        st[top-2] = x;
        top--;
    }
};

struct Div : public Op {
    virtual void op() const {
        if (top < 2) throw ERROR;
        if (st[top-1] == 0) throw ERROR;
        int64_t x = st[top-2] / st[top-1];
        if (abs(x) > MAX) throw ERROR;
        st[top-2] = x;
        top--;
    }
};

struct Mod : public Op {
    virtual void op() const {
        if (top < 2) throw ERROR;
        if (st[top-1] == 0) throw ERROR;
        int64_t x = st[top-2] % st[top-1];
        if (abs(x) > MAX) throw ERROR;
        st[top-2] = x;
        top--;
    }
};

vector<Op*> ops;

void eval(int64_t x) {
    if (abs(x) > MAX) {
        printf("ERROR\n");
        return;
    }
    top = 0;
    st[top++] = x;

    try {
        for (auto op: ops) {
            op->op();
        }
        if (top == 1) {
            printf("%ld\n", st[0]);
        } else {
            printf("ERROR\n");
        }
    } catch (...) {
        printf("ERROR\n");
    }
}

int main() {
    while (true) {
        string s;
        cin >> s;
        if (s == "END") break;
        else if (s == "NUM") {
            int64_t x;
            cin >> x;
            ops.push_back(new Num(x));
        } else if (s == "POP") {
            ops.push_back(new Pop());
        } else if (s == "INV") {
            ops.push_back(new Inv());
        } else if (s == "DUP") {
            ops.push_back(new Dup());
        } else if (s == "SWP") {
            ops.push_back(new Swp());
        } else if (s == "ADD") {
            ops.push_back(new Add());
        } else if (s == "SUB") {
            ops.push_back(new Sub());
        } else if (s == "MUL") {
            ops.push_back(new Mul());
        } else if (s == "DIV") {
            ops.push_back(new Div());
        } else if (s == "MOD") {
            ops.push_back(new Mod());
        }
    }

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int64_t x;
        cin >> x;
        eval(x);
    }
    return 0;
}
