#include <vector>
#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;

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

ull hash_valor(int k) { return hash_valor((long long)k); }

ull hash_valor(const vector<int> &v) {
    const ull B = 1000003, MOD = 1000000007ULL;
    ull h = 0;
    for (int i = 0; i < (int)v.size(); ++i)
        h = (h * B + (ull)v[i] + 1) % MOD;
    return h;
}

ull hash_valor(const string &s) {
    const ull B = 131, MOD = 1000000007ULL;
    ull h = 0;
    for (int i = 0; i < (int)s.size(); ++i)
        h = (h * B + (ull)(unsigned char)s[i] + 1) % MOD;
    return h;
}

template <typename K, typename V>
struct my_map {
    int m;
    int n;
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

    int pos_en(int b, const K &key) const {
        for (int i = 0; i < (int)chains[b].size(); ++i)
            if (chains[b][i].first == key) return i;
        return -1;
    }

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

    void clear() {
        chains.assign(m, vector<pair<K, V> >());
        n = 0;
    }

    bool has_key(const K &key) const {
        return pos_en(bucket_de(key), key) != -1;
    }

    V* find(const K &key) {
        int b = bucket_de(key);
        int i = pos_en(b, key);
        return (i == -1 ? (V*)0 : &chains[b][i].second);
    }

    V get(const K &key, V def = V()) const {
        int b = bucket_de(key);
        int i = pos_en(b, key);
        return (i == -1 ? def : chains[b][i].second);
    }

    V& operator[](const K &key) {
        int b = bucket_de(key);
        int i = pos_en(b, key);
        if (i != -1) return chains[b][i].second;
        if (n + 1 > 2 * m) {
            rehash();
            b = bucket_de(key);
        }
        chains[b].push_back(make_pair(key, V()));
        ++n;
        return chains[b].back().second;
    }

    void set(const K &key, const V &val) {
        (*this)[key] = val;
    }

    void add(const K &key, const V &delta) {
        (*this)[key] += delta;
    }

    bool erase(const K &key) {
        int b = bucket_de(key);
        int i = pos_en(b, key);
        if (i == -1) return false;
        swap(chains[b][i], chains[b].back());
        chains[b].pop_back();
        --n;
        return true;
    }

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

};
//  DE AQUI PARA ABAJO SE REEMPLAZA EN CADA PROBLEMA.
//  Lo de arriba nunca se toca.
//  (ejemplo: problema B, contar valores distintos)
/*
int main () {
    cin.tie(0) -> sync_with_stdio(false);
    int n;
    cin >> n;
    my_map<string, int> vistos(2 * n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        int cnt[26] = {0};
        for (int j = 0; j < (int)s.size(); ++j)
            ++cnt[s[j] - 'a'];
        string clave;
        clave.reserve(s.size());
        for (int c = 0; c < 26; ++c)
            clave.append(cnt[c], (char)('a' + c));
        vistos[clave] = 1;
    }
    cout << vistos.size() << '\n';
    return 0;
}
*/

int main () {
    cin.tie(0) -> sync_with_stdio(false);
    int n;
    cin >> n;
    my_map<vector<int>, int> vistos(2 * n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        vector<int> cnt(26, 0);
        for (int j = 0; j < (int)s.size(); ++j)
            ++cnt[s[j] - 'a'];
        vistos[cnt] = 1;
    }
    cout << vistos.size() << '\n';
    return 0;
}
