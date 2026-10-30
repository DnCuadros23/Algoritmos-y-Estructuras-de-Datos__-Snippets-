#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main() {
    cin.tie(0)->sync_with_stdio(false);
    int N, D, k;
    cin >> N >> D >> k;
    vector<int> salto(N + 1);
    for (int x = 1; x <= N; x++) salto[x] = x;
    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        salto[a] = b;
    }
    vector<int> dist(N + 1, -1);
    queue<int> cola;
    dist[1] = 0;
    cola.push(1);

    while (!cola.empty()) {
        int x = cola.front();
        cola.pop();
        if (x == N) break;
        for (int d = 1; d <= D && x + d <= N; d++) {
            int y = salto[x + d];
            if (dist[y] == -1) {
                dist[y] = dist[x] + 1;
                cola.push(y);
            }
        }
    }
    cout << dist[N] <<'\n';
    return 0;
}