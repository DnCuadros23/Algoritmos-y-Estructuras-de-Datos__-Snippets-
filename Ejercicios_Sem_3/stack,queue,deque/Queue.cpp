#include<bits/stdc++.h>
using namespace::std;
template<typename data_type>
struct Queue {
    struct QueueNode {
        data_type data;
        QueueNode* next;
        QueueNode() {
        }
        QueueNode(data_type data) : data(data), next(nullptr) {}
    };
    QueueNode* _front, *_back;
    Queue() {
        _front = nullptr;
        _back = nullptr;
    }
    void push(data_type value) {
        if (_front == nullptr) {
            _front = new QueueNode(value);
            _back = _front;
        }
        else {
            _back->next = new QueueNode(value);
            _back = _back -> next;
        }
    }
    void pop() {
        if (_front != nullptr) {
            _front = _front -> next;
        }
    }
    data_type front() {
        return _front == nullptr ? data_type() : _front -> data;
    }
    bool empty() {
        return _front == nullptr;
    }
};
int main() {
    int n, m;
    cin >> n >> m;
    Queue<pair<int, int>> Q;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        Q.push(make_pair(x, i));
    }
    int res = -1;
    while (not Q.empty()) {
        int x, i;
        tie(x, i) = Q.front(); Q.pop();
        if (x <= m) {
            res = i;
        }
        else {
            Q.push(make_pair(x - m, i));
        }
    }
    cout << res << '\n';
    return 0;
}
