// A. Doubly Linked List
// Clase ListaDoble tal cual la escribiste. Solo se completo el main.
// Complejidad: O(1) por insert/deleteFirst/deleteLast, O(n) por delete x (max 20).

#include <iostream>
#include <string>          // hacia falta: usas std::string en el main
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

    // Insert_front
    void push_front(const T& value) {
        Nodo* nuevo = new Nodo(value, nullptr, head);
        if (head) head->prev = nuevo;
        else      tail = nuevo;
        head = nuevo;
        ++n;
    }

    //elimina el primero
    //elimina el ultimo
    void pop_front() { if (head) erase(head); }
    void pop_back()  { if (tail) erase(tail); }   // O(1): aqui si, gracias a prev

    //delete k  (por POSICION, no por clave)
    void erase(int k) {
        Nodo* nodo = nodo_en(k);
        if (nodo) erase(nodo);
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

    // Elimina la primera aparicion de 'value'. O(n)
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

    Nodo* nodo_en(int k) const {
        if (k < 0 || k >= n) return nullptr;
        // Optimizacion: si k esta en la segunda mitad, se camina desde atras.
        if (k < n / 2) {
            Nodo* cur = head;
            for (int i = 0; i < k; ++i) cur = cur->next;
            return cur;
        }
        Nodo* cur = tail;
        for (int i = n - 1; i > k; --i) cur = cur->prev;
        return cur;
    }

    Nodo* buscar(const T& value) const {
        for (Nodo* cur = head; cur; cur = cur->next)
            if (cur->data == value) return cur;
        return nullptr;
    }

    void print() const {
        for (Nodo* cur = head; cur; cur = cur->next) cout << cur->data << " ";
        cout << '\n';
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    ListaDoble<int> lista;

    for (int i = 0; i < n; i++) {
        string op;
        cin >> op;

        if (op == "insert") {
            int x;
            cin >> x;
            lista.push_front(x);
        }
        else if (op == "delete") {
            int x;
            cin >> x;
            lista.delete_first(x);
        }
        else if (op == "deleteFirst") {
            lista.pop_front();
        }
        else if (op == "deleteLast") {
            lista.pop_back();
        }
    }

    lista.print();

    return 0;
}