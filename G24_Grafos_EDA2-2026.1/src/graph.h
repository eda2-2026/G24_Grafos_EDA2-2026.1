#ifndef GRAPH_H
#define GRAPH_H

#define MAX_VERTICES 10
#define INF 999999

/* Lista de adjacencia: cada vertice tem uma lista encadeada de arestas */
typedef struct Edge {
    int dest;
    int weight;
    struct Edge *next;
} Edge;

typedef struct Graph {
    int numVertices;
    Edge *adjList[MAX_VERTICES];
    char *names[MAX_VERTICES];
} Graph;

typedef struct {
    int src;
    int dest;
    int weight;
} EdgeRecord;

Graph *createGraph(int vertices);
void setVertexName(Graph *g, int v, const char *name);
void addEdge(Graph *g, int src, int dest, int weight);
void freeGraph(Graph *g);
void printGraph(const Graph *g);

/* Algoritmos de busca: preenchem 'order' com a ordem de visita, retornam o total visitado */
int bfs(const Graph *g, int start, int *order);
int dfs(const Graph *g, int start, int *order);

/* Dijkstra: preenche dist[] (custo minimo) e prev[] (predecessor) a partir de 'start' */
void dijkstra(const Graph *g, int start, int dist[MAX_VERTICES], int prev[MAX_VERTICES]);
void printPath(const Graph *g, const int prev[MAX_VERTICES], int dest);

/* Kruskal (MST via Union-Find): preenche mst[] com as arestas escolhidas, retorna a quantidade */
int kruskalMST(const Graph *g, EdgeRecord mst[MAX_VERTICES], int *totalWeight);

#endif
