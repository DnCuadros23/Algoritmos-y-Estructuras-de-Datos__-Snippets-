#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    cin.tie(0)-> sync_with_stdio(false);
    int n,m,q;
    cin>>n>>m>>q;

    vector<vector<int>> adj(n+1); //lista de adyacencia del 1 al n
    for (int i=0; i<m; i++) {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);    //no dirigido: en las dos listas
        adj[v].push_back(u);

    }
    //ordenar los contactos
    for (int u=1; u<=n; u++) {
        sort(adj[u].begin(), adj[u].end());

    }
    while (q--) {
        int tipo, u, val;
        cin>>tipo>>u>>val;
        if (tipo ==1) {
            int k=val;
            if (k>(int)adj[u].size()) {
                cout<<-1<<'\n';

            }
            else {
                cout<<adj[u][k-1]<<'\n';
            }
        }
        else {
            //contactos <= x (x=val): upper_bound apunta al primero>x
            int x=val;
            int cantidad = upper_bound(adj[u].begin(), adj[u].end(), x) - adj[u].begin();
            cout<<cantidad<<'\n';
        }
    }

    return 0;

}