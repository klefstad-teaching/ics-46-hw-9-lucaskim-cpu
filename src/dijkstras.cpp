#include "dijkstras.h"


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    
    vector<int> distance(n, INF);
    previous.resize(n, -1);
    vector<bool> visited(n, false);
    
    auto comp = [&distance](int a, int b) {
        return distance[a] > distance[b]; 
    };
    
    priority_queue<int, vector<int>, decltype(comp)> pq(comp);
    
    distance[source] = 0;
    pq.push(source);
    
    // Process vertices
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();

        // Skip if already visited
        if (visited[u]) {
            continue;
        }
        
        visited[u] = true;
    
        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            
            if (!visited[v] && distance[u] != INF && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(v);
            }
        }
    }
    
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    
    if (distances[destination] == INF) {
        return path;
    }
    
    int curr = destination;
    while (curr != -1) {
        path.push_back(curr);
        curr = previous[curr];
    }
    reverse(path.begin(), path.end());
    return path;
}

// Print 
void print_path(const vector<int>& path, int total) {
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}