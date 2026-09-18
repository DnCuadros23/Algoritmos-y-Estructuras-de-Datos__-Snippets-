#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


//https://github.com/DnCuadros23/Algoritmos-y-Estructuras-de-Datos__-Snippets-.git
typedef unsigned long long ull;

//  FUNCIONES HASH  (TODAS globales, fuera del struct)
//  Convierten una clave en un numero grande. El "% m" viene despues.

// Enteros con signo: polinomio en base B sobre los digitos.
// El do-while procesa el 0, y el signo entra en el valor inicial
// para que -12 y 12 no caigan en el mismo bucket.



//---------Funciones hashing-------
ull hash_valor(long long k) {
    const ull B = 311, MOD = 1000000007ULL;
    ull h = (k < 0 ? 1 : 2);
    ull x = (k < 0 ? -(ull)k : (ull)k);
    do {
        h = (h * B + (x % 10 + 1)) % MOD;
        x /= 10;
    } while (x > 0);
    return h;
}


// Enteros sin signo: mismo polinomio, nunca hay signo que codificar.
ull hash_valor(unsigned long long k) {
    const ull B = 311, MOD = 1000000007ULL;
    ull h = 2;
    do {
        h = (h * B + (k % 10 + 1)) % MOD;
        k /= 10;
    } while (k > 0);
    return h;
}

// Sobrecargas exactas para los tipos chicos: sin ellas, un my_map<unsigned int,...>
// da "ambiguous call" porque unsigned int puede ir a long long o a unsigned long long.
ull hash_valor(int k)           { return hash_valor((long long)k); }
ull hash_valor(unsigned int k)  { return hash_valor((unsigned long long)k); }
ull hash_valor(char k)          { return hash_valor((long long)k); }

// Strings: mismo polinomio, pero sobre los codigos ASCII.
ull hash_valor(const string &s) {
    const ull B = 131, MOD = 1000000007ULL;
    ull h = 0;
    for (int i = 0; i < (int)s.size(); ++i)
        h = (h * B + (ull)(unsigned char)s[i] + 1) % MOD;
    return h;
}

// Vectores de enteros (claves compuestas: coordenadas, tuplas, etc).
ull hash_valor(const vector<int> &v) {
    const ull B = 1000003, MOD = 1000000007ULL;
    ull h = 1;
    for (int i = 0; i < (int)v.size(); ++i)
        h = (h * B + (ull)(unsigned int)v[i] + 1) % MOD;
    return h;
}

// Pares (utiles para grillas).
ull hash_valor(const pair<int, int> &p) {
    const ull B = 1000003, MOD = 1000000007ULL;
    return ((ull)(unsigned int)p.first * B + (ull)(unsigned int)p.second + 1) % MOD;
}
ull hash_valor(const pair<long long, long long> &p) {
    const ull B = 1000003, MOD = 1000000007ULL;
    ull h = (ull)p.first % MOD;
    h = (h * B + (ull)p.second) % MOD;
    return h;
}
//  TABLA HASH CON ENCADENAMIENTO SEPARADO
//  chains[b] guarda TODAS las claves cuyo hash cae en el bucket b.
//  Manteniendo alpha = n/m acotado, cada operacion es O(1) esperado.

template <typename K, typename V>
struct my_map {
    int m;              // cantidad de buckets
    int n;              // cantidad de claves guardadas
    vector<vector<pair<K, V> > > chains;
    //Crear mapa
    my_map(int m_ini = 101) : m(primo_desde(m_ini)), n(0) {
        chains.assign(m, vector<pair<K, V> >());
    }

    static int primo_desde(long long x) {
        if (x < 3) x = 3;
        if (x > 2000000000LL) x = 2000000011LL;   // evita overflow al duplicar
        while (true) {
            bool ok = true;
            for (long long d = 2; d * d <= x; ++d)
                if (x % d == 0) { ok = false; break; }
            if (ok) return (int)x;
            ++x;
        }
    }

    int bucket_de(const K &key) const {
        return (int)(hash_valor(key) % (ull)m);
    }

    // Posicion de key dentro de su bucket, o -1 si no esta.
    // Toda busqueda pasa por aqui: una sola forma de recorrer la cadena.
    int pos_en(int b, const K &key) const {
        for (int i = 0; i < (int)chains[b].size(); ++i)
            if (chains[b][i].first == key) return i;
        return -1;
    }

    // Duplica la tabla y reubica todo. Solo se llama al pasarse de alpha,
    // asi que el costo queda amortizado en O(1) por insercion.
    void rehash() {
        vector<vector<pair<K, V> > > viejo;
        viejo.swap(chains);
        m = primo_desde(2LL * m);
        chains.assign(m, vector<pair<K, V> >());
        for (int b = 0; b < (int)viejo.size(); ++b)
            for (int i = 0; i < (int)viejo[b].size(); ++i)
                chains[bucket_de(viejo[b][i].first)].push_back(viejo[b][i]);
    }
    //tamaño
    int size() const { return n; }
    //vacio ?
    bool empty() const { return n == 0; }
    //vacia todo
    void clear() {
        chains.assign(m, vector<pair<K, V> >());
        n = 0;
    }
    //esta x ?
    bool has_key(const K &key) const {
        return pos_en(bucket_de(key), key) != -1;
    }

