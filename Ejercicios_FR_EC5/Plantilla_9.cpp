// =====================================================================
// Úsala cuando: laberinto, "pasos mínimos en el tablero",
//               "distancia al fuego/salida/hospital MÁS CERCANO".
// Multifuente: TODAS las fuentes entran a la cola al inicio con dist 0.
//              Un solo BFS: O(n * m). (Un BFS por fuente repetiría trabajo.)
// Para una sola fuente: meter solo esa casilla al inicio.
// =====================================================================
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>
using namespace std;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
//bfs grillas multifuente
int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (auto& fila : grid) cin >> fila;

    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int,int>> cola;

    // Fuentes: todas las casillas 'F' (ajustar el carácter al problema)
    for (int x = 0; x < n; x++)
        for (int y = 0; y < m; y++)
            if (grid[x][y] == 'F') {
                dist[x][y] = 0;
                cola.push({x, y});
            }

    while (!cola.empty()) {
        auto [x, y] = cola.front();
        cola.pop();
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;  // fuera
            if (grid[nx][ny] == '#') continue;                      // pared
            if (dist[nx][ny] != -1) continue;                       // ya visitada
            dist[nx][ny] = dist[x][y] + 1;
            cola.push({nx, ny});
        }
    }

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) cout << dist[x][y] << ' ';
        cout << '\n';
    }

    return 0;
}