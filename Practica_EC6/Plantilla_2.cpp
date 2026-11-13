// ============================================================
//  PLANTILLAS DIJKSTRA  —  C++17, sin bits/stdc++.h
//  Copia solo el bloque que necesites al problema.
// ============================================================
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <tuple>
#include <utility>
#include <string>
#include <algorithm>
using namespace std;

using ll = long long;
const ll INF = 4e18;                       // más grande que cualquier respuesta
using pli = pair<ll, int>;                 // (distancia, nodo)  ← d PRIMERO
// min-heap: priority_queue es max-heap por defecto, por eso greater<>
using MinHeap = priority_queue<pli, vector<pli>, greater<pli>>;

int n, m;
vector<vector<pair<int, ll>>> adj;         // adj[u] = {(v, w)}
vector<ll> dist;
vector<int> padre;

// ------------------------------------------------------------
// 1) DIJKSTRA BÁSICO + padre   —  O((n + m) log n)
//    Pesos >= 0. dist[v] == INF  ->  v no alcanzable.
// ------------------------------------------------------------
void dijkstra(int s) {
    dist.assign(n + 1, INF);
    padre.assign(n + 1, -1);
    MinHeap pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;         // entrada vieja
        // if (u == t) break;              // parar antes si solo importa t
        for (auto [v, w] : adj[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                padre[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

// ------------------------------------------------------------
// 2) RECONSTRUIR CAMINO s -> t (después de dijkstra(s))
// ------------------------------------------------------------
vector<int> camino(int t) {
    vector<int> c;
    if (dist[t] == INF) return c;          // vacío = no hay camino
    for (int v = t; v != -1; v = padre[v]) c.push_back(v);
    reverse(c.begin(), c.end());
    return c;
}

// ------------------------------------------------------------
// 3) VARIAS FUENTES (hospital / salida más cercana)
//    Todas entran con dist 0; lo demás es igual.
// ------------------------------------------------------------
void dijkstraMulti(const vector<int>& fuentes) {
    dist.assign(n + 1, INF);
    MinHeap pq;
    for (int f : fuentes) { dist[f] = 0; pq.push({0, f}); }
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u])
            if (d + w < dist[v]) { dist[v] = d + w; pq.push({dist[v], v}); }
    }
}

// ------------------------------------------------------------
// 4) CONTAR CAMINOS MÍNIMOS (mod 1e9+7)  —  pesos >= 1
//    mejora estricta -> copiar cnt[u];  empate -> sumar cnt[u]
// ------------------------------------------------------------
const ll MOD = 1e9 + 7;
vector<ll> cnt;
void dijkstraContar(int s) {
    dist.assign(n + 1, INF);
    cnt.assign(n + 1, 0);
    MinHeap pq;
    dist[s] = 0; cnt[s] = 1;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                cnt[v] = cnt[u];
                pq.push({dist[v], v});
            } else if (d + w == dist[v]) {
                cnt[v] = (cnt[v] + cnt[u]) % MOD;
            }
        }
    }
}

// ------------------------------------------------------------
// 5) ¿LA ARISTA (u,v,w) ESTÁ EN ALGÚN CAMINO MÍNIMO s->t?
//    Corre dijkstra desde s (ds) y desde t (dt).
//    En dirigido, dt se calcula sobre el grafo INVERTIDO.
// ------------------------------------------------------------
// vector<ll> ds, dt;
// dijkstra(s); ds = dist;  dijkstra(t); dt = dist;
// bool sirve = ds[u] != INF && dt[v] != INF && ds[u] + w + dt[v] == ds[t];

// ------------------------------------------------------------
// 6) DIJKSTRA EN GRILLA  —  costo de ENTRAR a la casilla
//    dist inicial = costo de la casilla de inicio.
// ------------------------------------------------------------
int R, C;
vector<vector<ll>> costo;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