    // Puntero al valor, o NULL si no existe. NO inserta.
    // OJO: el puntero se invalida si despues insertas (push_back / rehash).
    V* find(const K &key) {
        int b = bucket_de(key);
        int i = pos_en(b, key);
        return (i == -1 ? (V*)0 : &chains[b][i].second);
    }
    //
    const V* find(const K &key) const {
        int b = bucket_de(key);
        int i = pos_en(b, key);
        return (i == -1 ? (const V*)0 : &chains[b][i].second);
    }

    // Valor si existe, si no el default. NO inserta.
    V get(const K &key, V def = V()) const {
        int b = bucket_de(key);
        int i = pos_en(b, key);
        return (i == -1 ? def : chains[b][i].second);
    }

    // Crea la clave con V() si no existe. Cuidado: consultar con []
    // inserta. Para solo consultar, usa get() o has_key().
    V& operator[](const K &key) {
        int b = bucket_de(key);
        int i = pos_en(b, key);
        if (i != -1) return chains[b][i].second;
        if (n + 1 > 2 * m) {        // alpha > 2 : crecer
            rehash();
            b = bucket_de(key);     // el bucket cambio al cambiar m
        }
        chains[b].push_back(make_pair(key, V()));
        ++n;
        return chains[b].back().second;
    }
    //set(x,v) x con su valor
    void set(const K &key, const V &val) {
        (*this)[key] = val;
    }

    void add(const K &key, const V &delta) {
        (*this)[key] += delta;
    }

    // O(1): se pisa el elemento con el ultimo del bucket.
    // El orden dentro de un bucket no importa.
    bool erase(const K &key) {
        int b = bucket_de(key);
        int i = pos_en(b, key);
        if (i == -1) return false;
        swap(chains[b][i], chains[b].back());
        chains[b].pop_back();
        --n;
        return true;
    }

    // Recorridos. Devuelven COPIAS: O(m + n) por llamada.
    // Guardalas en una variable, no las llames dentro de un bucle.
    vector<K> keys() const {
        vector<K> res;
        res.reserve(n);
        for (int b = 0; b < m; ++b)
            for (int i = 0; i < (int)chains[b].size(); ++i)
                res.push_back(chains[b][i].first);
        return res;
    }

    vector<V> values() const {
        vector<V> res;
        res.reserve(n);
        for (int b = 0; b < m; ++b)
            for (int i = 0; i < (int)chains[b].size(); ++i)
                res.push_back(chains[b][i].second);
        return res;
    }

    vector<pair<K, V> > items() const {
        vector<pair<K, V> > res;
        res.reserve(n);
        for (int b = 0; b < m; ++b)
            for (int i = 0; i < (int)chains[b].size(); ++i)
                res.push_back(chains[b][i]);
        return res;
    }

    void print() const {
        for (int b = 0; b < m; ++b) {
            if (chains[b].empty()) continue;
            cout << "Bucket " << b << ":\n";
            for (int i = 0; i < (int)chains[b].size(); ++i)
                cout << "  " << chains[b][i].first << " --> " << chains[b][i].second << "\n";
        }
    }
};
struct Par {
    long long a, b;
    Par() : a(0), b(0) {}
    Par(long long a, long long b) : a(a), b(b) {}
};

bool operator == (const Par &p, const Par &q) {
    return p.a == q.a and p.b == q.b;
}

ull hash_valor(const Par &p) {
    const ull B = 1000003, MOD = 1000000007ULL;
    ull h = hash_valor(p.a);
    h = (h * B + hash_valor(p.b)) % MOD;
    return h;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    my_map<int, int> visto(300);
    vector<int> usadas;
    usadas.reserve(243);

    string salida;
    vector<string> g(9);

    while (T--) {

        for (int r = 0; r < 9; ++r) cin >> g[r];

        bool ok = true;
        for (int r = 0; r < 9 && ok; ++r) {
            for (int c = 0; c < 9 && ok; ++c) {
                if (g[r][c] == '.') continue;

                int d = g[r][c] - '1';            // 0..8
                int caja = (r / 3) * 3 + c / 3;   // 0..8

                int claves[3] = {
                    0   + r * 9 + d,      // fila
                    81  + c * 9 + d,      // columna
                    162 + caja * 9 + d    // caja
                };
                for (int x = 0; x < 3; ++x) {
                    if (visto.has_key(claves[x])) {
                        ok = false;
                        break;
                    }
                    visto[claves[x]] = 1;
                    usadas.push_back(claves[x]);
                }
            }
        }
        salida += (ok ? "SI\n" : "NO\n");

        for (int i = 0; i < (int)usadas.size(); ++i) visto.erase(usadas[i]);
        usadas.clear();
    }
    cout << salida;
    return 0;
}