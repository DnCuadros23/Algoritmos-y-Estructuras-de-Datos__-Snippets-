// =====================================================================
// Componentes: "cuántos grupos/islas/redes", "¿u y v están conectados?"
//   -> lanzar BFS desde cada vértice NO visitado; todo lo que alcanza
//      recibe la misma etiqueta. Total sigue siendo O(n + m).
// Bipartito: "dos equipos", "colorear con 2 colores", "sin ciclos impares"
//   -> color = paridad de la distancia. Si una arista une dos vértices del
//      MISMO color, hay ciclo impar -> NO es bipartito.
// =====================================================================
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
//componentes bipartito
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

    vector<int> comp(n + 1, -1);       // comp[u] = id de su componente
    vector<int> color(n + 1, -1);      // 0 / 1 (paridad de la distancia)
    int numComp = 0;
    bool bipartito = true;

    for (int s = 1; s <= n; s++) {
        if (comp[s] != -1) continue;   // ya pertenece a una componente

        queue<int> cola;
        comp[s] = numComp;
        color[s] = 0;
        cola.push(s);

        while (!cola.empty()) {
            int u = cola.front();
            cola.pop();
            for (int v : adj[u]) {
                if (comp[v] == -1) {
                    comp[v] = numComp;
                    color[v] = 1 - color[u];          // capa siguiente: otro color
                    cola.push(v);
                } else if (color[v] == color[u]) {
                    bipartito = false;                 // arista dentro de la misma capa
                }
            }
        }
        numComp++;
    }

    cout << numComp << ' ' << (bipartito ? "SI" : "NO") << '\n';
    // ¿u y v conectados?  ->  comp[u] == comp[v]

    return 0;
}