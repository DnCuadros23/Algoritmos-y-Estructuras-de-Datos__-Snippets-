// INVARIANTE:
//   Siempre se cumple  0 <= tam <= capacity,  y las primeras 'tam'
//   posiciones de data contienen los elementos válidos, en orden.
//
// COMPLEJIDADES
//   operator[], size, empty, back    O(1)
//   push_back                        O(1) AMORTIZADO  (O(n) cuando toca duplicar)
//   pop_back                         O(1)
//   insert(pos), erase(pos)          O(n)
//   busqueda lineal                  O(n)
// ESPACIO: O(capacity)
//
// ¿POR QUÉ push_back ES O(1) AMORTIZADO?
//   Duplicar la capacidad hace que las copias totales tras n inserciones
//   sean  1 + 2 + 4 + ... + n  <  2n.  Repartido entre n operaciones da
//   costo constante por operación. Si creciéramos de 1 en 1 sería O(n^2).

#include <iostream>
using namespace std;

template <typename T>
class my_vector {
    T* data;
    int tam;
    int capacity;

    // Redimensiona a nueva_cap (>= tam). O(n)
    void resize_interno(int nueva_cap) {
        T* nuevo = new T[nueva_cap];              // ¡T, no int!
        for (int i = 0; i < tam; ++i) nuevo[i] = data[i];
        delete[] data;
        data = nuevo;
        capacity = nueva_cap;
    }

public:
    my_vector() : data(nullptr), tam(0), capacity(0) {}

    my_vector(int n, const T& valor = T()) : data(nullptr), tam(0), capacity(0) {
        if (n <= 0) return;
        data = new T[n];
        for (int i = 0; i < n; ++i) data[i] = valor;
        tam = capacity = n;
    }

    my_vector(const my_vector& other) {
        tam = other.tam;
        capacity = other.capacity;
        data = capacity ? new T[capacity] : nullptr;   // BUG ORIGINAL: new int[]
        for (int i = 0; i < tam; ++i) data[i] = other.data[i];
    }

    my_vector& operator=(const my_vector& other) {
        if (this == &other) return *this;
        delete[] data;
        tam = other.tam;
        capacity = other.capacity;
        data = capacity ? new T[capacity] : nullptr;   // BUG ORIGINAL: new int[]
        for (int i = 0; i < tam; ++i) data[i] = other.data[i];
        return *this;
    }

    ~my_vector() { delete[] data; }

    int  size()     const { return tam; }
    int  cap()      const { return capacity; }
    bool empty()    const { return tam == 0; }

    T&       operator[](int i)       { return data[i]; }   // BUG ORIGINAL: devolvía int&
    const T& operator[](int i) const { return data[i]; }   // faltaba la versión const

    T& front() { return data[0]; }
    T& back()  { return data[tam - 1]; }

    T* begin() { return data; }
    T* end()   { return data + tam; }
    const T* begin() const { return data; }
    const T* end()   const { return data + tam; }

    void reserve(int nueva_cap) {
        if (nueva_cap > capacity) resize_interno(nueva_cap);
    }

    void push_back(const T& item) {          // por referencia: evita una copia
        if (tam == capacity)
            resize_interno(capacity == 0 ? 1 : capacity * 2);
        data[tam++] = item;
    }

    void pop_back() {
        if (tam > 0) --tam;
    }

    // Inserta 'item' en la posición pos (0-indexed). O(n)
    void insert(int pos, const T& item) {
        if (pos < 0 || pos > tam) return;
        if (tam == capacity)
            resize_interno(capacity == 0 ? 1 : capacity * 2);
        for (int i = tam; i > pos; --i) data[i] = data[i - 1];
        data[pos] = item;
        ++tam;
    }

    // Elimina la posición pos. O(n)
    void erase(int pos) {
        if (pos < 0 || pos >= tam) return;
        for (int i = pos; i < tam - 1; ++i) data[i] = data[i + 1];
        --tam;
    }

    // Índice del primer elemento igual a 'valor', o -1. O(n)
    int find(const T& valor) const {
        for (int i = 0; i < tam; ++i)
            if (data[i] == valor) return i;
        return -1;
    }

    // clear NO libera memoria: solo olvida los elementos (capacity se mantiene).
    void clear() { tam = 0; }

    void print() const {                     // antes se llamaba dum()
        for (int i = 0; i < tam; ++i) cout << data[i] << " ";
        cout << '\n';
    }
};

int main() {
    my_vector<int> v;
    for (int i = 1; i <= 5; ++i) v.push_back(i * 10);
    cout << "v: "; v.print();                       // 10 20 30 40 50
    cout << "size=" << v.size() << " cap=" << v.cap() << '\n';  // 5 8

    v.insert(0, 99);
    v.erase(3);
    cout << "v: "; v.print();                       // 99 10 20 40 50
    cout << "find(40) = " << v.find(40) << '\n';    // 3

    v[0] = -1;                                      // operator[] no-const
    cout << "front=" << v.front() << " back=" << v.back() << '\n';

    my_vector<int> w = v;                           // constructor de copia
    w.push_back(777);
    cout << "v: "; v.print();                       // v NO cambió
    cout << "w: "; w.print();

    // Prueba de que el template ya funciona con otros tipos
    // (con el bug de `new int[]` esto no compilaba / corrompía memoria)
    my_vector<double> d;
    d.push_back(1.5); d.push_back(2.5);
    cout << "d: "; d.print();                       // 1.5 2.5

    my_vector<char> c(3, 'x');
    cout << "c: "; c.print();                       // x x x

    for (int& x : v) x += 1;                        // usa begin()/end()
    cout << "v+1: "; v.print();

    return 0;
}