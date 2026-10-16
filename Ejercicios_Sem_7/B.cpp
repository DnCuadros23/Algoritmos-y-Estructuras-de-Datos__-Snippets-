
#include<bits/stdc++.h>
using namespace::std;
int left(int p) {
    return (p << 1) | 1;
}
int right(int p) {
    return (p << 1) + 2;
}
bool check_heap(int n, vector<int> &a) {
    for (int i = 0; left(i) < n; ++i) {
        if (a[left(i)] < a[i]) return false;
        if (right(i) < n and a[right(i)] < a[i]) return false;
    }
    return true;
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        cout << (check_heap(n, a) ? "SI" : "NO") << '\n';
    }
    return 0;
}
