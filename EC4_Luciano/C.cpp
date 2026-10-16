#include <iostream>
using namespace std;

int n;
long long w[12], load[3], best;

void dfs(int i) {
    if (i == n) {
        long long mx = load[0];
        if (load[1] > mx) mx = load[1];
        if (load[2] > mx) mx = load[2];
        if (mx < best) best = mx;
        return;
    }
    for (int p = 0; p < 3; ++p) {
        if (load[p] + w[i] < best) {
            load[p] += w[i];
            dfs(i + 1);
            load[p] -= w[i];
        }
        if (load[p] == 0) break;
    }
}

int main() {
    cin >> n;
    best = 0;
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
        best += w[i];
    }
    dfs(0);
    cout << best << '\n';
    return 0;
}