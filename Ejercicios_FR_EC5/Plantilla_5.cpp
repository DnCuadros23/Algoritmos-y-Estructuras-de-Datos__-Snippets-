// =====================================================================
// Úsala cuando: preguntan MUCHAS veces si dos vértices son adyacentes.
// Buscar en adj[u] cuesta O(deg u) -> puede dar TLE. Hash: O(1) promedio.
// Clave única: u * (n + 1) + v   (long long, porque pasa de 2^31)
// No dirigido: NORMALIZAR (menor primero) al guardar y al consultar.
// Problemas modelo: C (mutuos, set), E (cables múltiples, map)
// =====================================================================
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;
//Hash_aristas
int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, m, q;
    cin >> n >> m >> q;

    // Dirigido (u -> v distinto de v -> u)
    auto claveDir = [n](long long u, long long v) { return u * (n + 1) + v; };
    // No dirigido ({u, v} = {v, u})
    auto claveNoDir = [n](long long u, long long v) {
        if (u > v) std::swap(u, v);
        return u * (n + 1) + v;
    };

    unordered_set<long long> existe;            // ¿existe la arista?
    unordered_map<long long, int> cuantas;      // ¿cuántas aristas? (múltiples)
    existe.reserve(2 * m + 1);
    cuantas.reserve(2 * m + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        existe.insert(claveDir(u, v));
        cuantas[claveNoDir(u, v)]++;
    }

    while (q--) {
        int u, v;
        cin >> u >> v;
        bool hay = existe.count(claveDir(u, v));
        auto it = cuantas.find(claveNoDir(u, v));     // find: NO crea entradas vacías
        int total = (it == cuantas.end()) ? 0 : it->second;
        cout << hay << ' ' << total << '\n';
    }

    // Mutuos (dirigido): contar a->b con b->a, solo si a < b para no duplicar
    // if (a < b && existe.count(claveDir(b, a))) mutuos++;

    return 0;
}