
#include <iostream>
using namespace std;

struct Nodo {
    int exponente;
    long long coeficiente;
    Nodo* next;
};

void agregar(Nodo*& tailR, int e, long long c) {
    Nodo* nuevo = new Nodo;
    nuevo->exponente   = e;
    nuevo->coeficiente = c;
    nuevo->next        = nullptr;
    tailR->next = nuevo;
    tailR = nuevo;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int p;
    cin >> p;
    Nodo* head1 = new Nodo;          // centinela: nunca guarda datos
    head1->next = nullptr;
    Nodo* tail1 = head1;
    for (int i = 1; i <= p; i++) {
        Nodo* nuevo = new Nodo;
        cin >> nuevo->exponente;
        cin >> nuevo->coeficiente;
        nuevo->next = nullptr;
        tail1->next = nuevo;
        tail1 = nuevo;
    }

    int q;
    cin >> q;
    Nodo* head2 = new Nodo;
    head2->next = nullptr;
    Nodo* tail2 = head2;
    for (int i = 1; i <= q; i++) {
        Nodo* nuevo = new Nodo;
        cin >> nuevo->exponente;
        cin >> nuevo->coeficiente;
        nuevo->next = nullptr;
        tail2->next = nuevo;
        tail2 = nuevo;
    }

    Nodo* headR = new Nodo;          // centinela del resultado
    headR->next = nullptr;
    Nodo* tailR = headR;
    int m = 0;                       // cuantos terminos tiene R

    Nodo* t1 = head1->next;
    Nodo* t2 = head2->next;

    while (t1 != nullptr && t2 != nullptr) {

        if (t1->exponente < t2->exponente) {
            agregar(tailR, t1->exponente, t1->coeficiente);
            m++;
            t1 = t1->next;

        } else if (t1->exponente > t2->exponente) {
            agregar(tailR, t2->exponente, t2->coeficiente);
            m++;
            t2 = t2->next;

        } else {
            long long suma = t1->coeficiente + t2->coeficiente;
            if (suma != 0) {         // si se cancela, NO entra al resultado
                agregar(tailR, t1->exponente, suma);
                m++;
            }
            t1 = t1->next;
            t2 = t2->next;
        }
    }

    while (t1 != nullptr) {
        agregar(tailR, t1->exponente, t1->coeficiente);
        m++;
        t1 = t1->next;
    }
    while (t2 != nullptr) {
        agregar(tailR, t2->exponente, t2->coeficiente);
        m++;
        t2 = t2->next;
    }

    cout << m << endl;
    for (Nodo* t = headR->next; t != nullptr; t = t->next)
        cout << t->exponente << " " << t->coeficiente << endl;

    return 0;
}