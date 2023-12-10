public class Graph extends MyList {
    private MyList[] g;
    private boolean[] isVisited;
    private int size;

    public Graph(int n) {
        g = new MyList[n + 1];
        for(int i = 0; i <= n; i++)
            g[i] = new MyList();
        isVisited = new boolean[n + 1];
        size = n;
    }

    public void add(int x, int y) {
        g[x].add(y);
    }

    public void dfs(int start) {
        System.out.print(start + " ");
        isVisited[start] = true;

        for(int i = 0; i < g[start].size(); i++)
            if(!isVisited[(int)g[start].get(i)])
                dfs((int)g[start].get(i));
    }

    @Override
    public String toString() {
        String result = "";

        for(int i = 1; i <= size; i++) {
            result += i + ":";
            for(int j = 0; j < g[i].size(); j++)
                result += " " + g[i].get(j);

            result += "\n";
        }

        return result;
    }
}
