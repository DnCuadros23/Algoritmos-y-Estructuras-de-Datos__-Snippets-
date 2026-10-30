#include <vector>
#include <iostream>
using namespace std;
int n;
vector<int>recorrido_preorder;
vector<int>recorrido_inorder;
vector<int>recorrido_postorder;
int pre=0;
int post=0;
bool condicion_v=true;
void construirarbol() {
    if (!condicion_v) {
        return;
    }
    if (pre>=n or post>=n) {
        condicion_v=false;
        return;
    }
    //hoja
    int raiz=recorrido_preorder[pre];
    pre++;
    if (raiz==recorrido_postorder[post]){
        post++;
        recorrido_inorder.push_back(raiz);
        return;
    }
    //subarbol izq
    construirarbol();
    if (!condicion_v) {
        return;
    }
    if (post>=n or raiz ==recorrido_postorder[post]) {
        condicion_v=false;
        return;
    }
    recorrido_inorder.push_back(raiz);
    //subarbol drecho
    construirarbol();
    if (!condicion_v) {
        return;
    }
    if (post>= n or raiz!=recorrido_postorder[post]) {
        condicion_v=false;
        return;
    }
    post++;
}


int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin>>n;
    recorrido_preorder.resize(n);
    recorrido_postorder.resize(n);
    for (int i=0;i<n;i++) {
        cin>>recorrido_preorder[i];
    }
    for (int i=0;i<n;i++) {
        cin>>recorrido_postorder[i];
    }
    if (n%2==0) {
        cout <<"IMPOSIBLE\n";
        return 0;
    }
    construirarbol();
    if (!condicion_v) {
        cout <<"IMPOSIBLE\n";
        return 0;
    }
    for (int i=0;i<n;i++) {
        cout<<recorrido_inorder[i]<<" ";
    }
    cout<<"\n";


    return 0;
}