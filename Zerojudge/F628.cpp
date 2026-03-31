#include <iostream>
#include <vector>
using namespace std;

const long long INF = 1e18;  // big number for "not reachable"
int N, M;                     // number of nodes and number of edges

int main() {
    cin >> N >> M;  // read number of nodes and edges

    vector<vector<pair<int,int>>> adj(N + 1); // list of edges: adj[u] = list of (v, weight)
    vector<int> pool(N + 1, 0);              // count how many edges go into each node

    // read edges
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;      // edge from u to v with weight w
        adj[u].push_back({v, w}); // save edge
        pool[v]++;                // increase count of edges going into v
    }

    vector<long long> dist(N + 1, INF); // shortest distance to each node, start with big number
    dist[1] = 0;                         // distance to node 1 itself is 0

    vector<int> topo;          // list of nodes ready to process
    vector<int> deg = pool;    // copy of edge counts to modify

    // find all nodes with no edges going into them
    for (int i = 1; i <= N; i++) {
        if (deg[i] == 0) topo.push_back(i);
    }

    // process nodes in order
    for (int t = 0; t < (int)topo.size(); t++) {
        int u = topo[t];  // current node
        for (auto [v, w] : adj[u]) { // look at each node we can go to from u
            if (dist[u] != INF)       // only update if we can reach u
                dist[v] = min(dist[v], dist[u] + w); // update shortest distance to v
            deg[v]--;                // one less incoming edge to v
            if (deg[v] == 0) topo.push_back(v); // if v has no more incoming edges, add it to list
        }
    }

    // add up distances from node 1 to all other nodes
    long long ans = 0;
    for (int i = 2; i <= N; i++) ans += dist[i];

    cout << ans;  // print the total
}

/*
Main logic: Start with distance from 1 = 0, all others = big number. 
Go through each point one by one. For each point, check the places it can go and see if 
going through this point makes the distance shorter. Keep doing this until all points are checked. 
At the end, add up all distances from 1 to the others.
*/