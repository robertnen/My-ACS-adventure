#include <bits/stdc++.h>

typedef std::vector<std::vector<int>> graph;

const long MOD = 1'000'000'007;

//* check if x -> y exists, else return -1
int findVal(const graph& g, int x, int y) {
    for (auto& idx : g[x])
        if (idx == y) return idx;

    return -1;
}

int main() {
    std::ifstream fin("numarare.in");
    std::ofstream fout("numarare.out");

    int n, m, x, y, edge_num = 0;

    //* read input
    fin >> n >> m;

    //? g - first graph, gc - common graph
    graph g(n + 1), gc(n + 1);

    for (int i = 0; i < m; i++) {
        fin >> x >> y;
        g[x].push_back(y);
    }

    for (int i = 0; i < m; i++) {
        fin >> x >> y;
        if (findVal(g, x, y) != -1) {
            gc[x].push_back(y);
            edge_num++;
        }
    }

    //* solve problem
    std::vector<long> dp(n + 1, 0);

    //? from 1 to 1 there is always only one path
    dp[1] = 1;

    for (int i = 1; i <= n; i++)
        for (auto& idx : gc[i])
            dp[idx] = (dp[i] + dp[idx]) % MOD;

    //* output
    fout << dp[n];

    return 0;
}
