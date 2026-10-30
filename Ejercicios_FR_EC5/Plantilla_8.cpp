// =====================================================================
// Úsala cuando: "mínimo número de pasos/saltos/cambios", grafo SIN pesos.
// Idea: explorar por capas con una cola (FIFO). Capa k = distancia k.
// Se marca al ENTRAR a la cola (no al salir) -> cada vértice entra 1 vez.
// Costo: O(n + m) con lista de adyacencia (con matriz sería O(n^2)).
// NO sirve con pesos distintos: minimiza #aristas, no la suma de pesos.
// =====================================================================
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
//bfs
int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);              // BORRAR si es dirigido
    }

    int s = 1, t = n;                     // origen y destino (ajustar al problema)

    vector<int> dist(n + 1, -1);          // -1 = no descubierto (hace de "infinito")
    vector<int> padre(n + 1, -1);
    queue<int> cola;

    dist[s] = 0;
    cola.push(s);
    while (!cola.empty()) {
        int u = cola.front();
        cola.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {          // solo vértices nuevos
                dist[v] = dist[u] + 1;
                padre[v] = u;
                cola.push(v);             // marcado al entrar
            }
        }
    }

    if (dist[t] == -1) {
        cout << -1 << '\n';               // t no es alcanzable desde s
        return 0;
    }

    // Reconstruir camino: seguir padre desde t hasta s e invertir
    vector<int> camino;
    for (int v = t; v != -1; v = padre[v]) camino.push_back(v);
    reverse(camino.begin(), camino.end());

    cout << dist[t] << '\n';
    for (int v : camino) cout << v << ' ';
    cout << '\n';

    return 0;
}