
struct Interval {
    int start, end;
    Interval(int s, int e) {
       this->start = s;
       this->end = e;
    }
};

std::istream& operator >> (std::istream &in,
                           Interval &interval) {
    char c;
    in >> c;
    assert(c == '(');
    int a, b;
    in >> a;
    while (!('0' <= in.peek() && in.peek() <= '9')) in.get();
    in >> b;
    interval.start = a;
    interval.end = b;
    in >> c;
    assert(c == ')');
    return in;
}

std::ostream& operator << (std::ostream &out,
                           const Interval &interval) {
    out << '(' << interval.start << ',' << interval.end << ')';
    return out;
}

std::istream& operator >> (std::istream &in,
                          std::vector<Interval> &intervals) {
    char c;
    in >> c;
    assert(c == '[');
    Interval itv(0, 0);
    in >> itv;
    intervals.push_back(itv);
    while (in.peek() == ',') {
        in.get();
        in >> itv;
        intervals.push_back(itv);
    }
    in >> c;
    assert(c == ']');
    return in;
}

std::ostream& operator << (std::ostream &out,
                           const std::vector<Interval> &intervals) {
    out << '[';
    const int n = intervals.size();
    for (int i = 0; i < n; i++) {
        out << intervals[i];
        if (i != n-1) out << ',';
    }
    out << ']';
    return out;
}
