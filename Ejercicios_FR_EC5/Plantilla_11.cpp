// =====================================================================
// Úsala cuando: "estados", "jugadas", "movimientos", jarras, puzzles.
// El grafo NO se guarda: los vecinos se generan con las reglas.
// Cuidado: jugadas que NO cambian el estado no son aristas;
//          dos jugadas al mismo destino cuentan como UNA arista.
// Contar -> recorrer todos los estados | Distancia mínima -> BFS de estados.
// Problema modelo: G (Las jarras)
// =====================================================================
#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
//grafo estados
int A, B;

// Genera los vecinos de (a, b) aplicando todas las jugadas
array<pair<int,int>, 6> vecinos(int a, int b) {
    int d12 = min(a, B - b);          // de la 1 a la 2: lo que tengo o lo que cabe
    int d21 = min(b, A - a);          // de la 2 a la 1
    return {{
        {A, b}, {a, B},               // llenar 1, llenar 2
        {0, b}, {a, 0},               // vaciar 1, vaciar 2
        {a - d12, b + d12},           // pasar 1 -> 2
        {a + d21, b - d21}            // pasar 2 -> 1
    }};
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int objetivo;
    cin >> A >> B >> objetivo;

    // BFS de estados: mínimo de jugadas para tener 'objetivo' litros en alguna jarra
    vector<vector<int>> dist(A + 1, vector<int>(B + 1, -1));
    queue<pair<int,int>> cola;
    dist[0][0] = 0;
    cola.push({0, 0});

    while (!cola.empty()) {
        auto [a, b] = cola.front();
        cola.pop();
        if (a == objetivo || b == objetivo) {
            cout << dist[a][b] << '\n';
            return 0;
        }
        for (auto [na, nb] : vecinos(a, b)) {
            if (dist[na][nb] != -1) continue;   // también descarta (na,nb) == (a,b)
            dist[na][nb] = dist[a][b] + 1;
            cola.push({na, nb});
        }
    }

    cout << -1 << '\n';                       // imposible
    return 0;
}