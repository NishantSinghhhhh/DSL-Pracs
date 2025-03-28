#include <bits/stdc++.h>
using namespace std;

const int V = 7; // 7 offices
const int INF = INT_MAX;

// ------------------- PRIM'S (Simpler) -------------------
void primMST(int cost[V][V]) {
    vector<int> key(V, INF);
    vector<bool> inMST(V, false);
    key[0] = 0; 
    int totalCost = 0;

    for (int i = 0; i < V - 1; i++) {
        int u = -1;
        int minKey = INF;
        // find the unvisited vertex with the smallest key
        for (int v = 0; v < V; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }
        inMST[u] = true;
        if (minKey != INF) {
            totalCost += minKey;
        }

        // update keys of neighbors
        for (int w = 0; w < V; w++) {
            if (cost[u][w] != INF && !inMST[w] && cost[u][w] < key[w]) {
                key[w] = cost[u][w];
            }
        }
    }

    cout << "Prim's MST total cost: " << totalCost << "\n";
}

// ------------------- KRUSKAL'S (Simpler) -------------------
struct Edge {
    int u, v, w;
};

bool cmp(const Edge &a, const Edge &b) {
    return a.w < b.w;
}

int findSet(vector<int> &parent, int x) {
    if (parent[x] == x) return x;
    return parent[x] = findSet(parent, parent[x]);
}

void unionSet(vector<int> &parent, int x, int y) {
    parent[findSet(parent, x)] = findSet(parent, y);
}

int kruskalMST(vector<Edge> &edges) {
    sort(edges.begin(), edges.end(), cmp);

    vector<int> parent(V);
    for(int i=0; i<V; i++) parent[i] = i;

    int mstCost = 0;
    int edgesUsed = 0;
    for(auto &e : edges) {
        int setU = findSet(parent, e.u);
        int setV = findSet(parent, e.v);
        if(setU != setV) {
            unionSet(parent, setU, setV);
            mstCost += e.w;
            edgesUsed++;
            if(edgesUsed == V-1) break;
        }
    }
    return mstCost;
}

// ------------------- MAIN DEMO -------------------
int main() {
    // 1) Adjacency matrix for Prim's
    int cost[V][V];
    for(int i=0; i<V; i++){
        for(int j=0; j<V; j++){
            cost[i][j] = INF;
        }
    }
    // We'll define some edges (u, v, w):
    // (0,1,4), (0,6,10), (0,2,9), (1,2,8), (2,3,5),
    // (2,4,2), (2,6,7), (3,4,3), (3,5,7), (4,6,6), (5,6,11).

    auto addCost = [&](int u, int v, int w){
        cost[u][v] = w;
        cost[v][u] = w; // undirected
    };

    addCost(0,1,4);
    addCost(0,6,10);
    addCost(0,2,9);
    addCost(1,2,8);
    addCost(2,3,5);
    addCost(2,4,2);
    addCost(2,6,7);
    addCost(3,4,3);
    addCost(3,5,7);
    addCost(4,6,6);
    addCost(5,6,11);

    cout << "=== Prim's Algorithm ===\n";
    primMST(cost);

    // 2) Edge list for Kruskal's
    vector<Edge> edges = {
        {0,1,4}, {0,6,10}, {0,2,9}, {1,2,8}, {2,3,5},
        {2,4,2}, {2,6,7},  {3,4,3}, {3,5,7}, {4,6,6}, {5,6,11}
    };

    cout << "\n=== Kruskal's Algorithm ===\n";
    int kruskalCost = kruskalMST(edges);
    cout << "Kruskal's MST total cost: " << kruskalCost << "\n";

    return 0;
}
