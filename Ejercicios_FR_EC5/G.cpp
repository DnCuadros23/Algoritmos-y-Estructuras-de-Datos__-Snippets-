#include <iostream>
#include <array>
#include <utility>
#include <algorithm>
using namespace std;
int main() {
    cin.tie(0)->sync_with_stdio(false);
    int A,B,x,y;
    cin >> A >> B >> x >> y;
    long long aristas =0;
    long long entrada =0;
    for (int a=0; a<= A; a++) {
        for (int b=0; b<=B; b++) {
            int d12=min(a,B-b);     //Litros que pasan de la 1 a la 2
            int d21=min(b,A-a); // Litros que pasan de la 2 a la 1

            //Los 6 vecinos del estado (a, b): las 6 jugadas
            array<pair<int,int>,6> t={{
                {A, b}, //Llenar la 1
                {a,B},  //Llenar la 2
                {0,b},     //vaciar la 1
                {a,0},     //vacias la 2
                {a - d12,b+d12},  //pasar de la 1 a la 2
                {a+d21,b-d21}     //pasar de la 2 a la 1
            }};
            for (int k=0; k<6;k++) {
                if (t[k]==make_pair(a, b)) {
                    continue;
                }
                bool repetido=false;
                for (int j=0; j<k; j++) {
                    if (t[j]==t[k]) {
                        repetido=true;
                        break;
                    }
                }
                if (repetido) {
                    continue;
                }
                aristas++;
                if (t[k]==make_pair(x,y)) {
                    entrada++;
                }
            }
        }
    }

    cout<<aristas<<' '<<entrada<<'\n';

    return 0;

}