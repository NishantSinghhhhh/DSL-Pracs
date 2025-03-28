#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

static const int MAXN = 50; // maximum possible vertices

// Global adjacency matrix for simplicity (could be local)
int adj[MAXN][MAXN];

// =============== DFS (Recursive) ===============
void dfsRecursiveUtil(int start, vector<bool> &visited, int n) {
    // Mark current node as visited
    visited[start] = true;
    cout << start << " ";

    // Recur for all adjacent vertices
    for (int v = 0; v < n; v++) {
        if (adj[start][v] == 1 && !visited[v]) {
            dfsRecursiveUtil(v, visited, n);
        }
    }
}

// Wrapper for DFS Recursive
void dfsRecursive(int start, int n) {
    vector<bool> visited(n, false);
    cout << "DFS (Recursive) from vertex " << start << ": ";
    dfsRecursiveUtil(start, visited, n);
    cout << "\n";
}

// =============== DFS (Iterative) ===============
void dfsIterative(int start, int n) {
    vector<bool> visited(n, false);
    stack<int> st;
    st.push(start);

    cout << "DFS (Iterative) from vertex " << start << ": ";

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        if (!visited[u]) {
            visited[u] = true;
            cout << u << " ";

            // Push neighbors in reverse order if you want the same order as recursion
            // For simplicity, we push in normal ascending order
            for (int v = n - 1; v >= 0; v--) {
                if (adj[u][v] == 1 && !visited[v]) {
                    st.push(v);
                }
            }
        }
    }
    cout << "\n";
}

// =============== BFS (Iterative) ===============
void bfsIterative(int start, int n) {
    vector<bool> visited(n, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);

    cout << "BFS (Iterative) from vertex " << start << ": ";

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";

        // Enqueue all unvisited neighbors
        for (int v = 0; v < n; v++) {
            if (adj[u][v] == 1 && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << "\n";
}

// =============== BFS (Recursive) ===============
void bfsRecursiveUtil(queue<int> &q, vector<bool> &visited, int n) {
    if (q.empty()) return;

    int u = q.front();
    q.pop();
    cout << u << " ";

    // Enqueue unvisited neighbors
    for (int v = 0; v < n; v++) {
        if (adj[u][v] == 1 && !visited[v]) {
            visited[v] = true;
            q.push(v);
        }
    }

    // Recurse
    bfsRecursiveUtil(q, visited, n);
}

// Wrapper for BFS Recursive
void bfsRecursive(int start, int n) {
    vector<bool> visited(n, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);

    cout << "BFS (Recursive) from vertex " << start << ": ";
    bfsRecursiveUtil(q, visited, n);
    cout << "\n";
}

// =============== Connected Components ===============
int findConnectedComponents(int n) {
    vector<bool> visited(n, false);
    int components = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            // We can use BFS or DFS here. Let's use BFS (Iterative) for example:
            components++;

            // BFS from i
            queue<int> q;
            visited[i] = true;
            q.push(i);

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                // for all neighbors
                for (int v = 0; v < n; v++) {
                    if (adj[u][v] == 1 && !visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }

    return components;
}

// =============== Main ===============
int main() {
    int n, e;
    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> e;

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }

    cout << "Enter edges (u v) for an undirected graph:\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        // simple error-check: assume 0 <= u,v < n
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    int start;
    cout << "Enter a starting vertex for traversals: ";
    cin >> start;

    // 1) DFS (Recursive)
    dfsRecursive(start, n);

    // 2) DFS (Iterative)
    dfsIterative(start, n);

    // 3) BFS (Iterative)
    bfsIterative(start, n);

    // 4) BFS (Recursive)
    bfsRecursive(start, n);

    // Check connectivity
    int c = findConnectedComponents(n);
    if (c == 1) {
        cout << "\nGraph is connected.\n";
    } else {
        cout << "\nGraph is NOT connected. It has " << c << " connected components.\n";
    }

    return 0;
}
