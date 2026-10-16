#include <iostream>
#include <bits/stdc++.h>
using namespace std;
const int N =9;
string s[N][N+1];
bool col_values[N][N+1];
bool row_values[N][N+1];
bool candidate[N][N][N+1];
void solve(int x, int y) {
    if (x==N) {
        for (int i=0;i<N;++i) {
            cout<< s[i]<<"\n";
        }
        exit(0);
    }
    if (y==N) {
        solve(x+1,y);
    }
    if (s[x][y]!= ".") {
        solve (x,y+1);
    }
    else {
        for
    }
}


void update(int x, int y, int c, bool new_value) {
    for (int row=0;row<N;++row) {

    }
}
int main() {
    cin.tie(0)->sync_with_stdio(false);
    for (int i=0;i<N;++i) {
        cin >> s[i];
        for (int j=0;j<N;++j) {
            fill_n(candidate[i][j],N+1,true);

        }
    }
    for (int x=0)
}
