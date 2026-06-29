# 🚀 Rota Estelar — Grafos em Ação

Simulador de navegação espacial que demonstra **Grafos Ponderados** na prática, disponível em **duas versões**: programa de terminal (C) e site interativo (navegador).

Desenvolvido para a disciplina de **Estruturas de Dados e Algoritmos 2 (EDA2) – 2026.1**.

---

## Alunos

<div align="center">
<table>
  <tr>
    <td align="center"><a href="https://github.com/alvesingrid"><img style="border-radius: 50%;" src="https://github.com/alvesingrid.png" width="120" alt=""/><br/><sub><b>Ingrid Alves</b></sub></a></td>
    <td align="center"><a href="https://github.com/Ericcs10"><img style="border-radius: 50%;" src="https://github.com/Ericcs10.png" width="120" alt=""/><br/><sub><b>Eric Camargo</b></sub></a></td>
  </tr>
</table>
</div>

| Matrícula  | Nome                      |
|:-----------|:--------------------------|
| 202045348  | **Ingrid Alves Rocha**    |
| 202016168  | **Eric Camargo da Silva** |

---

## 🛰️ Sobre o Projeto

**Rota Estelar** simula a navegação de uma nave por uma galáxia de **10 sistemas estelares** conectados por **hyperlanes** (rotas com custo de combustível). O jogador/usuário assume o papel de comandante e usa algoritmos clássicos de grafos para tomar decisões de navegação:

| Ação                                          | Algoritmo de Grafo                        |
|-----------------------------------------------|--------------------------------------------|
| Explorar sistemas vizinhos em ondas           | **BFS** (Busca em Largura)                 |
| Explorar mergulhando o mais fundo possível    | **DFS** (Busca em Profundidade)            |
| Encontrar a rota mais econômica entre 2 pontos| **Dijkstra** (caminho mínimo)              |
| Construir a rede de hyperlanes mais barata    | **Kruskal** (Árvore Geradora Mínima / MST) |

O mapa estelar é representado como um **grafo ponderado e não-direcionado**: cada sistema é um vértice e cada hyperlane é uma aresta cujo peso é o custo de combustível para percorrê-la.

---

## 🌌 O Mapa Estelar

```
        Alpha Centauri
        /      |      \
      4/       3\       \10
      /          \        \
   Sol            Proxima — Sirius
      \8            \  5       /6
       \              \5      /
        Sirius —6— Vega —2— Kepler-90
                     |7         |4
               Trappist-1 —3— Orion Outpost
                  |9              |6
            Andromeda Gate —2— Nova Prime
```

10 sistemas estelares, 14 hyperlanes — os pesos representam o custo de combustível (mesmos dados nas versões C e Web).

### Complexidade dos algoritmos implementados

| Algoritmo | Pior caso              | Estrutura auxiliar     |
|-----------|-------------------------|-------------------------|
| BFS       | $O(V + E)$               | Fila                    |
| DFS       | $O(V + E)$               | Recursão / Pilha        |
| Dijkstra  | $O(V^2)$ (versão com vetor de distâncias) | Vetor `dist[]` / `prev[]` |
| Kruskal   | $O(E \log E)$            | Union-Find (Disjoint Set) |

### Detalhes de Implementação

- **Grafo em lista de adjacência**: cada vértice mantém uma lista encadeada de arestas (`Edge`), com destino e peso
- **BFS/DFS**: produzem a ordem de visita dos sistemas a partir de um ponto de partida
- **Dijkstra**: relaxamento de arestas a partir do vértice de menor distância ainda não visitado, reconstruindo o caminho via vetor de predecessores (`prev[]`)
- **Kruskal**: ordena todas as arestas por peso e usa **Union-Find** (`find`/`unite`) para evitar ciclos, construindo a Árvore Geradora Mínima

---

## 🖥️ Versão Web (Recomendada)

Site completo no navegador com **visualização ao vivo do grafo em SVG** e animação passo a passo dos algoritmos.

### Como abrir

```bash
# Basta abrir o arquivo no navegador:
xdg-open index.html
# ou arraste o arquivo index.html para o navegador
```

### Interface

