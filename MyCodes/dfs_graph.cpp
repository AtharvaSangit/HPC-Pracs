#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>
using namespace std;

const int MAX_NODES = 100; // Maximum number of nodes in the graph

vector<vector<int>> graph(MAX_NODES); // Adjacency list representation of the graph

void dfs(int start, int n) {
    vector<bool> visited(n, false); // To keep track of visited nodes
    stack<int> stk;
    stk.push(start);

    while (!stk.empty()) {
        int node;
        #pragma omp critical
        {
            node = stk.top();
            stk.pop();
        }

        if (!visited[node]) {
            visited[node] = true;
            cout << node << " "; // Print the current node
            #pragma omp parallel for
            for (int i = 0; i < graph[node].size(); ++i) {
                int neighbor = graph[node][i];
                if (!visited[neighbor]) {
                    #pragma omp critical
                    {
                        stk.push(neighbor); // Push unvisited neighbors onto the stack
                    }
                }
            }
        }
    }
}

int main() {
    int n, m; // n = number of nodes, m = number of edges
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> m;

    cout << "Enter the edges (u v) where u and v are connected vertices:\n";
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        // Assuming the graph is undirected
        graph[u].push_back(v);
        graph[v].push_back(u);
        // If directed, remove one of the above lines
    }

    cout << "Depth First Traversal starting from node 0: ";
    dfs(0, n); // Start DFS from node 0, passing the number of nodes

    return 0;
}



/*

INPUTS

Enter the number of nodes and edges: 6 9
Enter the edges (u v) where u and v are connected vertices:
0 1
0 3
1 2
1 3
1 4
2 4
2 5
3 4
4 5

OUTPUT
Depth First Traversal starting from node 0: 0 3 4 5 2 1 



*/