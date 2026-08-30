// INVARIANTE:
//   - Si la lista está vacía: head == tail == nullptr y n == 0.
//   - Si no: head apunta al primer nodo, tail al último,
//     tail->next == nullptr, y n es la cantidad de nodos.
//
// COMPLEJIDADES
//   push_front, pop_front, front, back, size, empty   O(1)
//   push_back                                         O(1)  (gracias a tail)
//   insert(k), erase(k), find, operator[]             O(n)
//   pop_back                                          O(n)  (no hay prev)
//   reverse, clear, print                             O(n)
// ESPACIO: O(n)  -- cada nodo cuesta sizeof(T) + un puntero
//
// ¿POR QUÉ ESTA Y NO LA DE DOBLE PUNTERO?  Ver README y archivo 04.

#include <iostream>
using namespace std;

template <typename T>
class ListaEnlazada {
    struct Nodo {
        T data;
        Nodo* next;
        Nodo(const T& data, Nodo* next = nullptr) : data(data), next(next) {}
    };

    Nodo* head;
    Nodo* tail;
    int   n;

public:
    ListaEnlazada() : head(nullptr), tail(nullptr), n(0) {}

    // Sin esto, copiar una lista copiaría los punteros y DOS listas
    // borrarían los mismos nodos -> doble delete.
    ListaEnlazada(const ListaEnlazada& other) : head(nullptr), tail(nullptr), n(0) {
        for (Nodo* cur = other.head; cur; cur = cur->next) push_back(cur->data);
    }

    ListaEnlazada& operator=(const ListaEnlazada& other) {
        if (this == &other) return *this;
        clear();
        for (Nodo* cur = other.head; cur; cur = cur->next) push_back(cur->data);
        return *this;
    }

    ~ListaEnlazada() { clear(); }

    bool empty() const { return head == nullptr; }
    int  size()  const { return n; }

    T& front() { return head->data; }   // precondición: !empty()
    T& back()  { return tail->data; }   // precondición: !empty()

    void push_front(const T& value) {
        head = new Nodo(value, head);
        if (!tail) tail = head;         // la lista estaba vacía
        ++n;
    }

    void push_back(const T& value) {
        Nodo* nuevo = new Nodo(value);
        if (!tail) head = tail = nuevo;
        else { tail->next = nuevo; tail = nuevo; }
        ++n;
    }

    // Inserta 'value' DESPUÉS del nodo dado (que no debe ser nulo). O(1)
    void insert_after(Nodo* nodo, const T& value) {
        if (!nodo) return;
        nodo->next = new Nodo(value, nodo->next);
        if (nodo == tail) tail = nodo->next;
        ++n;
    }

    // Inserta 'value' de modo que quede en la posición k (0-indexed). O(k)
    void insert(int k, const T& value) {
        if (k < 0 || k > n) return;           // validación que faltaba
        if (k == 0)  { push_front(value); return; }
        if (k == n)  { push_back(value);  return; }
        Nodo* cur = head;
        for (int i = 0; i < k - 1; ++i) cur = cur->next;
        insert_after(cur, value);
    }

    void pop_front() {
        if (!head) return;                    // el original crasheaba aquí
        Nodo* viejo = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete viejo;
        --n;
    }

    // O(n) porque hay que llegar al penúltimo nodo (no hay prev).
    void pop_back() {
        if (!head) return;
        if (head == tail) { pop_front(); return; }
        Nodo* cur = head;
        while (cur->next != tail) cur = cur->next;
        delete tail;
        tail = cur;
        tail->next = nullptr;
        --n;
    }

    // Elimina el nodo SIGUIENTE a 'nodo'. O(1)
    // (Nombre explícito: el original se llamaba erase() y confundía
    //  porque en la lista doble erase() borra el nodo mismo.)
    void erase_after(Nodo* nodo) {
        if (!nodo || !nodo->next) return;
        Nodo* victima = nodo->next;
        if (victima == tail) tail = nodo;
        nodo->next = victima->next;
        delete victima;
        --n;
    }

    // Elimina la posición k (0-indexed). O(k)
    void erase(int k) {
        if (k < 0 || k >= n) return;
        if (k == 0) { pop_front(); return; }
        Nodo* cur = head;
        for (int i = 0; i < k - 1; ++i) cur = cur->next;
        erase_after(cur);
    }

    // Elimina la primera aparición de 'value'. Devuelve si borró algo. O(n)
    bool remove(const T& value) {
        if (!head) return false;
        if (head->data == value) { pop_front(); return true; }
        for (Nodo* cur = head; cur->next; cur = cur->next) {
            if (cur->next->data == value) { erase_after(cur); return true; }
        }
        return false;
    }

    void clear() {
        while (head) {
            Nodo* siguiente = head->next;
            delete head;
            head = siguiente;
        }
        tail = nullptr;
        n = 0;
    }

    // Índice de la primera aparición, o -1. O(n)
    int find(const T& value) const {
        int i = 0;
        for (Nodo* cur = head; cur; cur = cur->next, ++i)
            if (cur->data == value) return i;
        return -1;
    }

    // Acceso por índice: O(n), NO O(1). Esa es la diferencia con el array.
    T& operator[](int k) {
        Nodo* cur = head;
        for (int i = 0; i < k; ++i) cur = cur->next;
        return cur->data;
    }

    // Invierte la lista in-place. O(n) tiempo, O(1) espacio.
    void reverse() {
        Nodo* prev = nullptr;
        Nodo* cur  = head;
        tail = head;
        while (cur) {
            Nodo* siguiente = cur->next;
            cur->next = prev;
            prev = cur;
            cur = siguiente;
        }
        head = prev;
    }

    void print() const {
        for (Nodo* cur = head; cur; cur = cur->next) cout << cur->data << " ";
        cout << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ListaEnlazada<int> L;

    L.push_back(10);
    L.push_back(20);
    L.push_back(30);
    L.push_front(5);
    cout << "L: "; L.print();                 // 5 10 20 30

    L.insert(2, 99);
    cout << "insert(2,99): "; L.print();      // 5 10 99 20 30

    L.erase(0);
    cout << "erase(0):     "; L.print();      // 10 99 20 30

    L.pop_back();
    cout << "pop_back():   "; L.print();      // 10 99 20

    cout << "find(99) = " << L.find(99) << '\n';   // 1
    cout << "L[2] = "     << L[2] << '\n';         // 20
    cout << "front=" << L.front() << " back=" << L.back()
         << " size=" << L.size() << '\n';

    L.remove(99);
    cout << "remove(99):   "; L.print();      // 10 20

    L.reverse();
    cout << "reverse():    "; L.print();      // 20 10
    cout << "back tras reverse = " << L.back() << '\n';  // 10

    // Copia profunda
    ListaEnlazada<int> M = L;
    M.push_back(777);
    cout << "L: "; L.print();                 // 20 10   (no cambió)
    cout << "M: "; M.print();                 // 20 10 777

    // Casos borde: operaciones sobre lista vacía no deben crashear
    ListaEnlazada<int> vacia;
    vacia.pop_front();
    vacia.pop_back();
    vacia.erase(0);
    cout << "vacia.empty() = " << vacia.empty() << '\n';  // 1

    return 0;
}