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

int read_stack(int pending, Stack<int> &S) {
    if (pending == 0) return 0;
    int x;
    cin >> x;
    int res = read_stack(pending - 1, S);
    S.push(x);
    return res + x;
}

int main() {
    array<int, 3> n;
    for (int i = 0; i < 3; ++i) cin >> n[i];
    array<int, 3> h;
    vector<Stack<int>> S(3, Stack<int>());
    for (int i = 0; i < 3; ++i) {
        h[i] = read_stack(n[i], S[i]);
    }
    while (!(h[0] == h[1] and h[1] == h[2])) {
        int highest = 0;
        for (int i = 1; i < 3; ++i) {
            if (h[highest] < h[i]) {
                highest = i;
            }
        }
        int x = S[highest].top();
        h[highest] -= x;
        S[highest].pop();
    }
    cout << h[0] << '\n';
    return 0;
}