```
┌───────────────────┬─────────────────────────────┬───────────────────────┐
│ Painel de Comando  │      Mapa Estelar (SVG)      │   Log de Operações   │
│                    │                              │                       │
│ Algoritmo:         │        Alpha Centauri         │ ▶ Visita: Sol         │
│ [Dijkstra ▾]       │       /●\         ●           │ ▶ Relaxa: Sol->Alpha  │
│                    │      /   \       Nova Prime   │ ▶ Fecha: Alpha (4)    │
│ Partida: [Sol ▾]   │   ●Sol    ●Proxima    ●        │ ▶ Rota final: ...     │
│ Destino: [Andro ▾] │      \    /  \      Andromeda  │ Custo total: 24       │
│                    │       ●Sirius ●Kepler-90       │                       │
│ [▶ Executar]       │                                │                       │
│ [↺ Reiniciar]      │                                │                       │
└───────────────────┴─────────────────────────────┴───────────────────────┘
```

### Funcionalidades Web

- ✅ Grafo visualizado em **SVG interativo** (vértices, arestas e pesos)
- ✅ **Animação passo a passo** de BFS, DFS, Dijkstra e Kruskal, com destaque de vértices e arestas visitados
- ✅ **Log de operações** em tempo real explicando cada decisão do algoritmo
- ✅ Seleção de **sistema de partida/destino** para BFS, DFS e Dijkstra
- ✅ Exibição do **custo total** da rota (Dijkstra) ou da rede mínima (Kruskal)
- ✅ Botão de **reiniciar mapa** para limpar destaques e repetir simulações

---

## 💻 Versão Terminal (C)

### Pré-requisitos

- GCC (`gcc --version`)
- Terminal com suporte a cores ANSI (Linux/macOS/WSL)

### Compilar e executar

```bash
# Clonar o repositório
git clone https://github.com/SEU_USUARIO/G24_Grafos_EDA2-2026.1.git
cd G24_Grafos_EDA2-2026.1

# Compilar
make

# Executar
./rota-estelar

# Ou tudo de uma vez
make run

# Limpar binários
make clean
```

### Menu interativo

```
*** ROTA ESTELAR — Navegando o Grafo da Galaxia ***

1) Mostrar mapa estelar
2) Explorar com BFS
3) Explorar com DFS
4) Calcular rota mais economica (Dijkstra)
5) Construir rede minima de hyperlanes (Kruskal/MST)
0) Sair
```

---

## 🏗️ Implementação Técnica

### Representação do grafo (`graph.h` / `graph.c`)
Lista de adjacência com `MAX_VERTICES = 10`; cada vértice guarda seu nome (sistema estelar) e uma lista encadeada de arestas (`Edge`) com destino e peso. As arestas são adicionadas em ambas as direções (`addEdge`), pois o grafo é não-direcionado.

### BFS / DFS
- `bfs`: usa uma fila para visitar os sistemas em ondas, a partir de um ponto de partida
- `dfs`: usa recursão para se aprofundar no grafo antes de retroceder (backtracking)

### Dijkstra
A cada iteração, escolhe o vértice não visitado de menor distância acumulada e relaxa suas arestas, atualizando `dist[]` e `prev[]`. O caminho final é reconstruído recursivamente em `printPath`.

### Kruskal (MST)
Todas as arestas são ordenadas por peso; em seguida, cada aresta é testada com **Union-Find**: se os dois extremos já pertencem ao mesmo conjunto, a aresta é descartada (evita ciclo); caso contrário, ela entra na Árvore Geradora Mínima.

---

## 📁 Estrutura do Projeto

```
G24_Grafos_EDA2-2026.1/
├── index.html        # Site Web (abrir no navegador)
├── graph.js           # Grafo + algoritmos em JS (BFS, DFS, Dijkstra, Kruskal) e animação
├── src/
│   ├── graph.h        # Tipos e declarações do Grafo (C)
│   ├── graph.c         # Implementação completa em C (lista de adjacência, BFS, DFS, Dijkstra, Kruskal)
│   └── main.c          # Programa de navegação no terminal (C)
├── Makefile
└── README.md
```

---

## 🎬 Apresentação

<div align="center">
<a href="https://youtu.be/A9l2jmLXKHE">
  <img src="https://img.youtube.com/vi/A9l2jmLXKHE/maxresdefault.jpg" width="60%" alt="Apresentação do Projeto"/>
</a>
</div>

<font size="3"><p align="center">▶ <a href="https://youtu.be/A9l2jmLXKHE">Assistir apresentação no YouTube</a></p></font>

---

<font size="3"><p align="center">Projeto EDA2 — 2026.1 | Grupo 24<br/>
<a href="https://github.com/alvesingrid">Ingrid Alves</a> & <a href="https://github.com/Ericcs10">Eric Camargo</a></p></font>
