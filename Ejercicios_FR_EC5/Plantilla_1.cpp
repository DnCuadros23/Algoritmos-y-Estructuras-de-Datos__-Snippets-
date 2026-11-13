
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n,m;
    // n es la cantidad de vertices
    // m la cantidad de aristas que hay por lo que vamos a leer aristas
    cin>>n>>m;
    // No dirigido
    auto claveNoDir = [n](long long u, long long v) {
        if (u > v) {
            swap(u, v);
        }
        return u * (n + 1) + v;
    };
    vector<long long> a(m), b(m); //Lista de aristas

    unordered_set<long long> existe;       // ¿existe la arista?
    existe.reserve(2*m+1);
    if (m<n-1) {
        cout<<"NO";
        return 0;
    }
    for (int i=0; i<m;i++) {
        int u, v;
        cin>>u>>v;
        existe.insert(claveNoDir(u, v));
        if (u > v) {
            a.push_back(v);
            b.push_back(u);
        }
        else {
            a.push_back(u);
            b.push_back(v);
        }
    }
    for (int i=0; i<m;i++) {
        bool hay = existe.count(claveNoDir(a[i], b[i]));
        if (!hay) {
            cout<<"NO";
            return 0;
        }
    }
    cout<<"SI";
    return 0;
}