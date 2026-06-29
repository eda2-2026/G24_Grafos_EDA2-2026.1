#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define COR_RESET   "\x1b[0m"
#define COR_CIANO   "\x1b[36m"
#define COR_AMARELO "\x1b[33m"
#define COR_VERDE   "\x1b[32m"
#define COR_MAGENTA "\x1b[35m"

static const char *SISTEMAS[MAX_VERTICES] = {
    "Sol",            "Alpha Centauri", "Sirius",        "Proxima",
    "Vega",           "Kepler-90",      "Trappist-1",    "Orion Outpost",
    "Nova Prime",     "Andromeda Gate"
};

static Graph *construirMapaEstelar(void) {
    Graph *g = createGraph(MAX_VERTICES);
    for (int i = 0; i < MAX_VERTICES; i++) setVertexName(g, i, SISTEMAS[i]);

    addEdge(g, 0, 1, 4);   /* Sol - Alpha Centauri */
    addEdge(g, 0, 2, 8);   /* Sol - Sirius */
    addEdge(g, 1, 3, 3);   /* Alpha Centauri - Proxima */
    addEdge(g, 1, 4, 10);  /* Alpha Centauri - Vega */
    addEdge(g, 2, 4, 6);   /* Sirius - Vega */
    addEdge(g, 2, 3, 5);   /* Sirius - Proxima */
    addEdge(g, 3, 5, 5);   /* Proxima - Kepler-90 */
    addEdge(g, 4, 5, 2);   /* Vega - Kepler-90 */
    addEdge(g, 4, 6, 7);   /* Vega - Trappist-1 */
    addEdge(g, 5, 7, 4);   /* Kepler-90 - Orion Outpost */
    addEdge(g, 6, 7, 3);   /* Trappist-1 - Orion Outpost */
    addEdge(g, 7, 8, 6);   /* Orion Outpost - Nova Prime */
    addEdge(g, 6, 9, 9);   /* Trappist-1 - Andromeda Gate */
    addEdge(g, 8, 9, 2);   /* Nova Prime - Andromeda Gate */

    return g;
}

static void mostrarMapa(const Graph *g) {
    printf(COR_CIANO "\n=== Mapa de Hyperlanes Conhecidas ===\n" COR_RESET);
    printGraph(g);
}

static int lerSistema(const char *prompt) {
    printf("%s (0-%d): ", prompt, MAX_VERTICES - 1);
    int v;
    if (scanf("%d", &v) != 1) return -1;
    if (v < 0 || v >= MAX_VERTICES) return -1;
    return v;
}

static void executarBusca(const Graph *g, int usarBFS) {
    int origem = lerSistema("Sistema de partida");
    if (origem < 0) { printf("Sistema invalido.\n"); return; }

    int order[MAX_VERTICES];
    int count = usarBFS ? bfs(g, origem, order) : dfs(g, origem, order);

    printf(COR_VERDE "\nOrdem de exploracao (%s) a partir de %s:\n" COR_RESET,
           usarBFS ? "BFS" : "DFS", g->names[origem]);
    for (int i = 0; i < count; i++) {
        printf("  %d. %s\n", i + 1, g->names[order[i]]);
    }
}

static void executarDijkstra(const Graph *g) {
    int origem = lerSistema("Sistema de partida");
    int destino = lerSistema("Sistema de destino");
    if (origem < 0 || destino < 0) { printf("Sistema invalido.\n"); return; }

    int dist[MAX_VERTICES], prev[MAX_VERTICES];
    dijkstra(g, origem, dist, prev);

    if (dist[destino] >= INF) {
        printf(COR_AMARELO "\nNenhuma rota encontrada entre os sistemas.\n" COR_RESET);
        return;
    }

    printf(COR_VERDE "\nRota mais economica (Dijkstra): " COR_RESET);
    printPath(g, prev, destino);
    printf("\nCusto total de combustivel: %d\n", dist[destino]);
}

static void executarKruskal(const Graph *g) {
    EdgeRecord mst[MAX_VERTICES];
    int totalWeight = 0;
    int count = kruskalMST(g, mst, &totalWeight);

    printf(COR_MAGENTA "\n=== Rede Minima de Hyperlanes (Kruskal/MST) ===\n" COR_RESET);
    for (int i = 0; i < count; i++) {
        printf("  %s <-> %s  (custo %d)\n",
               g->names[mst[i].src], g->names[mst[i].dest], mst[i].weight);
    }
    printf("Custo total de construcao da rede: %d\n", totalWeight);
}

int main(void) {
    Graph *g = construirMapaEstelar();
    int opcao;

    printf(COR_CIANO "\n*** ROTA ESTELAR — Navegando o Grafo da Galaxia ***\n" COR_RESET);

    do {
        printf("\n----------------------------------\n");
        printf("1) Mostrar mapa estelar\n");
        printf("2) Explorar com BFS\n");
        printf("3) Explorar com DFS\n");
        printf("4) Calcular rota mais economica (Dijkstra)\n");
        printf("5) Construir rede minima de hyperlanes (Kruskal/MST)\n");
        printf("0) Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &opcao) != 1) break;

        switch (opcao) {
            case 1: mostrarMapa(g); break;
            case 2: executarBusca(g, 1); break;
            case 3: executarBusca(g, 0); break;
            case 4: executarDijkstra(g); break;
            case 5: executarKruskal(g); break;
            case 0: printf("Encerrando viagem...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    freeGraph(g);
    return 0;
}
