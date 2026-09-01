#include <iostream>
using namespace std;

const int MAXN = 205;
int p[MAXN], ans[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int q;
    cin >> q;
    while (q--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> p[i];

        // TODO: calcular ans[1..n]

        for (int i = 1; i <= n; i++) cout << ans[i] << " ";
        cout << endl;
    }
    return 0;
}