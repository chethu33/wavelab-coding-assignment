#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_NODES 101
#define MAX_EDGES 6001

typedef struct {
    int node;
    int time;
} Edge;

typedef struct {
    Edge edges[MAX_EDGES];
    int numEdges;
} Graph;

Graph createGraph() {
    Graph graph;
    graph.numEdges = 0;
    return graph;
}

void addEdge(Graph* graph, int source, int target, int time) {
    Edge edge;
    edge.node = target;
    edge.time = time;
    graph->edges[graph->numEdges++] = edge;
}

int minDistance(int dist[], bool visited[], int numNodes) {
    int min = INT_MAX;
    int minIndex = -1;

    for (int i = 1; i <= numNodes; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}

int networkDelayTime(int times[MAX_EDGES][3], int numEdges, int numNodes, int source) {
    Graph graph = createGraph();
    for (int i = 0; i < numEdges; i++) {
        int sourceNode = times[i][0];
        int targetNode = times[i][1];
        int time = times[i][2];
        addEdge(&graph, sourceNode, targetNode, time);
    }

    int dist[MAX_NODES];
    bool visited[MAX_NODES];

    for (int i = 1; i <= numNodes; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[source] = 0;

    for (int count = 0; count < numNodes - 1; count++) {
        int u = minDistance(dist, visited, numNodes);

        if (u == -1) {
            break;
        }

        visited[u] = true;

        for (int i = 0; i < graph.numEdges; i++) {
            int v = graph.edges[i].node;
            int w = graph.edges[i].time;

            if (!visited[v] && dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    int maxTime = 0;
    for (int i = 1; i <= numNodes; i++) {
        if (dist[i] == INT_MAX) {
            return -1;
        }
        if (dist[i] > maxTime) {
            maxTime = dist[i];
        }
    }

    return maxTime;
}

int main() {
    int times[MAX_EDGES][3] = {
        {2, 1, 1},
        {2, 3, 1},
        {3, 4, 1}
    };
    int numEdges = 3;
    int numNodes = 4;
    int source = 2;

    int result = networkDelayTime(times, numEdges, numNodes, source);
    printf("Minimum time: %d\n", result);

    return 0;
}
