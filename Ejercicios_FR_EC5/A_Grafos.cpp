#include <iostream>
#include <vector>
#include <string>
#include <array>

//Grafo implicito
using namespace std;
const int dx[4]={-1,1,0,0};
const int dy[4]={0,0,-1,1};

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    vector <string> grid(n);
    for (int i=0;i<n;i++) {
        cin>>grid[i];
    }

    array<int,5> cnt{}; //casillas de tierra de grado k
    long long perimetro=0;

    for (int x=0; x<n;x++) {
        for (int y=0; y<m;y++) {
            if (grid[x][y]!= '#') {
                continue;
            }

            int grado=0;
            for (int k=0; k<4; k++) {
                int nx=x+dx[k];
                int ny=y+dy[k];
                bool dentro =(nx>=0 && nx<n && ny>=0 &&ny<m);
                if (dentro && grid[nx][ny] =='#') {
                    grado++;
                }
            }
            cnt[grado]++;
            perimetro +=4-grado;
        }
    }
    cout << perimetro;
    for (int k=0; k<=4; k++) {
        cout << ' '<< cnt[k];
    }
    cout << "\n";

    return 0;
}





