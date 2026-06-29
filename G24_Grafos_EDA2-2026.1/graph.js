/* ===== Dados do Mapa Estelar (mesmo grafo da versao C) ===== */
const NODES = [
  { id: 0, name: "Sol",             x:  90, y: 260 },
  { id: 1, name: "Alpha Centauri",  x: 230, y: 110 },
  { id: 2, name: "Sirius",          x: 230, y: 410 },
  { id: 3, name: "Proxima",         x: 360, y: 210 },
  { id: 4, name: "Vega",            x: 390, y: 430 },
  { id: 5, name: "Kepler-90",       x: 500, y: 300 },
  { id: 6, name: "Trappist-1",      x: 570, y: 460 },
  { id: 7, name: "Orion Outpost",   x: 630, y: 250 },
  { id: 8, name: "Nova Prime",      x: 700, y: 140 },
  { id: 9, name: "Andromeda Gate",  x: 730, y: 390 },
];

const EDGES = [
  [0, 1, 4], [0, 2, 8], [1, 3, 3], [1, 4, 10], [2, 4, 6],
  [2, 3, 5], [3, 5, 5], [4, 5, 2], [4, 6, 7], [5, 7, 4],
  [6, 7, 3], [7, 8, 6], [6, 9, 9], [8, 9, 2],
];

function buildAdjList() {
  const adj = NODES.map(() => []);
  for (const [a, b, w] of EDGES) {
    adj[a].push({ to: b, w });
    adj[b].push({ to: a, w });
  }
  return adj;
}

function edgeKey(a, b) {
  return a < b ? `${a}-${b}` : `${b}-${a}`;
}

/* ===== Algoritmos: cada um devolve uma lista de "passos" para animacao ===== */

function runBFS(start) {
  const adj = buildAdjList();
  const visited = new Array(NODES.length).fill(false);
  const steps = [];
  const queue = [start];
  visited[start] = true;
  steps.push({ type: "visit", node: start, log: `Visita inicial: ${NODES[start].name}` });

  while (queue.length) {
    const u = queue.shift();
    for (const { to } of adj[u]) {
      if (!visited[to]) {
        visited[to] = true;
        queue.push(to);
        steps.push({ type: "edge", a: u, b: to, log: `INSERT na fila: ${NODES[to].name} (via ${NODES[u].name})` });
        steps.push({ type: "visit", node: to, log: `Visita: ${NODES[to].name}` });
      }
    }
  }
  return steps;
}

function runDFS(start) {
  const adj = buildAdjList();
  const visited = new Array(NODES.length).fill(false);
  const steps = [];

  function visit(u) {
    visited[u] = true;
    steps.push({ type: "visit", node: u, log: `Visita: ${NODES[u].name}` });
    for (const { to } of adj[u]) {
      if (!visited[to]) {
        steps.push({ type: "edge", a: u, b: to, log: `Aprofunda: ${NODES[u].name} -> ${NODES[to].name}` });
        visit(to);
      }
    }
  }
  visit(start);
  return steps;
}

function runDijkstra(start, target) {
  const adj = buildAdjList();
  const dist = new Array(NODES.length).fill(Infinity);
  const prev = new Array(NODES.length).fill(-1);
  const visited = new Array(NODES.length).fill(false);
  const steps = [];

  dist[start] = 0;
  for (let count = 0; count < NODES.length; count++) {
    let u = -1, best = Infinity;
    for (let i = 0; i < NODES.length; i++) {
      if (!visited[i] && dist[i] < best) { best = dist[i]; u = i; }
    }
    if (u === -1) break;
    visited[u] = true;
    steps.push({ type: "visit", node: u, log: `Fecha menor custo: ${NODES[u].name} (custo ${dist[u]})` });

    for (const { to, w } of adj[u]) {
      if (!visited[to] && dist[u] + w < dist[to]) {
        dist[to] = dist[u] + w;
        prev[to] = u;
        steps.push({ type: "edge", a: u, b: to, log: `Relaxa aresta: ${NODES[u].name} -> ${NODES[to].name} (novo custo ${dist[to]})` });
      }
    }
  }

  const path = [];
  let cur = target;
  while (cur !== -1) { path.unshift(cur); cur = prev[cur]; }

  if (dist[target] === Infinity) {
    steps.push({ type: "info", log: "Nenhuma rota encontrada." });
    return { steps, dist: null, path: [] };
  }

  for (let i = 0; i < path.length - 1; i++) {
    steps.push({ type: "path", a: path[i], b: path[i + 1], log: `Rota final: ${NODES[path[i]].name} -> ${NODES[path[i + 1]].name}` });
  }
  steps.push({ type: "info", log: `Custo total: ${dist[target]}` });

  return { steps, dist: dist[target], path };
}

function runKruskal() {
  const sorted = [...EDGES].sort((e1, e2) => e1[2] - e2[2]);
  const parent = NODES.map((_, i) => i);
  const steps = [];
  let total = 0;
  let count = 0;

  function find(x) { while (parent[x] !== x) x = parent[x]; return x; }

  for (const [a, b, w] of sorted) {
    const ra = find(a), rb = find(b);
    if (ra !== rb) {
      parent[ra] = rb;
      total += w;
      count++;
      steps.push({ type: "path", a, b, log: `Adiciona hyperlane: ${NODES[a].name} <-> ${NODES[b].name} (custo ${w})` });
    } else {
      steps.push({ type: "skip", a, b, log: `Descarta (gera ciclo): ${NODES[a].name} <-> ${NODES[b].name}` });
    }
    if (count === NODES.length - 1) break;
  }
  steps.push({ type: "info", log: `Custo total da rede minima: ${total}` });
  return steps;
}
