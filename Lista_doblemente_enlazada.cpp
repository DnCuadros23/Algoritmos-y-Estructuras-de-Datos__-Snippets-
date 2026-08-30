// Cada nodo guarda prev y next. Eso cuesta un puntero extra por nodo,
// pero a cambio:
//   - pop_back pasa de O(n) a O(1)
//   - erase(nodo) es O(1) teniendo solo el nodo (en la simple necesitas
//     el anterior)
//   - se puede recorrer hacia atrás
//
// INVARIANTE:
//   - Vacía: head == tail == nullptr, n == 0.
//   - Si no: head->prev == nullptr, tail->next == nullptr, y para todo
//     nodo x con x->next != nullptr se cumple x->next->prev == x.
//
// COMPLEJIDADES
//   push_front, push_back, pop_front, pop_back      O(1)
//   erase(nodo), insert_before/after(nodo)          O(1)
//   find, insert(k), erase(k), operator[]           O(n)
//   print, print_reverse, clear                     O(n)
// ESPACIO: O(n), con 2 punteros por nodo

#include <iostream>
using namespace std;

template <typename T>
class ListaDoble {
public:
    struct Nodo {
        T data;
        Nodo* prev;
        Nodo* next;
        Nodo(const T& data, Nodo* prev = nullptr, Nodo* next = nullptr)
            : data(data), prev(prev), next(next) {}
    };

private:
    Nodo* head;
    Nodo* tail;
    int   n;

public:
    ListaDoble() : head(nullptr), tail(nullptr), n(0) {}

    ListaDoble(const ListaDoble& other) : head(nullptr), tail(nullptr), n(0) {
        for (Nodo* cur = other.head; cur; cur = cur->next) push_back(cur->data);
    }

    ListaDoble& operator=(const ListaDoble& other) {
        if (this == &other) return *this;
        clear();
        for (Nodo* cur = other.head; cur; cur = cur->next) push_back(cur->data);
        return *this;
    }

    ~ListaDoble() { clear(); }

    bool empty() const { return head == nullptr; }
    int  size()  const { return n; }
    T& front() { return head->data; }
    T& back()  { return tail->data; }

    void push_front(const T& value) {
        Nodo* nuevo = new Nodo(value, nullptr, head);
        if (head) head->prev = nuevo;
        else      tail = nuevo;
        head = nuevo;
        ++n;
    }

    void push_back(const T& value) {
        Nodo* nuevo = new Nodo(value, tail, nullptr);
        if (tail) tail->next = nuevo;
        else      head = nuevo;
        tail = nuevo;
        ++n;
    }

    // Inserta después de 'nodo'. O(1)
    void insert_after(Nodo* nodo, const T& value) {
        if (!nodo) return;
        Nodo* nuevo = new Nodo(value, nodo, nodo->next);
        if (nodo->next) nodo->next->prev = nuevo;
        else            tail = nuevo;
        nodo->next = nuevo;
        ++n;
    }

    // Inserta antes de 'nodo'. O(1)
    void insert_before(Nodo* nodo, const T& value) {
        if (!nodo) return;
        Nodo* nuevo = new Nodo(value, nodo->prev, nodo);
        if (nodo->prev) nodo->prev->next = nuevo;
        else            head = nuevo;
        nodo->prev = nuevo;
        ++n;
    }

    // Inserta en la posición k (0-indexed). O(k)
    void insert(int k, const T& value) {
        if (k < 0 || k > n) return;
        if (k == 0) { push_front(value); return; }
        if (k == n) { push_back(value);  return; }
        Nodo* cur = head;
        for (int i = 0; i < k; ++i) cur = cur->next;
        insert_before(cur, value);
    }

    // Elimina EL NODO DADO (no el siguiente). O(1)
    void erase(Nodo* nodo) {
        if (!nodo) return;
        if (nodo->prev) nodo->prev->next = nodo->next;
        else            head = nodo->next;
        if (nodo->next) nodo->next->prev = nodo->prev;
        else            tail = nodo->prev;
        delete nodo;
        --n;
    }

    void pop_front() { if (head) erase(head); }
    void pop_back()  { if (tail) erase(tail); }   // O(1): aquí sí, gracias a prev

    void erase(int k) {
        Nodo* nodo = nodo_en(k);
        if (nodo) erase(nodo);
    }

    // Elimina la primera aparición de 'value'. O(n)
    bool delete_first(const T& value) {
        Nodo* cur = buscar(value);
        if (!cur) return false;
        erase(cur);          // OJO: tras esto 'cur' queda colgante, no usarlo
        return true;
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

    Nodo* buscar(const T& value) const {
        for (Nodo* cur = head; cur; cur = cur->next)
            if (cur->data == value) return cur;
        return nullptr;
    }

    Nodo* nodo_en(int k) const {
        if (k < 0 || k >= n) return nullptr;
        // Optimización: si k está en la segunda mitad, se camina desde atrás.
        if (k < n / 2) {
            Nodo* cur = head;
            for (int i = 0; i < k; ++i) cur = cur->next;
            return cur;
        }
        Nodo* cur = tail;
        for (int i = n - 1; i > k; --i) cur = cur->prev;
        return cur;
    }

    T& operator[](int k) { return nodo_en(k)->data; }

    int find(const T& value) const {
        int i = 0;
        for (Nodo* cur = head; cur; cur = cur->next, ++i)
            if (cur->data == value) return i;
        return -1;
    }

    void reverse() {
        Nodo* cur = head;
        while (cur) {
            Nodo* tmp = cur->next;      // intercambia prev y next en cada nodo
            cur->next = cur->prev;
            cur->prev = tmp;
            cur = tmp;
        }
        Nodo* tmp = head;               // y al final intercambia head y tail
        head = tail;
        tail = tmp;
    }

    void print() const {
        for (Nodo* cur = head; cur; cur = cur->next) cout << cur->data << " ";
        cout << '\n';
    }

    void print_reverse() const {
        for (Nodo* cur = tail; cur; cur = cur->prev) cout << cur->data << " ";
        cout << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ListaDoble<int> L;
    L.push_back(10);
    L.push_back(20);
    L.push_back(30);
    L.push_front(5);
    cout << "L:          "; L.print();          // 5 10 20 30
    cout << "al reves:   "; L.print_reverse();  // 30 20 10 5

    L.insert(2, 99);
    cout << "insert(2):  "; L.print();          // 5 10 99 20 30

    L.pop_back();
    L.pop_front();
    cout << "pops:       "; L.print();          // 10 99 20

    L.delete_first(99);
    cout << "del(99):    "; L.print();          // 10 20

    cout << "L[1]=" << L[1] << " find(20)=" << L.find(20)
         << " size=" << L.size() << '\n';

    L.push_back(40);
    L.reverse();
    cout << "reverse:    "; L.print();          // 40 20 10
    cout << "y al reves: "; L.print_reverse();  // 10 20 40

    ListaDoble<int> M = L;                      // copia profunda
    M.push_front(-1);
    cout << "L: "; L.print();
    cout << "M: "; M.print();

    // Casos borde
    ListaDoble<int> vacia;
    vacia.pop_front();
    vacia.pop_back();
    cout << "vacia.empty()=" << vacia.empty() << '\n';   // 1

    // Un solo elemento: head == tail
    ListaDoble<int> uno;
    uno.push_back(7);
    uno.pop_back();
    cout << "uno.empty()=" << uno.empty() << " size=" << uno.size() << '\n';  // 1 0

    return 0;
}