#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;


int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n,m,q;
    cin>>n>>m>>q;


    //clave unica del par No ordenado [u,v] siempre el menor primero
    auto clave =[n](long long u, long long v) {
        if (u>v)swap(u,v);
        return u*(n+1)+v;

    };
    unordered_map<long long, int> cables; // par {u,v} -> cuantos clabes los unen
    cables.reserve(2*m+1);

    for (int i=0; i<m; i++) {
        int u ,v ;
        cin>>u>>v;
        cables[clave(u,v)]++; // aristas multiples se acumulan

    }
    while (q--) {
        int u,v;
        cin>>u>>v;
        auto it= cables.find(clave(u,v));
        cout <<(it==cables.end()?0:it->second)<<'\n';
    }


    return 0;
}