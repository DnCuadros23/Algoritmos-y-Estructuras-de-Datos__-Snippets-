#include <iostream>
using namespace std;
const int MAXN = 100005;
int L[MAXN];   // L[i] = caja inmediatamente a la IZQUIERDA de i
int R[MAXN];   // R[i] = caja inmediatamente a la DERECHA  de i
// El nodo 0 es CENTINELA: R[0] = primera caja, L[0] = ultima caja.
int n, m;
// conecta a -> b (a queda a la izquierda de b)
inline void enlazar(int a, int b) {
    R[a] = b;
    L[b] = a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int caso = 1;
    while (cin >> n >> m) {

        // --- inicializar la linea 1 2 3 ... n como lista circular con centinela 0
        for (int i = 1; i <= n; i++) {
            L[i] = i - 1;
            R[i] = (i + 1) % (n + 1);   // R[n] = 0
        }
        R[0] = 1;
        L[0] = n;

        bool inv = false;   // true = la linea real esta al reves de como la guardo

        for (int k = 0; k < m; k++) {
            int op;
            cin >> op;

            if (op == 4) {          // invertir: O(1), solo cambio el flag
                inv = !inv;
                continue;
            }

            int X, Y;
            cin >> X >> Y;

            // el swap es simetrico: normalizo para que X este a la izquierda de Y
            if (op == 3 && R[Y] == X) {
                int t = X;
                X = Y;
                Y = t;
            }

            // si la linea esta invertida, "izquierda" y "derecha" se intercambian
            if (op != 3 && inv)
                op = 3 - op;
            // 1 <-> 2

            // comandos que se ignoran
            if (op == 1 && L[Y] == X)
                continue;
            if (op == 2 && R[Y] == X)
                continue;

            int lx = L[X],
            rx = R[X],
            ly = L[Y],
            ry = R[Y];

            if (op == 1) {                 // X va inmediatamente a la izquierda de Y
                enlazar(lx, rx);           // saco X
                enlazar(ly, X);
                enlazar(X, Y);
            } else if (op == 2) {          // X va inmediatamente a la derecha de Y
                enlazar(lx, rx);           // saco X
                enlazar(Y, X);
                enlazar(X, ry);
            } else {                       // op == 3: intercambiar X e Y
                if (R[X] == Y) {           // caso especial: son vecinas
                    enlazar(lx, Y);
                    enlazar(Y, X);
                    enlazar(X, ry);
                } else {                   // caso general: estan separadas
                    enlazar(lx, Y);
                    enlazar(Y, rx);
                    enlazar(ly, X);
                    enlazar(X, ry);
                }
            }
        }

        // --- recorrer y sumar posiciones impares (en el orden GUARDADO)
        long long suma = 0;
        int u = R[0];
        for (int i = 1; i <= n; i++) {
            if (i & 1)
                suma += u;
            u = R[u];
        }

        // si la linea real esta invertida y n es par,
        // las impares reales son las pares guardadas -> complemento
        if (inv && n % 2 == 0) {
            long long total = (long long)n * (n + 1) / 2;
            suma = total - suma;
        }

        cout << "Case " << caso++ << ": " << suma <<endl;
    }
    return 0;
}