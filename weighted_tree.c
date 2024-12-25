#include <stdio.h>
#include <stdlib.h>

// Define a structure for an edge
typedef struct Edge {
    int node;
    int weight;
    struct Edge* next;
} Edge;

// Create an array of adjacency lists
void addEdge(Edge* adj[], int u, int v, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->node = v;
    newEdge->weight = weight;
    newEdge->next = adj[u];
    adj[u] = newEdge;
}

void printTree(Edge* adj[], int nodes) {
    int totalWeight = 0;  // Variable to store the total weight
    for (int i = 0; i < nodes; i++) {
        printf("Node %d: ", i);
        Edge* temp = adj[i];
        while (temp != NULL) {
            printf("-> (%d, %d) ", temp->node, temp->weight);
            totalWeight += temp->weight;  // Add the weight to total weight
            temp = temp->next;
        }
        printf("\n");
    }
    printf("\nTotal Weight of the Tree: %d\n", totalWeight);
}

int main() {
    int nodes, edges;
    printf("Enter the number of nodes: ");
    scanf("%d", &nodes);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    Edge* adj[nodes];
    for (int i = 0; i < nodes; i++)
        adj[i] = NULL;

    printf("Enter edges in the format (node1 node2 weight):\n");
    for (int i = 0; i < edges; i++) {
        int u, v, weight;
        scanf("%d %d %d", &u, &v, &weight);
        addEdge(adj, u, v, weight);
        addEdge(adj, v, u, weight); // For undirected tree
    }

    printf("\nWeighted Tree Representation:\n");
    printTree(adj, nodes);

    return 0;
}