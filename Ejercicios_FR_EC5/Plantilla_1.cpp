// Checklist antes de enviar:
//   [ ] ¿Leo TODO con cin? (nada escrito a mano)
//   [ ] ¿Hay varios casos de prueba? -> limpiar estructuras entre casos
//   [ ] ¿Vértices de 1..n o de 0..n-1?
//   [ ] ¿No dirigido? -> agregar la arista en LAS DOS listas
//   [ ] ¿Sumas o claves grandes? -> long long
//   [ ] ¿Límites de los for = tamaño real de lo que recorro?
//   [ ] ¿Probé TODOS los ejemplos del enunciado?
// =====================================================================
#include <iostream>
#include <vector>
using namespace std;

void resolver() {
    int n, m;
    cin >> n >> m;
    // ... lógica del problema ...
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int T = 1;
    // cin >> T;              // <- descomentar si hay varios casos de prueba
    while (T--) resolver();   // las variables dentro de resolver() se reinician solas

    return 0;
}