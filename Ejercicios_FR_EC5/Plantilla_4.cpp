// Úsala cuando: solo piden grados, grado de entrada/salida, o Euler.
// NO necesitas lista de adyacencia: basta un vector de contadores.
// Lazo (u == v): grado[u]++ dos veces -> suma 2 automáticamente.
// Lema del apretón de manos: suma de grados = 2m -> #impares siempre es par.
// Problemas modelo: B (Königsberg), C (grado de entrada)
// =====================================================================
#include <iostream>
#include <vector>
using namespace std;
//Grados euler
int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<int> grado(n + 1, 0);
    // Dirigido: vector<int> entrada(n + 1, 0), salida(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        grado[u]++;
        grado[v]++;
        // Dirigido: salida[u]++; entrada[v]++;
    }

    // Euler (REQUIERE grafo conexo; si no lo garantizan, verificar con BFS)
    int impares = 0;
    for (int u = 1; u <= n; u++)
        if (grado[u] % 2 != 0) impares++;

    if (impares == 0)      cout << "CIRCUITO\n";   // empieza y termina en el mismo
    else if (impares == 2) cout << "CAMINO\n";     // de un impar al otro
    else                   cout << "IMPOSIBLE\n";

    // Máximo con desempate por menor índice: usar '>' ESTRICTO
    // int mejor = 1;
    // for (int u = 2; u <= n; u++) if (grado[u] > grado[mejor]) mejor = u;

    return 0;
}