#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

Graph *createGraph(int vertices) {
    Graph *g = malloc(sizeof(Graph));
    g->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        g->adjList[i] = NULL;
        g->names[i] = NULL;
    }
    return g;
}

void setVertexName(Graph *g, int v, const char *name) {
    g->names[v] = malloc(strlen(name) + 1);
    strcpy(g->names[v], name);
}

static void addDirectedEdge(Graph *g, int src, int dest, int weight) {
    Edge *e = malloc(sizeof(Edge));
    e->dest = dest;
    e->weight = weight;
    e->next = g->adjList[src];
    g->adjList[src] = e;
}

void addEdge(Graph *g, int src, int dest, int weight) {
    addDirectedEdge(g, src, dest, weight);
    addDirectedEdge(g, dest, src, weight);
}

void freeGraph(Graph *g) {
    for (int i = 0; i < g->numVertices; i++) {
        Edge *e = g->adjList[i];
        while (e) {
            Edge *tmp = e;
            e = e->next;
            free(tmp);
        }
        free(g->names[i]);
    }
    free(g);
}

void printGraph(const Graph *g) {
    for (int i = 0; i < g->numVertices; i++) {
        printf("  [%d] %-16s -> ", i, g->names[i]);
        Edge *e = g->adjList[i];
        while (e) {
            printf("%s(%d) ", g->names[e->dest], e->weight);
            e = e->next;
        }
        printf("\n");
    }
}

int bfs(const Graph *g, int start, int *order) {
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = 0, back = 0, count = 0;

    visited[start] = 1;
    queue[back++] = start;

    while (front < back) {
        int u = queue[front++];
        order[count++] = u;
        for (Edge *e = g->adjList[u]; e; e = e->next) {
            if (!visited[e->dest]) {
                visited[e->dest] = 1;
                queue[back++] = e->dest;
            }
        }
    }
    return count;
}

static void dfsVisit(const Graph *g, int u, int *visited, int *order, int *count) {
    visited[u] = 1;
    order[(*count)++] = u;
    for (Edge *e = g->adjList[u]; e; e = e->next) {
        if (!visited[e->dest]) {
            dfsVisit(g, e->dest, visited, order, count);
        }
    }
}

int dfs(const Graph *g, int start, int *order) {
    int visited[MAX_VERTICES] = {0};
    int count = 0;
    dfsVisit(g, start, visited, order, &count);
    return count;
}

void dijkstra(const Graph *g, int start, int dist[MAX_VERTICES], int prev[MAX_VERTICES]) {
    int visited[MAX_VERTICES] = {0};

    for (int i = 0; i < g->numVertices; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[start] = 0;

    for (int count = 0; count < g->numVertices; count++) {
        int u = -1, best = INF;
        for (int i = 0; i < g->numVertices; i++) {
            if (!visited[i] && dist[i] < best) {
                best = dist[i];
                u = i;
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (Edge *e = g->adjList[u]; e; e = e->next) {
            if (!visited[e->dest] && dist[u] + e->weight < dist[e->dest]) {
                dist[e->dest] = dist[u] + e->weight;
                prev[e->dest] = u;
            }
        }
    }
}

void printPath(const Graph *g, const int prev[MAX_VERTICES], int dest) {
    if (prev[dest] == -1) {
        printf("%s", g->names[dest]);
        return;
    }
    printPath(g, prev, prev[dest]);
    printf(" -> %s", g->names[dest]);
}

/* Union-Find para o Kruskal */
static int find(int parent[], int x) {
    while (parent[x] != x) x = parent[x];
    return x;
}

static void unite(int parent[], int a, int b) {
    parent[find(parent, a)] = find(parent, b);
}

int kruskalMST(const Graph *g, EdgeRecord mst[MAX_VERTICES], int *totalWeight) {
    EdgeRecord edges[MAX_VERTICES * MAX_VERTICES];
    int numEdges = 0;

    for (int u = 0; u < g->numVertices; u++) {
        for (Edge *e = g->adjList[u]; e; e = e->next) {
            if (u < e->dest) {
                edges[numEdges].src = u;
                edges[numEdges].dest = e->dest;
                edges[numEdges].weight = e->weight;
                numEdges++;
            }
        }
    }

    /* ordena arestas por peso (insertion sort: numEdges e' pequeno) */
    for (int i = 1; i < numEdges; i++) {
        EdgeRecord key = edges[i];
        int j = i - 1;
        while (j >= 0 && edges[j].weight > key.weight) {
            edges[j + 1] = edges[j];
            j--;
        }
        edges[j + 1] = key;
    }

    int parent[MAX_VERTICES];
    for (int i = 0; i < g->numVertices; i++) parent[i] = i;

    int mstCount = 0;
    *totalWeight = 0;
    for (int i = 0; i < numEdges && mstCount < g->numVertices - 1; i++) {
        int ra = find(parent, edges[i].src);
        int rb = find(parent, edges[i].dest);
        if (ra != rb) {
            unite(parent, ra, rb);
            mst[mstCount++] = edges[i];
            *totalWeight += edges[i].weight;
        }
    }
    return mstCount;
}
