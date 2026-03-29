#include <iostream>
#include <vector>
using namespace std;

const long long INF = 1e18;
int N, M;

int main() {
    cin >> N >> M;
    vector<vector<pair<int,int>>> adj(N + 1);
    vector<int> pool(N + 1, 0);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        pool[v]++;
    }
    vector<long long> dist(N + 1, INF);
    dist[1] = 0;
    vector<int> topo;
    vector<int> deg = pool;
    for (int i = 1; i <= N; i++){
        if (deg[i] == 0) topo.push_back(i);
    }
    for (int t = 0; t < (int)topo.size(); t++) {
        int u = topo[t];
        for (auto [v, w] : adj[u]) {
            if (dist[u] != INF)
                dist[v] = min(dist[v], dist[u] + w);
            deg[v]--;
            if (deg[v] == 0) topo.push_back(v);
        }
    }
    long long ans = 0;
    for (int i = 2; i <= N; i++) ans += dist[i];
    cout << ans;
}