#include <iostream>
#include <vector>
using namespace std;
int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n,m;
    cin>>n>>m;

    vector <int> grado(n+1,0);//indices 1 al n
    for (int i=0; i<m;i++) {
        int u,v;
        cin>>u>>v;
        grado[u]++;
        grado[v]++;

    }
    int impares=0;
    for (int u=1; u<=n; u++) {
        if (grado[u]%2!=0) {
            impares++;
        }
    }
    if (impares==0) {
        cout<<"CIRCUITO\n";

    }
    else if (impares==2){
        cout<<"CAMINO\n";
    }
    else {
        cout<<"IMPOSIBLE\n";
    }


    return 0;
}