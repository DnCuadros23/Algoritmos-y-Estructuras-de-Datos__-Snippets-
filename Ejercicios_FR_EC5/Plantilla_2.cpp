// =====================================================================
// Úsala cuando: necesitas recorrer los vecinos de un vértice (casi siempre).
// Memoria: O(n + m) | Vecinos de u: O(deg u) | Todos los vecinos: O(n + m)
// Señal para NO usarla: solo piden grados, o es una grilla/estados (implícito).
// =====================================================================
#include <iostream>
#include <vector>
#include <utility>
using namespace std;
//Lista de adyacencia

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    // --- Sin pesos ---
    vector<vector<int>> adj(n + 1);              // índices 1..n
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);                     // BORRAR si el grafo es dirigido
    }

    // --- Con pesos (reemplaza el bloque de arriba) ---
    // vector<vector<pair<int,int>>> adj(n + 1); // (vecino, peso)
    // adj[u].push_back({v, w});
    // adj[v].push_back({u, w});
    // for (auto [v, w] : adj[u]) { ... }

    // --- Uso típico ---
    for (int u = 1; u <= n; u++) {
        int grado = adj[u].size();               // grado en O(1)
        for (int v : adj[u]) {                   // recorrer vecinos
            (void)v;                             // ... usar v ...
        }
        (void)grado;
    }

    return 0;
}