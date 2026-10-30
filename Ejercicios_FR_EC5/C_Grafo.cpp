#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    cin.tie(0)-> sync_with_stdio(false);
    int n,m;
    cin>>n>>m;

    vector<int> a(m), b(m); //Lista de aristas
    vector <int> seguidores (n+1,0); //Grado de entrada de cada usuario
    unordered_set <long long> aristas; //preguntar adyacencia en O(1)
    aristas.reserve(2*m+1);//evitamos rehashes

    //calve unica para arista dirigida u->v
    auto clave= [n](long long u, long long v) {
        return u*(n+1)+v;
    };


    for (int i=0; i<m; i++) {
        cin>> a[i]>>b[i];
        seguidores[b[i]]++;
        aristas.insert(clave(a[i],b[i]));

    };

    //para cada a-> b existe b->a?
    //se cuenta solo cuando a<b para no contar la misma pareja
    long long mutuos =0;
    for (int i=0; i<m; i++) {
        if (a[i]<b[i]&&aristas.count(clave(b[i],a[i]))) {
            mutuos++;
        }
    }

    //usuarios con mas seguidores con >
    int mejor=1;
    for (int u=2; u<=n; u++) {
        if (seguidores[u]> seguidores[mejor]) {
            mejor=u;
        }
    }
    cout <<mutuos<< ' '<< mejor <<' '<< seguidores[mejor]<<'\n';


    return 0;

}