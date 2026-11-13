#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//arreglo de estados de cada nodo
// - vis[1...n] -> no visitado, en proceso, finalizado
//arreglo de enteros del nodo en el DFS-Tree
// - pad[1...n]


//-Tiempo de entrada y tiempo de salida (no siempre va)
// in[i...n] ---- Timestamps
// out[1...n]
const int N = 100000 + 1;
int n, m;
int pi[N];
int vis[N]; // 0 -> sin visitar, 1 -> en proceso, 2 -> finalizado
vector<int> G[N];
void DFS(int u) {
    vis[u] = 1;
    for (int &v : G[u]) {
        if (vis[v]) continue;
        pi[v] = u;
        DFS(v);
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    int s, t;
    cin >> s >> t;
    for (int i = 1; i <= n; ++i) sort(G[i].begin(), G[i].end());
    DFS(s);
    if (!vis[t]) {
        cout << "no solution" << '\n';
        return 0;
    }
    stack<int> S;
    while (t != s) {
        S.emplace(t);
        t = pi[t];
    }
    cout << s;
    while (not S.empty()) {
        cout << " " << S.top();
        S.pop();
    }
    cout << '\n';
    return 0;
}
