#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<int> eu(m), ev(m);
    for (int i = 0; i < m; i++) {
        cin >> eu[i] >> ev[i];
        adj[eu[i]].push_back(ev[i]);
        if (eu[i] != ev[i]) adj[ev[i]].push_back(eu[i]);
    }
    vector<int> comp(n + 1, -1);
    vector<long long> vertices;
    int numComp = 0;

    for (int s = 1; s <= n; s++) {
        if (comp[s] != -1) continue;
        vertices.push_back(0);
        queue<int> cola;
        comp[s] = numComp;
        cola.push(s);
        while (!cola.empty()) {
            int u = cola.front();
            cola.pop();
            vertices[numComp]++;
            for (int v : adj[u]) {
                if (comp[v] == -1) {
                    comp[v] = numComp;
                    cola.push(v);
                }
            }
        }
        numComp++;
    }

    vector<long long> aristas(numComp, 0);
    for (int i = 0; i < m; i++) aristas[comp[eu[i]]]++;

    for (int c = 0; c < numComp; c++) {
        if (aristas[c] > vertices[c]) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "SI\n";
    return 0;
}