// Úsala cuando: el input es un plano de '#' y '.', laberinto, tablero.
// NO construyas lista de adyacencia: los vecinos se calculan con dx/dy.
// Convención: x = fila, y = columna -> grid[x][y]
// Problema modelo: A (Perímetro del terreno)
// =====================================================================
#include <iostream>
#include <vector>
#include <string>
using namespace std;
//Grilla_vecinos
const int dx[4] = {-1, 1, 0, 0};    // arriba, abajo, izquierda, derecha
const int dy[4] = {0, 0, -1, 1};
// 8 direcciones (si cuentan diagonales):
// const int dx[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
// const int dy[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, m;                                   // n filas, m columnas
    cin >> n >> m;
    vector<string> grid(n);
    for (auto& fila : grid) cin >> fila;

    auto dentro = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    };

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            if (grid[x][y] != '#') continue;    // solo casillas que son vértices

            int grado = 0;
            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k], ny = y + dy[k];
                if (dentro(nx, ny) && grid[nx][ny] == '#') grado++;
            }
            // ... usar grado ...
        }
    }

    // Si necesitas arreglos por vértice (dist, visitado): id = x * m + y  (0 .. n*m-1)
    return 0;
}