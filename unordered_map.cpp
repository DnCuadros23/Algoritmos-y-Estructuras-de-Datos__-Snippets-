#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef unsigned long long ull;

//  FUNCIONES HASH
//  Convierten una clave en un numero grande. El "% m" viene despues.

// Enteros: polinomio en base B sobre los digitos (metodo de clase).
// El do-while procesa el 0, y el signo entra en el valor inicial
// para que -12 y 12 no caigan en el mismo bucket.
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

// Strings: mismo polinomio, pero sobre los codigos ASCII.
ull hash_valor(const string &s) {
    const ull B = 131, MOD = 1000000007ULL;
    ull h = 0;
    for (int i = 0; i < (int)s.size(); ++i)
        h = (h * B + (ull)(unsigned char)s[i] + 1) % MOD;
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

    my_map(int m_ini = 101) : m(primo_desde(m_ini)), n(0) {
        chains.assign(m, vector<pair<K, V> >());
    }

    static int primo_desde(int x) {
        if (x < 3) x = 3;
        while (true) {
            bool ok = true;
            for (int d = 2; 1LL * d * d <= x; ++d)
                if (x % d == 0) { ok = false; break; }
            if (ok) return x;
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
        m = primo_desde(2 * m);
        chains.assign(m, vector<pair<K, V> >());
        for (int b = 0; b < (int)viejo.size(); ++b)
            for (int i = 0; i < (int)viejo[b].size(); ++i)
                chains[bucket_de(viejo[b][i].first)].push_back(viejo[b][i]);
    }

    int size() const { return n; }
    bool empty() const { return n == 0; }

    bool has_key(const K &key) const {
        return pos_en(bucket_de(key), key) != -1;
    }

    // Puntero al valor, o NULL si no existe. NO inserta.
    V* find(const K &key) {
        int b = bucket_de(key);
        int i = pos_en(b, key);
        return (i == -1 ? (V*)0 : &chains[b][i].second);
    }

    // Valor si existe, si no el default. NO inserta.
    V get(const K &key, V def = V()) {
        V *p = find(key);
        return (p ? *p : def);
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
};

//  DE AQUI PARA ABAJO SE REEMPLAZA EN CADA PROBLEMA.
//  Lo de arriba nunca se toca.
//  (ejemplo: problema B, contar valores distintos)

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n;
    cin >> n;

    my_map<int, int> freq(2 * n);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        ++freq[x];
    }

    cout << freq.size() << '\n';
    return 0;
}

/*
++freq[x];              // contar (crea en 0 si no existe)
freq.get(x, 0)          // consultar SIN insertar
freq.has_key(x)         // ¿existe?
freq.erase(x)           // borrar, O(1)
freq.size()             // cuántas claves distintas
*/

/* my_map<int,int> freq(2 * n);   // si conoces n: evita rehashes
my_map<int,int> freq;          // si no: crece sola*/
