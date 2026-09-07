#include<bits/stdc++.h>
using namespace::std;

template<typename data_type>
struct Stack {

    struct StackNode {
        data_type data;
        StackNode* next;

        StackNode(data_type data) : data(data), next(nullptr) {}
    };

    StackNode* _top;

    Stack() {
        _top = nullptr;
    }

    void push(data_type value) {
        StackNode* new_node = new StackNode(value);
        new_node -> next = _top;
        _top = new_node;
    }

    void pop() {
        if (_top != nullptr) {
            _top = _top -> next;
        }
    }

    data_type top() {
        return _top == nullptr ? data_type() : _top -> data;
    }

    bool empty() {
        return _top == nullptr;
    }
};

template<typename data_type>
struct AssociativeQueue {
    Stack<pair<data_type, data_type>> in, out;

    AssociativeQueue() {

    }

    void push(data_type value) {
        if (in.empty()) {
            in.push(make_pair(value, value));
        }
        else {
            in.push(make_pair(value, in.top().second + value));
        }
    }

    void pop() {
        if (out.empty()) {
            while (not in.empty()) {
                data_type value = in.top().first;
                in.pop();
                if (out.empty()) {
                    out.push(make_pair(value, value));
                }
                else {
                    out.push(make_pair(value, value + out.top().second));
                }
            }
        }
        out.pop();
    }

    data_type all() {
        if (out.empty()) return in.top().second;
        if (in.empty()) return out.top().second;
        return out.top().second + in.top().second;
    }
};

template<int MOD>
struct ModularMatrix {
    array<array<int, 2>, 2> M;

    ModularMatrix() {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                M[i][j] = 0;
            }
        }
    }

    ModularMatrix operator + (const ModularMatrix &rhs) const {
        ModularMatrix res;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                long long cur = 0;
                for (int k = 0; k < 2; ++k) {
                    cur += 1ll * M[i][k] * rhs.M[k][j];
                }
                res.M[i][j] = cur % MOD;
            }
        }
        return res;
    }

    int trace() {
        return (M[0][0] + M[1][1]) % MOD;
    }

    friend istream& operator >> (istream& is, ModularMatrix& M) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                is >> M.M[i][j];
            }
        }
        return is;
    }
};

using Matrix = ModularMatrix<1000000007>;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<Matrix> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    while (q--) {
        int d;
        cin >> d;
        AssociativeQueue<Matrix> Q;
        for (int i = 0; i + 1 < d; ++i) {
            Q.push(a[i]);
        }
        int res = INT_MIN;
        for (int i = d - 1; i < n; ++i) {
            Q.push(a[i]);
            if (i >= d) Q.pop();
            res = max(res, Q.all().trace());
        }
        cout << res << '\n';
    }
    return 0;
}
