
#include <iostream>
using namespace std;
const int MAXN = 100005;

struct Nodo {
    int   caja;
    Nodo* izq;
    Nodo* der;
};

// ref[i] = puntero al nodo de la caja i.
// Sin esto habria que BUSCAR el nodo X -> O(n) por comando -> TLE.
Nodo* ref_[MAXN];

inline void enlazar(Nodo* a, Nodo* b) {
    a->der = b;
    b->izq = a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, caso = 1;

    while (cin >> n >> m) {

        Nodo* cent = new Nodo;             // centinela: no es una caja real
        cent->caja = 0;

        Nodo* ant = cent;
        for (int i = 1; i <= n; i++) {
            Nodo* nuevo = new Nodo;
            nuevo->caja = i;
            ref_[i] = nuevo;               // anoto su direccion
            enlazar(ant, nuevo);
            ant = nuevo;                   // avanzar (el patron de siempre)
        }
        enlazar(ant, cent);                // cierro el circulo

        bool inv = false;

        for (int k = 0; k < m; k++) {
            int op;
            cin >> op;

            if (op == 4) {
                inv = !inv;
                continue;
            }

            int a, b;
            cin >> a >> b;
            Nodo* X = ref_[a];             // O(1)
            Nodo* Y = ref_[b];             // O(1)

            // normalizo el swap: X queda a la izquierda de Y
            if (op == 3 && Y->der == X) {
                Nodo* t = X; X = Y; Y = t;
            }

            // si la linea esta invertida, izquierda y derecha se intercambian
            if (op != 3 && inv) op = 3 - op;

            // comandos que se ignoran
            if (op == 1 && Y->izq == X)
                continue;
            if (op == 2 && Y->der == X)
                continue;

            Nodo* lx = X->izq;
            Nodo* rx = X->der;
            Nodo* ly = Y->izq;
            Nodo* ry = Y->der;

            if (op == 1) {                 // X a la izquierda de Y
                enlazar(lx, rx);           // saco X
                enlazar(ly, X);
                enlazar(X, Y);
            } else if (op == 2) {          // X a la derecha de Y
                enlazar(lx, rx);           // saco X
                enlazar(Y, X);
                enlazar(X, ry);
            } else {                       // intercambiar X e Y
                if (X->der == Y) {         // vecinas
                    enlazar(lx, Y);
                    enlazar(Y, X);
                    enlazar(X, ry);
                } else {                   // separadas
                    enlazar(lx, Y);
                    enlazar(Y, rx);
                    enlazar(ly, X);
                    enlazar(X, ry);
                }
            }
        }

        long long suma = 0;
        Nodo* u = cent->der;
        for (int i = 1; i <= n; i++) {
            if (i & 1)
                suma += u->caja;
            u = u->der;
        }
        if (inv && n % 2 == 0) {
            long long total = (long long)n * (n + 1) / 2;
            suma = total - suma;
        }

        cout << "Case " << caso++ << ": " << suma << "\n";

        Nodo* p = cent->der;
        while (p != cent) {
            Nodo* q = p->der;
            delete p;
            p = q;
        }
        delete cent;
    }

    return 0;
}