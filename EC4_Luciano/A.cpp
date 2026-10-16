#include <iostream>
#include <vector>
using namespace std;

vector<int> cur;

void gen(int rem, int mx) {
    if (rem == 0) {
        for (int i = 0; i < (int)cur.size(); ++i)
            cout << cur[i] << (i + 1 < (int)cur.size() ? ' ' : '\n');
        return;
    }
    for (int v = (rem < mx ? rem : mx); v >= 1; --v) {
        cur.push_back(v);
        gen(rem - v, v);
        cur.pop_back();
    }
}

int main() {
    int n;
    cin >> n;
    gen(n, n);
    return 0;
}