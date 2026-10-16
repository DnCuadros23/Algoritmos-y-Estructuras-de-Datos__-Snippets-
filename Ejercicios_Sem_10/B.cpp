#include <iostream>
#include <bits/stdc++.h>
using namespace std;
void hanoi(int n, int src, int pivot, int snk) {
    if (n==1) {
        cout<<n<<" "<<src<<" "<<snk<<"\n";
        return;
    }
    hanoi(n-1,src,snk,pivot);
    cout<<n<<" "<< src<< " "<<snk<<"\n";
    hanoi(n-1,pivot,src,snk);

}
int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin>>n;
    hanoi(n,1,2,3);
    return 0;
}
