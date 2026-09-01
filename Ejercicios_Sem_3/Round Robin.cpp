// B. Round Robin  -  simulacion de planificacion por quantum
// Cola circular implementada sobre arreglo. Sin STL.
// Complejidad: O(n + Sigma(time)/q) tiempo, O(n) espacio.

#include <iostream>
using namespace std;

const int MAXN = 100005;      // n <= 100000

struct Cola {
    int datos[MAXN];
    int frente;               // posicion del primero de la fila
    int atras;                // posicion donde entrara el proximo
    int tam;                  // cuantos hay ahora mismo

    void iniciar() {
        frente = 0;
        atras  = 0;
        tam    = 0;
    }

    bool vacia() {
        return tam == 0;
    }

    void encolar(int x) {
        datos[atras] = x;
        atras = (atras + 1) % MAXN;   // al llegar al final, vuelve al inicio
        tam++;
    }

    int desencolar() {
        int x = datos[frente];
        frente = (frente + 1) % MAXN;
        tam--;
        return x;
    }
};

Cola cola;
char nombre[MAXN][11];
int  tiempo[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; i++)
        cin >> nombre[i] >> tiempo[i];

    cola.iniciar();
    for (int i = 0; i < n; i++)
        cola.encolar(i);

    int reloj = 0;

    while (!cola.vacia()) {
        int i = cola.desencolar();

        int corre = (tiempo[i] < q) ? tiempo[i] : q;

        reloj     += corre;   // el reloj SOLO SUBE (suma acumulada)
        tiempo[i] -= corre;   // el restante SOLO BAJA

        if (tiempo[i] > 0)
            cola.encolar(i);                              // le falta: al final
        else
            cout << nombre[i] << " " << reloj << endl;    // termino
    }

    return 0;
}