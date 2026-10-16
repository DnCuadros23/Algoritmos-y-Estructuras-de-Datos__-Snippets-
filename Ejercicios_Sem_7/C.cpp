
#include<bits/stdc++.h>
using namespace::std;
int sift_down(int n, int i, vector<int> &a) {
    int res = 0;
    while (true) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int menor = i;
        if (l < n and a[l] < a[menor]) menor = l;
        if (r < n and a[r] < a[menor]) menor = r;
        if (menor == i) break;
        ++res;
        swap(a[menor], a[i]);
        i = menor;
    }
    return res;
}
int build_heap(vector<int> &a) {
    int res = 0;
    const int n = a.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        res += sift_down(n, i, a);
    }
    return res;
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    cout << build_heap(a) << '\n';
    for (int i = 0; i < n; ++i) cout << a[i] << " \n"[i + 1 == n];
    return 0;
}
