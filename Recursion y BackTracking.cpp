#include <iostream>
#include <vector>
#include <string>
using namespace std;

// =====================================================
// RECURSIÓN: predicado -> caso base -> paso
// =====================================================

// 1. potencia rápida  O(lg n)
long long power(long long a, long long n) {
    if (n == 0) return 1;
    long long h = power(a, n / 2);      // una sola llamada
    if (n % 2 == 0) return h * h;
    return h * h * a;
}

// 2. hanoi: mover n de src a snk usando pivot  (2^n - 1 movs)
void hanoi(int n, int src, int pivot, int snk) {
    if (n == 0) return;
    hanoi(n - 1, src, snk, pivot);
    cout << n << " " << src << " " << snk << '\n';
    hanoi(n - 1, pivot, src, snk);
}

// 3. prefija: devuelve valor, avanza pos
long long eval_prefix(const vector<string>& t, int& pos) {
    string s = t[pos++];
    if (s != "+" && s != "-" && s != "*") return stoll(s);
    long long a = eval_prefix(t, pos);
    long long b = eval_prefix(t, pos);   // desde donde terminó a
    if (s == "+") return a + b;
    if (s == "-") return a - b;
    return a * b;
}

// =====================================================
// BACKTRACKING: base -> por opción: verificar, hacer, explorar, deshacer
// =====================================================

int n;
vector<int> a;
vector<int> actual;            // solución parcial
long long soluciones = 0;

// 4. contar subconjuntos con suma s  (tomar / no tomar)
long long count_sum(int i, long long s) {
    if (s < 0) return 0;                       // poda (positivos)
    if (i == n) return s == 0;
    return count_sum(i + 1, s) + count_sum(i + 1, s - a[i]);
}

// 5. listar subconjuntos
void subsets(int i) {
    if (i == n) {
        for (int x : actual) cout << x << " ";
        cout << '\n';
        return;
    }
    subsets(i + 1);                            // no tomar
    actual.push_back(a[i]);                    // hacer
    subsets(i + 1);
    actual.pop_back();                         // deshacer
}

// 6. permutaciones
vector<bool> usado;
void permutations() {
    if ((int)actual.size() == n) {
        for (int x : actual) cout << x << " ";
        cout << '\n';
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (usado[i]) continue;                // verificar
        usado[i] = true; actual.push_back(a[i]);
        permutations();
        actual.pop_back(); usado[i] = false;
    }
}

// 7. palabras distintas (letras repetidas)
int cnt[26];
string palabra;
void words(int len) {
    if ((int)palabra.size() == len) {
        cout << palabra << '\n';
        return;
    }
    for (int c = 0; c < 26; ++c) {             // por tipo de letra
        if (cnt[c] == 0) continue;
        --cnt[c]; palabra.push_back('a' + c);
        words(len);
        palabra.pop_back(); ++cnt[c];
    }
}

// 8. n reinas: contar
vector<bool> col, diag, anti;
long long queens(int f) {
    if (f == n) return 1;
    long long total = 0;
    for (int c = 0; c < n; ++c) {
        if (col[c] || diag[f + c] || anti[f - c + n - 1]) continue;
        col[c] = diag[f + c] = anti[f - c + n - 1] = true;
        total += queens(f + 1);
        col[c] = diag[f + c] = anti[f - c + n - 1] = false;
    }
    return total;
}

// 9. primera solución: corta al encontrar
bool exists_sum(int i, long long s) {
    if (s == 0) return true;
    if (s < 0 || i == n) return false;
    actual.push_back(a[i]);
    if (exists_sum(i + 1, s - a[i])) return true;   // cortar
    actual.pop_back();
    return exists_sum(i + 1, s);
}

// =====================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int op;
    cin >> op;

    if (op == 1) {                     // a n
        long long x, e; cin >> x >> e;
        cout << power(x, e) << '\n';
    } else if (op == 2) {              // n
        cin >> n;
        hanoi(n, 1, 2, 3);
    } else if (op == 3) {              // k tokens
        int k; cin >> k;
        vector<string> t(k);
        for (auto& s : t) cin >> s;
        int pos = 0;
        cout << eval_prefix(t, pos) << '\n';
    } else if (op == 4 || op == 9) {   // n S a...
        long long S; cin >> n >> S;
        a.assign(n, 0);
        for (int& x : a) cin >> x;
        if (op == 4) cout << count_sum(0, S) << '\n';
        else if (exists_sum(0, S)) {
            for (int x : actual) cout << x << " ";
            cout << '\n';
        } else cout << "NO\n";
    } else if (op == 5 || op == 6) {   // n a...
        cin >> n;
        a.assign(n, 0);
        for (int& x : a) cin >> x;
        usado.assign(n, false);
        if (op == 5) subsets(0);
        else permutations();
    } else if (op == 7) {              // palabra
        string w; cin >> w;
        for (char ch : w) ++cnt[ch - 'a'];
        words((int)w.size());
    } else if (op == 8) {              // n
        cin >> n;
        col.assign(n, false);
        diag.assign(2 * n - 1, false);
        anti.assign(2 * n - 1, false);
        cout << queens(0) << '\n';
    }
    return 0;
}