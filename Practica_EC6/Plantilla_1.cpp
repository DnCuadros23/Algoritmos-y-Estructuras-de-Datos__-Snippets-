// ============================================================
//  PLANTILLAS DFS  —  C++17, sin bits/stdc++.h
//  Copia solo el bloque que necesites al problema.
// ============================================================
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

int n, m;
vector<vector<int>> adj;   // adj[u] = vecinos de u (nodos 1..n)
vector<bool> vis;

// ------------------------------------------------------------
// 1) DFS RECURSIVO  —  O(n + m)
//    Ojo: con n ~ 1e5-1e6 en forma de cadena puede desbordar
//    la pila. Si pasa (RE), usa la versión iterativa (2).
// ------------------------------------------------------------
void dfs(int u) {
    vis[u] = true;
    for (int v : adj[u])
        if (!vis[v]) dfs(v);
}

// ------------------------------------------------------------
// 2) DFS ITERATIVO con pila  —  O(n + m), sin riesgo de stack overflow
// ------------------------------------------------------------
void dfsIter(int s) {
    stack<int> st;
    st.push(s);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (vis[u]) continue;          // puede entrar repetido a la pila
        vis[u] = true;
        for (int v : adj[u])
            if (!vis[v]) st.push(v);
    }
}

// ------------------------------------------------------------
// 3) CONTAR COMPONENTES CONEXAS (grafo no dirigido)
// ------------------------------------------------------------
int contarComponentes() {
    vis.assign(n + 1, false);
    int comp = 0;
    for (int u = 1; u <= n; u++)
        if (!vis[u]) { comp++; dfs(u); }
    return comp;
}

// ------------------------------------------------------------
// 4) CICLO EN GRAFO NO DIRIGIDO  (no volver por el padre)
// ------------------------------------------------------------
bool cicloNoDir(int u, int p) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (vis[v]) return true;             // arista a ya visitado = ciclo
        if (cicloNoDir(v, u)) return true;
    }
    return false;
}
// uso: vis.assign(n+1,false); for u: if(!vis[u] && cicloNoDir(u,-1)) -> hay ciclo

// ------------------------------------------------------------
// 5) CICLO EN GRAFO DIRIGIDO + ORDEN TOPOLÓGICO (colores)
//    0 = blanco (no visto), 1 = gris (en la pila), 2 = negro (terminado)
//    Arista a un gris = ciclo.
// ------------------------------------------------------------
vector<int> color, topo;
bool hayCiclo = false;

void dfsTopo(int u) {
    color[u] = 1;
    for (int v : adj[u]) {
        if (color[v] == 1) hayCiclo = true;
        else if (color[v] == 0) dfsTopo(v);
    }
    color[u] = 2;
    topo.push_back(u);                 // se agrega al TERMINAR
}
// uso:
//   color.assign(n+1,0); topo.clear();
//   for u=1..n: if(color[u]==0) dfsTopo(u);
//   reverse(topo.begin(), topo.end());   // orden topológico
//   si hayCiclo -> no existe orden topológico

// ------------------------------------------------------------
// 6) DFS EN GRILLA (flood fill / contar islas)  —  O(R*C)
// ------------------------------------------------------------
int R, C;
vector<string> grid;
vector<vector<bool>> visG;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void dfsGrid(int x, int y) {
    visG[x][y] = true;
    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx >= 0 && nx < R && ny >= 0 && ny < C &&
            !visG[nx][ny] && grid[nx][ny] != '#')
            dfsGrid(nx, ny);
    }
}
// uso: visG.assign(R, vector<bool>(C,false));
//      for i,j: if(grid[i][j]=='.' && !visG[i][j]) { islas++; dfsGrid(i,j); }

// ------------------------------------------------------------
// 7) DFS EN ÁRBOL: profundidad, tamaño de subárbol, padre
// ------------------------------------------------------------
vector<int> par, depth_, sub;
void dfsArbol(int u, int p) {
    par[u] = p;
    sub[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        depth_[v] = depth_[u] + 1;
        dfsArbol(v, u);
        sub[u] += sub[v];
    }
}
// uso: par.assign(n+1,0); depth_.assign(n+1,0); sub.assign(n+1,0); dfsArbol(1,0);

// ============================================================
//  MAIN de ejemplo: lee n m y m aristas no dirigidas,
//  imprime el número de componentes.
// ============================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    adj.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);           // quitar si es DIRIGIDO
    }
    cout << contarComponentes() << "\n";
    return 0;
}