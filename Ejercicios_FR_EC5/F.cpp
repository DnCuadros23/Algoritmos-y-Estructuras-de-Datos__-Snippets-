#include <iostream>
#include <vector>

using namespace std;
int main () {
    cin.tie(0)->sync_with_stdio(false)  ;
    int n,m,q;
    cin>>n>>m>>q;
    vector<vector<int>> adj(n+1); //lista de adyacencia
    for (int i=0; i<m; i++) {
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b); //amistad mutua en las dos aristad
        adj[b].push_back(a);

    }
    vector <char> marca(n+1,0); //marca[x]=1 si x es amigo de u
    while (q--) {
        int u,v;
        cin>>u>>v;

        //marca a los amigos de u
        for (int x : adj[u]) {
            marca[x] =1;
        }


        //contar los amigos de v que estan marcados
        int comunes=0;
        for (int y: adj[v]) {
            if (marca[y]) {
                comunes++;
            }
        }


        //limpiar solo lo que se marco : O (deg u)
        for (int x: adj[u]) {
            marca[x]=0;
        }
        cout << comunes << '\n';

    }

    return 0;

}