// Un array guarda datos del MISMO tipo en posiciones CONTIGUAS de memoria.
// Esa contigüidad es lo que permite el acceso O(1): la dirección del
// elemento i se calcula como  base + i * sizeof(T).
// COMPLEJIDADES
//   Acceso    A[i]              O(1)
//   Búsqueda  (no ordenado)     O(n)
//   Búsqueda  (ordenado, bin.)  O(log n)
//   Inserción al inicio         O(n)   -- hay que correr todo
//   Inserción al medio          O(n)
//   Inserción al final          O(1) amortizado si hay capacidad, O(n) si toca redimensionar
//   Eliminación                 O(n)   (salvo al final: O(1))
// ESPACIO: O(n)

#include <iostream>
#include <cstdlib>   // malloc / free (¡faltaba en la versión original!)
using namespace std;
 
// Utilidades básicas sobre arrays crudos (sin STL)

template <typename T>
void imprimir(const T* a, int n) {
    for (int i = 0; i < n; ++i) cout << a[i] << " ";
    cout << '\n';
}
 
// Búsqueda lineal. Devuelve el índice, o -1 si no está. O(n)
template <typename T>
int buscar_lineal(const T* a, int n, const T& objetivo) {
    for (int i = 0; i < n; ++i)
        if (a[i] == objetivo) return i;
    return -1;
}
 
// Búsqueda binaria (el array DEBE estar ordenado). O(log n)
template <typename T>
int buscar_binaria(const T* a, int n, const T& objetivo) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;      // evita overflow de (lo+hi)
        if (a[mid] == objetivo) return mid;
        if (a[mid] < objetivo) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}
 
// Inserta 'valor' en la posición 'pos'. 'n' es la cantidad actual de
// elementos y 'cap' la capacidad total. Devuelve el nuevo n. O(n)
template <typename T>
int insertar_en(T* a, int n, int cap, int pos, const T& valor) {
    if (n >= cap || pos < 0 || pos > n) return n;   // no cabe / posición inválida
    for (int i = n; i > pos; --i) a[i] = a[i - 1];  // corre a la derecha
    a[pos] = valor;
    return n + 1;
}
 
// Elimina el elemento en 'pos'. Devuelve el nuevo n. O(n)
template <typename T>
int eliminar_en(T* a, int n, int pos) {
    if (pos < 0 || pos >= n) return n;
    for (int i = pos; i < n - 1; ++i) a[i] = a[i + 1];  // corre a la izquierda
    return n - 1;
}
 
// Invierte el array in-place. O(n), espacio O(1)
template <typename T>
void invertir(T* a, int n) {
    for (int i = 0, j = n - 1; i < j; ++i, --j) {
        T tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
}
 
int main() {
    // Fast I/O. La forma correcta (la versión encadenada
    // cin.tie(0)->sync_with_stdio(false) funciona por accidente:
    // sync_with_stdio es un método ESTÁTICO de ios_base).
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // OJO: si usas printf/scanf mezclado con cin/cout, NO desactives la sync.
 
    // Formas de declarar arrays

    // 1) Estático (stack). Tamaño fijo, se libera solo al salir del scope.
    int A[10];
    for (int i = 0; i < 10; ++i) A[i] = i * i;
    cout << "A (estatico): "; imprimir(A, 10);
 
    // 2) Dinámico estilo C (heap)
    int* a = (int*) malloc(10 * sizeof(int));
 
    // 3) Dinámico estilo C++ (heap) -- ESTA es la que debes usar
    int* b = new int[10];
 
    // En C++ moderno el tamaño puede ser una variable en tiempo de ejecución
    // cuando usas new/malloc. Con arrays estáticos debe ser constante.
    int n = 5;
    int* c = new int[n];
    for (int i = 0; i < n; ++i) c[i] = n - i;   // {5,4,3,2,1}
 
    cout << "c original:  "; imprimir(c, n);
    invertir(c, n);
    cout << "c invertido: "; imprimir(c, n);    // {1,2,3,4,5}
 
    cout << "buscar_binaria(4) -> " << buscar_binaria(c, n, 4) << '\n';  // 3
    cout << "buscar_lineal(9)  -> " << buscar_lineal(c, n, 9) << '\n';   // -1
 
    // Insertar y eliminar necesitan capacidad de sobra
    int cap = 10;
    int* d = new int[cap];
    int m = 0;
    for (int i = 0; i < 5; ++i) m = insertar_en(d, m, cap, m, i);  // 0 1 2 3 4
    m = insertar_en(d, m, cap, 0, 99);                             // 99 0 1 2 3 4
    m = eliminar_en(d, m, 3);                                      // 99 0 1 3 4
    cout << "d: "; imprimir(d, m);
 
    // LIBERACIÓN DE MEMORIA -- obligatoria, si no hay memory leak.
    // Regla: malloc -> free,  new -> delete,  new[] -> delete[]
    // Nunca mezclar (malloc + delete es comportamiento indefinido).
    free(a);
    delete[] b;
    delete[] c;
    delete[] d;
    // A no se libera: vive en el stack.
 
    return 0;
}