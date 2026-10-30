// =====================================================================
// Úsala cuando: "amigos en común", "vecinos compartidos" entre u y v.
// Señal: el enunciado limita la SUMA de deg(u)+deg(v) de las consultas.
// Costo por consulta: O(deg u + deg v)
// REGLA DE ORO: desmarcar SOLO lo que marcaste (nunca reiniciar todo: O(n))
// Problema modelo: F (Amigos en común)
// =====================================================================
#include <iostream>
#include <vector>
using namespace std;
//vecinos comunes
int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<char> marca(n + 1, 0);        // char > bool (vector<bool> es lento)

    while (q--) {
        int u, v;
        cin >> u >> v;

        for (int x : adj[u]) marca[x] = 1;          // 1. marcar vecinos de u

        int comunes = 0;
        for (int y : adj[v]) if (marca[y]) comunes++; // 2. contar en vecinos de v

        for (int x : adj[u]) marca[x] = 0;          // 3. limpiar SOLO lo marcado

        cout << comunes << '\n';
    }

    return 0;
}