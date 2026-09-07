
#include <iterator>
#include <bits/stdc++.h>
using namespace std;
template <typename data_type>
struct Deque {
    struct DequeNode {
        data_type data;
        DequeNode* next;
        DequeNode *prev;
        DequeNode(data_type value) : data(value), next(nullptr), prev(nullptr) {};
        DequeNode(): next (nullptr), prev(nullptr) {};

    };
    DequeNode* _front;
    DequeNode* _back;
    Deque() {
        _front = nullptr;
        _back = nullptr;
    }
    void push_back(data_type value) {
        if (_front ==nullptr) {
            _front == new DequeNode (value);
            _back=_front;
        }
        else {
            _back->next = new DequeNode (value);
            _back->next->prev = _back;
            _back = _back->next;

        }
    }
    void push_front(data_type value) {
        if (_front == nullptr) {
            _front = new DequeNode (value);
            _back=_front;

        }
        else {
            _front -> prev = new DequeNode (value);
            _front -> prev -> prev = _front;
            _front =_front->prev;
        }
    }
    void pop_back() {
        if (_back!=nullptr) {
            _back = _back -> prev;

        }
        if (_back==nullptr) {
            _front = nullptr;
        }
        else {
            _back-> next = nullptr;
        }
    }
    void pop_front() {
        if (_front != nullptr) {
            _front = _front -> next;

        }
        if (_front == nullptr) {
            _back = nullptr;

        }
        else {
            _front -> prev = nullptr;
        }
    }
    bool empty() {
        return _front == nullptr;
    }
    data_type front() {
        return _front==nullptr? data_type() : _front->data;

    }
    data_type back() {
        return _back==nullptr? data_type() : _back->data;
    }
};



int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int q;
    cin >> q;
    Deque<int> Q;
    bool reversed = false;
    while (q--) {
        string op;
        cin >> op;
        if (op[0] == 'b') {
            if (Q.empty()) {
                cout << "No job for Ada?" << '\n';
            }
            else {
                cout << (reversed ? Q.front() : Q.back()) << '\n';
                reversed ? Q.pop_front() : Q.pop_back();
            }
        }
        else if (op[0] == 'f') {
            if (Q.empty()) {
                cout << "No job for Ada?" << '\n';
            }
            else {
                cout << (reversed ? Q.back() : Q.front()) << '\n';
                reversed ? Q.pop_back() : Q.pop_front();
            }
        }
        else if (op[0] == 'r') {
            reversed = !reversed;
        }
        else if (op[0] == 'p') {
            int x;
            cin >> x;
            reversed ? Q.push_front(x) : Q.push_back(x);
        }
        else {
            int x;
            cin >> x;
            reversed ? Q.push_back(x) : Q.push_front(x);
        }
    }
    return 0;
}
