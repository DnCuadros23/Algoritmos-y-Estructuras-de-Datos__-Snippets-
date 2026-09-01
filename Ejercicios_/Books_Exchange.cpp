#include <iostream>
using namespace std;

const int MAXN = 205;
int p[MAXN], ans[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int q;
    cin >> q;
    while (q--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> p[i];
        for (int i = 1; i <= n; i++)
            ans[i] = 0; //Se crean arreglos segun el tamaño

        for (int inicio = 1; inicio <= n; inicio++) {
            if (ans[inicio] != 0)
                continue; //Si ya no esta lleno ese arreglo entonces continua

            int actual = inicio, largo = 0; //Se inicializa
            do {
                actual = p[actual]; //Se cuenta aunque sea una vez
                largo++;
            }
            while (actual != inicio); //Si es diferente continua, midiendo cuanto es el largo

            actual = inicio;
            do {
                ans[actual] = largo; //Se pone en el arreglo resultado (el largo)
                actual = p[actual]; // Para resolver cuando se repitan
                // Escribir luego mover
            }
            while (actual != inicio); //Mientras que sea diferente
        }

        for (int i = 1; i <= n; i++)
            cout << ans[i] << " ";
        cout << endl;
    }
    return 0;
}