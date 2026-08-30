// Igual que la lista simple, pero  tail->next == head  en vez de nullptr.
// No hay "final": recorrerla es dar vueltas.
//
// INVARIANTE:
//   - Vacía: head == tail == nullptr, n == 0.
//   - Si no: tail->next == head siempre. Ningún next es nullptr.
//
// CUIDADO AL RECORRER: la condición cur!= nullptr  NUNCA se cumple,
// se cuelga en bucle infinito. Hay que usar do-while comparando con head
// o contar n iteraciones.
//
// COMPLEJIDADES
//   push_front, push_back, pop_front, front, empty, size   O(1)
//   rotar (mandar el frente al final)                      O(1)  <- la joya
//   pop_back, buscar, print                                O(n)
// ESPACIO: O(n)
//
// APLICACIÓN CLÁSICA: planificación Round Robin, el juego de Josephus,
// buffers circulares, turnos de jugadores.

#include <iostream>
using namespace std;

template <typename T>
class ListaCircular {
public:
    struct Nodo {
        T data;
        Nodo* next;
        Nodo(const T& data, Nodo* next = nullptr) : data(data), next(next) {}
    };

private:
    Nodo* head;
    Nodo* tail;
    int   n;

public:
    ListaCircular() : head(nullptr), tail(nullptr), n(0) {}

    ListaCircular(const ListaCircular& other) : head(nullptr), tail(nullptr), n(0) {
        if (!other.head) return;
        Nodo* cur = other.head;
        do { push_back(cur->data); cur = cur->next; } while (cur != other.head);
    }

    ListaCircular& operator=(const ListaCircular& other) {
        if (this == &other) return *this;
        clear();
        if (!other.head) return *this;
        Nodo* cur = other.head;
        do { push_back(cur->data); cur = cur->next; } while (cur != other.head);
        return *this;
    }

    ~ListaCircular() { clear(); }

    bool empty() const { return head == nullptr; }
    int  size()  const { return n; }
    T& front() { return head->data; }
    T& back()  { return tail->data; }

    void push_front(const T& value) {
        if (!head) {
            head = tail = new Nodo(value);
            head->next = head;              // se apunta a sí mismo
        } else {
            head = new Nodo(value, head);
            tail->next = head;              // se mantiene el círculo
        }
        ++n;
    }

    void push_back(const T& value) {
        if (!head) { push_front(value); return; }
        Nodo* nuevo = new Nodo(value, head);   // el nuevo cierra el círculo
        tail->next = nuevo;
        tail = nuevo;
        ++n;
    }

    void pop_front() {
        if (!head) return;
        Nodo* viejo = head;
        if (head == tail) {                 // único elemento
            head = tail = nullptr;
        } else {
            head = head->next;
            tail->next = head;
        }
        delete viejo;
        --n;
    }

    // O(n): hay que llegar al penúltimo.
    void pop_back() {
        if (!head) return;
        if (head == tail) { pop_front(); return; }
        Nodo* cur = head;
        while (cur->next != tail) cur = cur->next;
        delete tail;
        tail = cur;
        tail->next = head;
        --n;
    }

    void clear() {
        if (!head) return;
        Nodo* cur = head;
        do {
            Nodo* siguiente = cur->next;
            delete cur;
            cur = siguiente;
        } while (cur != head);
        head = tail = nullptr;
        n = 0;
    }


    // Manda el elemento del frente al final SIN borrar ni crear nodos.
    // Como la lista ya es un círculo, basta con avanzar los dos punteros.
    // O(1).
    void rotar() {
        if (!head) return;
        head = head->next;
        tail = tail->next;
    }

    // Elimina la primera aparición de 'value'. O(n)
    bool remove(const T& value) {
        if (!head) return false;
        if (head->data == value) { pop_front(); return true; }
        Nodo* cur = head;
        while (cur->next != head) {
            if (cur->next->data == value) {
                Nodo* victima = cur->next;
                if (victima == tail) tail = cur;
                cur->next = victima->next;
                delete victima;
                --n;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    void print() const {
        if (!head) { cout << "(vacia)\n"; return; }
        Nodo* cur = head;
        do { cout << cur->data << " "; cur = cur->next; } while (cur != head);
        cout << '\n';
    }
};

// APLICACIÓN: Round Robin con quantum q
// Cada proceso corre como máximo q unidades; si no termina, vuelve al final.
struct Proceso {
    int id;
    int pendiente;
    Proceso(int id = 0, int pendiente = 0) : id(id), pendiente(pendiente) {}
};

void round_robin() {
    ListaCircular<Proceso> L;
    L.push_back(Proceso(1, 5));
    L.push_back(Proceso(2, 3));
    L.push_back(Proceso(3, 8));

    int q = 3;              // quantum
    int reloj = 0;

    cout << "\n--- Round Robin (quantum = " << q << ") ---\n";
    while (!L.empty()) {
        Proceso& actual = L.front();
        if (actual.pendiente > q) {
            actual.pendiente -= q;      // consume su turno y va al final
            reloj += q;
            L.rotar();                  // O(1)
        } else {
            reloj += actual.pendiente;  // termina
            cout << "Proceso " << actual.id << " termina en t=" << reloj << '\n';
            L.pop_front();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ListaCircular<int> C;
    C.push_back(1);
    C.push_back(2);
    C.push_back(3);
    C.push_back(4);
    cout << "C:        "; C.print();      // 1 2 3 4

    C.rotar();
    cout << "rotar():  "; C.print();      // 2 3 4 1
    cout << "front=" << C.front() << " back=" << C.back() << '\n';  // 2, 1

    C.push_front(0);
    cout << "push_front(0): "; C.print(); // 0 2 3 4 1

    C.remove(3);
    cout << "remove(3):     "; C.print(); // 0 2 4 1

    C.pop_back();
    C.pop_front();
    cout << "pops:          "; C.print(); // 2 4
    cout << "size=" << C.size() << '\n';

    ListaCircular<int> D = C;             // copia profunda
    D.push_back(9);
    cout << "C: "; C.print();
    cout << "D: "; D.print();

    round_robin();

    return 0;
}