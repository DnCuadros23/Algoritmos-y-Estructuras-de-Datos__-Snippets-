// se guarda: elimina TODOS los casos especiales de la cabeza.
//
// LA IDEA CENTRAL
//   En vez de guardar "el nodo actual" (Nodo*), guardamos "la dirección
//   del puntero que apunta al nodo actual" (Nodo**).
//
//   Lista:   head --> [A] --> [B] --> [C] --> nullptr
//
//   Con Nodo*  apuntas al nodo B.  Para borrarlo necesitas a A
//              (para poder hacer A->next = C) => necesitas buscarAnterior().
//   Con Nodo** apuntas a la CASILLA A->next, que es donde vive el puntero
//              a B.  Para borrar B basta con  *p = B->next.
//
//   Y si el nodo buscado es el primero, p apunta a &head, que se actualiza
//   con exactamente el mismo código. Cero if especiales.
//
//   CONSECUENCIA: buscarAnterior() del código original SOBRA. Es
//   justamente el caso que esta técnica viene a eliminar.
//
// COMPLEJIDADES
//   push_front, insert(p,v), erase(p)   O(1)
//   buscar(v)                           O(n)
//   size (con contador), empty          O(1)
//   print, clear                        O(n)
// ESPACIO: O(n)

#include <iostream>
using namespace std;

template <class T>
class ListaDoblePuntero {
public:
    // El struct debe ser PÚBLICO: buscar() devuelve Nodo** y desde main
    // no se podría nombrar el tipo si fuera privado.
    struct Nodo {
        T data;
        Nodo* next;
        Nodo(const T& data, Nodo* next = nullptr) : data(data), next(next) {}
    };

private:
    Nodo* head;
    int   n;

public:
    ListaDoblePuntero() : head(nullptr), n(0) {}

    ListaDoblePuntero(const ListaDoblePuntero& other) : head(nullptr), n(0) {
        Nodo** cola = &head;                  // el doble puntero también
        for (Nodo* cur = other.head; cur; cur = cur->next) {
            *cola = new Nodo(cur->data);      // sirve para copiar en orden
            cola = &((*cola)->next);
            ++n;
        }
    }

    ListaDoblePuntero& operator=(const ListaDoblePuntero& other) {
        if (this == &other) return *this;
        clear();
        Nodo** cola = &head;
        for (Nodo* cur = other.head; cur; cur = cur->next) {
            *cola = new Nodo(cur->data);
            cola = &((*cola)->next);
            ++n;
        }
        return *this;
    }

    ~ListaDoblePuntero() { clear(); }   // FALTABA: sin esto, memory leak

    bool empty() const { return head == nullptr; }
    int  size()  const { return n; }


    // Devuelve la DIRECCIÓN del puntero que apunta al primer nodo con
    // ese valor. Si no existe, devuelve la dirección del último 'next'
    // (que vale nullptr) -- o sea, el punto exacto donde habría que
    // insertarlo. Nunca devuelve nullptr.
    Nodo** buscar(const T& data) {
        Nodo** actual = &head;
        while (*actual && (*actual)->data != data)
            actual = &((*actual)->next);
        return actual;
    }

    // Inserta antes del nodo apuntado por p. O(1)
    // BUG ORIGINAL: estaba declarada como  Nodo** insert(...)  pero no
    // retornaba nada -> comportamiento indefinido. Es void.
    void insert(Nodo** p, const T& data) {
        *p = new Nodo(data, *p);
        ++n;
    }

    // Elimina el nodo apuntado por p. O(1). Devuelve si borró algo.
    // Funciona igual si p == &head. Ese es todo el truco.
    bool erase(Nodo** p) {
        if (!p || !*p) return false;
        Nodo* victima = *p;
        *p = victima->next;
        delete victima;
        --n;
        return true;
    }

    void push_front(const T& data) { insert(&head, data); }

    // O(n): sin tail hay que caminar hasta el final. Este es el precio
    // de esta versión frente a la de 03.
    void push_back(const T& data) {
        Nodo** p = &head;
        while (*p) p = &((*p)->next);
        insert(p, data);
    }

    void pop_front() { erase(&head); }

    bool remove(const T& data) { return erase(buscar(data)); }

    bool contains(const T& data) { return *buscar(data) != nullptr; }

    void clear() {
        while (head) {
            Nodo* siguiente = head->next;
            delete head;
            head = siguiente;
        }
        n = 0;
    }

    void print() const {
        for (Nodo* cur = head; cur; cur = cur->next) cout << cur->data << " ";
        cout << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ListaDoblePuntero<int> lista;
    lista.push_front(1);
    lista.push_front(2);
    lista.push_front(3);
    cout << "lista: "; lista.print();          // 3 2 1

    // ERROR ORIGINAL:  cout << &(*lista.buscar(2));
    //   buscar(2) da Nodo**, el * lo convierte en Nodo*, el & lo vuelve
    //   Nodo** otra vez. Se imprimía una DIRECCIÓN de memoria, no el dato.
    // Forma correcta: desreferenciar dos veces, revisando antes que exista.
    ListaDoblePuntero<int>::Nodo** p = lista.buscar(2);
    if (*p) cout << "encontrado: " << (*p)->data << '\n';   // 2
    else    cout << "no está\n";

    // Insertar justo antes del 2
    lista.insert(p, 99);
    cout << "insert antes de 2: "; lista.print();   // 3 99 2 1

    // Borrar la CABEZA con el mismo código que cualquier otro nodo
    lista.remove(3);
    cout << "remove(3):         "; lista.print();   // 99 2 1

    lista.remove(1);                                // el último
    cout << "remove(1):         "; lista.print();   // 99 2

    cout << "contains(2)=" << lista.contains(2)
         << " contains(7)=" << lista.contains(7)
         << " size=" << lista.size() << '\n';

    // Buscar algo que no existe: devuelve el punto de inserción al final
    ListaDoblePuntero<int>::Nodo** q = lista.buscar(1000);
    lista.insert(q, 1000);
    cout << "insert al final:   "; lista.print();   // 99 2 1000

    ListaDoblePuntero<int> copia = lista;           // copia profunda
    copia.push_front(-1);
    cout << "original: "; lista.print();
    cout << "copia:    "; copia.print();

    return 0;
}