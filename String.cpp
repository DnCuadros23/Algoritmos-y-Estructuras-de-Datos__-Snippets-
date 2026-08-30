// INVARIANTE:
//   - Si m_str != nullptr, apunta a un bloque del heap de m_size chars
//     terminado en '\0', y m_size == longitud + 1.
//   - Si m_str == nullptr, entonces m_size == 0 (string vacío).
//   En ambos casos size() devuelve la longitud lógica (sin el '\0').
// COMPLEJIDADES
//   size(), c_str(), operator[]      O(1)
//   constructor / copia / operator=  O(n)
//   operator+                        O(n + m)
//   operator+=                       O(n + m)   -- reconstruye, no amortiza
//   find, ==, <                      O(n)
// ESPACIO: O(n)

#include <iostream>
using namespace std;
 
class my_string {
    char* m_str = nullptr;   // bloque en el heap
    int   m_size = 0;        // longitud + 1 (incluye el '\0'), o 0 si vacío
 
    // Helpers propios: así el archivo NO depende de <cstring>
    static int longitud_c(const char* s) {
        int n = 0;
        while (s[n] != '\0') ++n;
        return n;
    }
    static void copiar(char* destino, const char* origen, int n) {
        for (int i = 0; i < n; ++i) destino[i] = origen[i];
    }
 
public:

    // Constructor (también sirve de constructor por defecto)
    my_string(const char* str = nullptr) {
        if (!str) return;                 // queda m_str=nullptr, m_size=0
        m_size = longitud_c(str) + 1;
        m_str = new char[m_size];
        copiar(m_str, str, m_size);       // copia también el '\0'
    }
 
    // Constructor de copia (copia PROFUNDA: bloque nuevo, no comparte puntero)
    my_string(const my_string& other) {
        if (!other.m_str) return;
        m_size = other.m_size;
        m_str = new char[m_size];
        copiar(m_str, other.m_str, m_size);
    }
 
    // Operador de asignación
    my_string& operator=(const my_string& other) {
        if (this == &other) return *this;   // autoasignación: s = s
        delete[] m_str;                     // libero lo viejo primero
        m_size = other.m_size;
        m_str  = other.m_str ? new char[m_size] : nullptr;
        if (m_str) copiar(m_str, other.m_str, m_size);
        return *this;
    }
 
    // Destructor
    ~my_string() { delete[] m_str; }
 
    int size()  const { return m_size ? m_size - 1 : 0; }
    bool empty() const { return size() == 0; }
    const char* c_str() const { return m_str ? m_str : ""; }
 
    // end() apunta al '\0', o sea UNA posición después del último char válido.
    char* begin() { return m_str; }
    char* end()   { return m_str + size(); }
    const char* begin() const { return c_str(); }
    const char* end()   const { return c_str() + size(); }
 
    char&       operator[](int i)       { return m_str[i]; }
    const char& operator[](int i) const { return m_str[i]; }
 
    // Se construye el resultado DIRECTAMENTE (una sola copia).
    // La versión con buffer temporal + delete[] hacía copia doble.
    my_string operator+(const my_string& other) const {
        int n1 = size(), n2 = other.size();
        my_string r;
        r.m_size = n1 + n2 + 1;
        r.m_str  = new char[r.m_size];
        copiar(r.m_str, c_str(), n1);
        copiar(r.m_str + n1, other.c_str(), n2);
        r.m_str[n1 + n2] = '\0';
        return r;
    }
 
    my_string& operator+=(const my_string& other) {
        *this = *this + other;
        return *this;
    }
 
    bool operator==(const my_string& o) const {
        if (size() != o.size()) return false;
        for (int i = 0; i < size(); ++i)
            if (c_str()[i] != o.c_str()[i]) return false;
        return true;
    }
    bool operator!=(const my_string& o) const { return !(*this == o); }
 
    // Orden lexicográfico (como strcmp < 0)
    bool operator<(const my_string& o) const {
        int i = 0;
        const char *a = c_str(), *b = o.c_str();
        while (a[i] && b[i] && a[i] == b[i]) ++i;
        return a[i] < b[i];
    }
 
    // Índice de la primera aparición de 'sub', o -1. O(n*m) (fuerza bruta)
    int find(const my_string& sub) const {
        int n = size(), m = sub.size();
        if (m == 0) return 0;
        if (m > n) return -1;
        for (int i = 0; i + m <= n; ++i) {
            int j = 0;
            while (j < m && c_str()[i + j] == sub.c_str()[j]) ++j;
            if (j == m) return i;
        }
        return -1;
    }
 
    // Subcadena de longitud 'len' desde 'pos'. O(len)
    my_string substr(int pos, int len) const {
        if (pos < 0 || pos >= size() || len <= 0) return my_string();
        if (pos + len > size()) len = size() - pos;
        my_string r;
        r.m_size = len + 1;
        r.m_str  = new char[r.m_size];
        copiar(r.m_str, c_str() + pos, len);
        r.m_str[len] = '\0';
        return r;
    }
 
    friend ostream& operator<<(ostream& os, const my_string& s) {
        return os << s.c_str();
    }
};
 
int main() {
    my_string a("Hola");
    my_string b(" mundo");
 
    cout << a << b << '\n';              // Hola mundo
    cout << (a + b) << '\n';             // Hola mundo
    cout << "size(a) = " << a.size() << '\n';   // 4
 
    my_string c = a;                     // constructor de copia
    c += "!!!";                          // operator+= (const char* -> my_string implícito)
    cout << "c = " << c << "   a = " << a << '\n';  // c cambió, a NO (copia profunda)
 
    my_string d;
    d = c;                               // operator=
    cout << "d = " << d << '\n';
 
    cout << "(a == d)? " << (a == d) << '\n';               // 0
    cout << "find(\"mun\") = " << (a + b).find("mun") << '\n'; // 5
    cout << "substr(0,4) = " << (a + b).substr(0, 4) << '\n';  // Hola
 
    cout << "recorrido: ";
    for (char ch : a) cout << ch << '.';  // usa begin()/end()
    cout << '\n';
 
    my_string vacio;
    cout << "vacio.empty() = " << vacio.empty() << ", size = " << vacio.size() << '\n';
 
    return 0;
}