ll dijkstraGrilla(int sx, int sy, int tx, int ty) {
    vector<vector<ll>> d(R, vector<ll>(C, INF));
    priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>,
                   greater<tuple<ll, int, int>>> pq;
    d[sx][sy] = costo[sx][sy];
    pq.push({d[sx][sy], sx, sy});
    while (!pq.empty()) {
        auto [cd, x, y] = pq.top(); pq.pop();
        if (cd > d[x][y]) continue;
        if (x == tx && y == ty) return cd;
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
            // if (pared[nx][ny]) continue;
            if (cd + costo[nx][ny] < d[nx][ny]) {
                d[nx][ny] = cd + costo[nx][ny];
                pq.push({d[nx][ny], nx, ny});
            }
        }
    }
    return -1;                             // inalcanzable
}

// ------------------------------------------------------------
// 7) GRAFO DE ESTADOS: hasta K aristas GRATIS
//    estado = (nodo, j gratis usadas), j en [0..K]
//    (mismo molde para combustible, llaves, paridad...)
// ------------------------------------------------------------
ll dijkstraGratis(int s, int t, int K) {
    vector<vector<ll>> d(n + 1, vector<ll>(K + 1, INF));
    priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>,
                   greater<tuple<ll, int, int>>> pq;
    d[s][0] = 0;
    pq.push({0, s, 0});
    while (!pq.empty()) {
        auto [cd, u, j] = pq.top(); pq.pop();
        if (cd > d[u][j]) continue;
        for (auto [v, w] : adj[u]) {
            if (cd + w < d[v][j]) {                     // pagar
                d[v][j] = cd + w;
                pq.push({d[v][j], v, j});
            }
            if (j < K && cd < d[v][j + 1]) {            // usar una gratis
                d[v][j + 1] = cd;
                pq.push({cd, v, j + 1});
            }
        }
    }
    ll ans = INF;
    for (int j = 0; j <= K; j++) ans = min(ans, d[t][j]);
    return ans == INF ? -1 : ans;
}

// ------------------------------------------------------------
// 8) DIJKSTRA DENSO sin heap  —  O(n^2), cuando m ~ n^2
//    (aquí con matriz de adyacencia; W[u][v] = INF si no hay arista)
// ------------------------------------------------------------
vector<ll> dijkstraDenso(int s, const vector<vector<ll>>& W) {
    vector<ll> d(n + 1, INF);
    vector<bool> listo(n + 1, false);
    d[s] = 0;
    for (int it = 0; it < n; it++) {
        int u = -1;
        for (int v = 1; v <= n; v++)
            if (!listo[v] && (u == -1 || d[v] < d[u])) u = v;
        if (u == -1 || d[u] == INF) break;
        listo[u] = true;
        for (int v = 1; v <= n; v++)
            if (W[u][v] != INF && d[u] + W[u][v] < d[v]) d[v] = d[u] + W[u][v];
    }
    return d;
}

// ------------------------------------------------------------
// 9) BONUS: BFS 0-1 (pesos solo 0 o 1)  —  O(n + m)
//    peso 0 -> push_front, peso 1 -> push_back
// ------------------------------------------------------------
void bfs01(int s) {
    dist.assign(n + 1, INF);
    deque<int> dq;
    dist[s] = 0;
    dq.push_back(s);
    while (!dq.empty()) {
        int u = dq.front(); dq.pop_front();
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) dq.push_front(v);
                else        dq.push_back(v);
            }
        }
    }
}

// ============================================================
//  MAIN de ejemplo: lee n m, m aristas (u v w) no dirigidas.
//  Imprime dist de 1 a n y el camino (o -1).
// ============================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    adj.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});          // quitar si es DIRIGIDO
    }

    // Varios casos de prueba: dist/padre se reinician dentro de dijkstra()
    dijkstra(1);
    if (dist[n] == INF) { cout << -1 << "\n"; return 0; }
    cout << dist[n] << "\n";
    for (int v : camino(n)) cout << v << " ";
    cout << "\n";
    return 0;
}