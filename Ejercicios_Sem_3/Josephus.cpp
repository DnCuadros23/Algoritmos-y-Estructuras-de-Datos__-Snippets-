// D. Josephus  -  eliminar uno de cada dos en un circulo
// Lista CIRCULAR SIMPLEMENTE enlazada. Sin STL.
// Complejidad: O(n) tiempo, O(n) espacio.

#include <iostream>
using namespace std;

struct Nodo {
    int valor;
    Nodo* sig;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Nodo* head = new Nodo;
    head->valor = 1;
    head->sig   = nullptr;
    Nodo* tail = head;                 // tail = ultimo nodo creado
    for (int i = 2; i <= n; i++) {
        Nodo* nuevo = new Nodo;
        nuevo->valor = i;
        nuevo->sig   = nullptr;
        tail->sig = nuevo;             // engancho el nuevo al final
        tail = nuevo;                  // ahora el nuevo es el ultimo
    }
    tail->sig = head;

    Nodo* cur = head;                  // estoy parado en cur; muere cur->sig
    int vivos = n;

    while (vivos > 1) {
        Nodo* muere = cur->sig;        // guardo al que muere ANTES de desengancharlo

        cout << muere->valor << ' ';

        cur->sig = muere->sig;         // salto por encima del muerto
        delete muere;                  // libero memoria
        vivos--;

        cur = cur->sig;                // avanzo al siguiente sobreviviente
    }

    cout << cur->valor << endl;
    delete cur;

    return 0;
}