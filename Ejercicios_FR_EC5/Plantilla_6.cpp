// =====================================================================
// Úsala cuando: "k-ésimo vecino", "cuántos vecinos son <= x", rangos.
// Ordenar todas las listas una vez: O(m log m).
// k-ésimo: adj[u][k-1] -> O(1) | cuántos <= x: upper_bound -> O(log deg)
// Problema modelo: D (Agenda de contactos)
// =====================================================================
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//vecinos_ordenados
int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int u = 1; u <= n; u++) sort(adj[u].begin(), adj[u].end());

    auto kesimo = [&](int u, int k) {                       // -1 si no existe
        return (k > (int)adj[u].size()) ? -1 : adj[u][k - 1];
    };
    auto menoresIguales = [&](int u, int x) {               // vecinos <= x
        return int(upper_bound(adj[u].begin(), adj[u].end(), x) - adj[u].begin());
    };
    auto menoresEstricto = [&](int u, int x) {              // vecinos < x
        return int(lower_bound(adj[u].begin(), adj[u].end(), x) - adj[u].begin());
    };
    // Vecinos en [L, R]: menoresIguales(u, R) - menoresEstricto(u, L)
    // ¿v es vecino de u?: binary_search(adj[u].begin(), adj[u].end(), v)

    (void)kesimo; (void)menoresIguales; (void)menoresEstricto;
    return 0;
}