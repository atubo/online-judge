
class NestedInteger {
public:
    NestedInteger(bool is_integer = false, int x = 0):
        is_integer_(is_integer), val_(x) {}

    bool isInteger() const {
        return is_integer_;
    }

    int getInteger() const {
        return val_;
    }

    const vector<NestedInteger> &getList() const {
        return list_;
    }

private:
    bool is_integer_;
    int val_;
    vector<NestedInteger> list_;
    friend class NestedIntegerParser;
};

class NestedIntegerParser {
public:
    NestedIntegerParser(const string &str): str_(str), pos_(0) {}

    NestedInteger parseItem() {
        if (peek() == '[') {
            NestedInteger res;
            res.list_ = parse();
            return res;
        } else {
            int q = pos_;
            while ('0' <= str_[q] && str_[q] <= '9') q++;
            int val = stoi(str_.substr(pos_, q-pos_));
            pos_ = q;
            return NestedInteger(true, val);
        }
    }

    vector<NestedInteger> parse() {
        vector<NestedInteger> res;
        accept('[');
        res.push_back(parseItem());
        while (peek() == ',') {
            accept(',');
            res.push_back(parseItem());
        }
        accept(']');
        return res;
    }

private:
    const string &str_;
    int pos_;

    char peek() const {
        return str_[pos_];
    }

    void accept(char c) {
        assert(str_[pos_] == c);
        pos_++;
    }
};

std::istream& operator >> (std::istream &in,
                           vector<NestedInteger> &ni) {
    std::string s;
    in >> s;
    NestedIntegerParser parser(s);
    ni = parser.parse();
    return in;
}

std::ostream& operator << (std::ostream& out,
                           const vector<NestedInteger> &ni) {
    out << '[';
    for (int i = 0; i < (int)ni.size()-1; i++) {
        const auto &x = ni[i];
        if (x.isInteger()) {
            out << x.getInteger();
        } else {
            out << x.getList();
        }
        out << ',';
    }
    if (ni.size() > 0) {
        const auto &x = ni.back();
        if (x.isInteger()) {
            out << x.getInteger();
        } else {
            out << x.getList();
        }
    }
    out << ']';
    return out;
}

