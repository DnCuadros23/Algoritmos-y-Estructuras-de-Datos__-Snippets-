
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//arreglo de estados de cada nodo
// - vis[1...n] -> no visitado, en proceso, finalizado
//arreglo de enteros del nodo en el DFS-Tree
// - pad[1...n]

//-Tiempo de entrada y tiempo de salida (no siempre va)
// in[i...n] ---- Timestamps
// out[1...n]
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
const int N = 1000;
int n;
int m;
char s[N][N + 1];
int DFS(int x, int y) {
    s[x][y] = '.';
    int res = 1;
    for (int k = 0; k < 4; ++k) {
        int vx = x + dx[k];
        int vy = y + dy[k];
        if (vx < 0 or vx >= n or vy < 0 or vy >= m) continue;
        if (s[vx][vy] == '.') continue;
        res += DFS(vx, vy);
    }
    return res;
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> s[i];
    int cnt_islas = 0, max_isla = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i][j] == '.') continue;
            max_isla = max(max_isla, DFS(i, j));
            ++cnt_islas;
        }
    }
    cout << cnt_islas << " " << max_isla << '\n';
    return 0;
}
