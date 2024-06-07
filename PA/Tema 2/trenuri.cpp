#include <bits/stdc++.h>

typedef std::vector<std::vector<int>> graph;

//* searches in dictionary for the id of the city
int findId(const std::unordered_map<std::string, int>& dict,
            std::string city) {
    auto name = dict.find(city);

    return name != dict.end() ? name->second : -1;
}

void topoSort(const graph& g, std::stack<int>& s,
                std::vector<bool>& isVisited, int idx) {
    isVisited[idx] = true;

    for (auto& x : g[idx])
        if (!isVisited[x])
            topoSort(g, s, isVisited, x);

    s.push(idx);
}

int main() {
    std::ifstream fin("trenuri.in");
    std::ofstream fout("trenuri.out");

    std::unordered_map<std::string, int> dict;
    std::string xs, ys;
    int n = 2, m, idx;

    fin >> xs >> ys;
    fin >> m;

    dict[xs] = 1;  //? source
    dict[ys] = 2;  //? destination

    //* I can have maximum 2 * (number of routes) cities
    graph g(2 * m + 1);

    for (int i = 0; i < m; i++) {
        fin >> xs >> ys;

        int pos1 = findId(dict, xs), pos2 = findId(dict, ys);

        //* first time source city appears
        if (pos1 == -1) {
            dict[xs] = ++n;
            pos1 = n;
        }

        //* first time destination city appears
        if (pos2 == -1) {
            dict[ys] = ++n;
            pos2 = n;
        }

        g[pos1].push_back(pos2);
    }

    std::stack<int> s;
    std::vector<bool> isVisited(n + 1, false);

    //* distances using dfs for topological sort
    for (idx = 1; idx <= n; idx++)
        if (!isVisited[idx])
            topoSort(g, s, isVisited, idx);

    std::vector<int> levels(n + 1, -1);

    levels[1] = 0;  //? source

    while (!s.empty()) {
        idx = s.top();
        s.pop();

        if (levels[idx] != -1)
            for (auto& x : g[idx])
                if (levels[x] < levels[idx] + 1) levels[x] = levels[idx] + 1;
    }

    //* dists knows the number of edges of the path, so edges_num + 1 cities
    fout << levels[2] + 1;

    return 0;
}
