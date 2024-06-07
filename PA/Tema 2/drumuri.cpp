#include <bits/stdc++.h>

typedef std::pair<int, int> edge;
typedef std::pair<long, int> weight;
typedef std::vector<std::vector<edge>> graph;

std::vector<long> dijkstra(graph& g, int src, int n) {
    std::priority_queue<weight, std::vector<weight>, std::greater<>> pq;
    std::vector<long> dists(n + 1, LONG_MAX);
    int u, v, w;

    dists[src] = 0;
    pq.emplace(0, src);

    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();

        if (w > dists[u]) continue;

        for (auto [v, wv] : g[u]) {
            long total = wv + dists[u];

            if (total < dists[v]) {
                dists[v] = total;
                pq.emplace(dists[v], v);
            }
        }
    }

    return dists;
}

int main() {
    std::ifstream fin("drumuri.in");
    std::ofstream fout("drumuri.out");

    int n, m, x, y, z, w;
    long ans = LONG_MAX;

    fin >> n >> m;

    //? g - graph, r - reversed graph (if x -> y in g, then y -> x in r)
    graph g(n + 1), r(n + 1);

    //* read the graph and the reversed graph
    for (int i = 0; i < m; i++) {
        fin >> x >> y >> w;

        g[x].push_back({y, w});
        r[y].push_back({x, w});
    }

    //* the nodes mentioned
    fin >> x >> y >> z;

    //* find shortest paths (for z with reverse the graph)
    std::vector<long> disX(dijkstra(g, x, n));
    std::vector<long> disY(dijkstra(g, y, n));
    std::vector<long> disZ(dijkstra(r, z, n));

    //* find common
    for (int v = 1; v <= n; v++)
        if (disX[v] != LONG_MAX && disY[v] != LONG_MAX && disZ[v] != LONG_MAX) {
            long _ = disX[v] + disY[v] + disZ[v];
            ans = std::min(ans, _);
        }

    fout << ans;

    return 0;
}
