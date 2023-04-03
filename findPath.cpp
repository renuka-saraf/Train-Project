#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

// Define the structure for a node in the graph
struct Node {
    int id;
    map<int, int> edges; // Map of edge weights to adjacent nodes
};

// Function to add an edge between two nodes
void add_edge(vector<Node>& graph, int source, int destination, int weight) {
    graph[source].edges[destination] = weight;
}

// Function to find the shortest path between two nodes using Dijkstra's algorithm
vector<int> find_shortest_path(vector<Node>& graph, int source, int destination) {
    vector<int> distances(graph.size(), INT_MAX); // Initialize distances to infinity
    vector<int> previous(graph.size(), -1); // Initialize previous nodes to -1
    distances[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min-heap for Dijkstra's algorithm
    pq.push(make_pair(0, source));

    while (!pq.empty()) {
        int current_node = pq.top().second;
        pq.pop();

        for (auto it = graph[current_node].edges.begin(); it != graph[current_node].edges.end(); it++) {
            int neighbor = it->first;
            int weight = it->second;

            int distance = distances[current_node] + weight;
            if (distance < distances[neighbor]) {
                distances[neighbor] = distance;
                previous[neighbor] = current_node;
                pq.push(make_pair(distance, neighbor));
            }
        }
    }

    // Reconstruct the shortest path
    vector<int> path;
    int current_node = destination;
    while (current_node != source) {
        path.insert(path.begin(), current_node);
        current_node = previous[current_node];
    }
    path.insert(path.begin(), source);

    return path;
}

int main() {
    // Example train network with 6 stations
    vector<Node> train_network(6);

    // Add edges between stations
    add_edge(train_network, 0, 1, 4);
    add_edge(train_network, 0, 2, 3);
    add_edge(train_network, 1, 3, 2);
    add_edge(train_network, 1, 4, 5);
    add_edge(train_network, 2, 1, 1);
    add_edge(train_network, 2, 3, 4);
    add_edge(train_network, 3, 5, 6);
    add_edge(train_network, 4, 3, 1);
    add_edge(train_network, 4, 5, 2);

    // Find the shortest path from station 0 to station 5
    vector<int> path = find_shortest_path(train_network, 0, 5);

    // Print the shortest path
    cout << "Shortest path from station 0 to station 5: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << endl;

    return 0;
}
