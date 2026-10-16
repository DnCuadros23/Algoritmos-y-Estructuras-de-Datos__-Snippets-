#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int f(int i, int s, int n, vector <int > &a) {
    if (s<0) return 0;
    if (i==n) return s==0;
    return f(i+1,s,n,a)+f(i+1,s-a[i],n,a);

}
int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n,S;
    cin>>n>>S;
    vector <int > a(n);
    for (int i=0;i<n;i++) {cin >> a[i];}
    cout<<f(0,S,n,a)<<"\n";

    return 0;
}
