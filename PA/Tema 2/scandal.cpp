#include <bits/stdc++.h>

typedef std::vector<int> iVec;
typedef std::vector<bool> bVec;
typedef std::vector<std::vector<int>> graph;

void dfsTopo(int idx, iVec& q, bVec& isVisited, graph& g, graph& topo) {
    isVisited[idx] = true;
    for (auto id : g[idx])
            if (!isVisited[id]) dfsTopo(id, q, isVisited, g, topo);

    q.push_back(idx);
}

void dfsSetLevel(int idx, int& level, iVec& levels, graph& topo) {
    levels[idx] = level++;
    for (auto id : topo[idx])
        if (!levels[id]) dfsSetLevel(id, level, levels, topo);
}

int main() {
    std::ifstream fin("scandal.in");
    std::ofstream fout("scandal.out");

    int n, m, x, y, rx, ry, level = 1;
    char c;

    fin >> n >> m;

    n = 2 * n + 1;

    //* initialize with 2 * n + 1 elements
    iVec q, levels(n), ans;
    bVec isVisited(n, false);
    graph g(n), topo(n);

    n = (n - 1) / 2;

    for (int i = 0; i < m ; i++) {
        fin >> x >> y >> c;

        switch (c) {
            case '0': break;                  //* x | | y
            case '1': y += n; break;          //* x --> y
            case '2': x += n; break;          //* x <-- y
            case '3': x += n; y += n; break;  //* x  ^  y
            default: std::cerr << "Wrong rule.\n"; exit(true);
        }

        //* rx and ry are the the "opposite" nodes
        rx = x > n ? x - n : x + n;
        ry = y > n ? y - n : y + n;

        g[rx].push_back(y);
        g[ry].push_back(x);

        //* order of nodes normally
        topo[y].push_back(rx);
        topo[x].push_back(ry);
    }

    //* topo sort
    for (int i = 1; i < 2 * n + 1; i++)
        if (!isVisited[i]) dfsTopo(i, q, isVisited, g, topo);

    //* dfsTopo add in q from end to start, so we reverse it to set levels
    std::reverse(q.begin(), q.end());

    for (auto idx : q)
        if (!levels[idx]) dfsSetLevel(idx, level, levels, topo);

    for (int i = 1; i <= n ; i++)
        if (levels[i + n] < levels[i]) ans.push_back(i);

    //* show output
    fout << ans.size();
    for (auto idx : ans) fout << '\n' << idx;
}
