vector<vector<int>> parent(200010, vector<int>(21, -1));
vector<vector<int>> adj(200010);
vector<int> level(200010);
vector<int> depth(200010);

void dfs(int node, int par, int d)
{
    parent[node][0] = par;
    level[node] = d;

    for (int i = 0; i < adj[node].size(); i++)
    {
        int child = adj[node][i];
        if (child == par)
            continue;
        dfs(child, node, d + 1);
        depth[node] = max(depth[node], 1 + depth[child]);
    }
}

void binaryLift(int n)
{
    dfs(1, -1, 0); // Assuming 1 as the root node

    for (int k = 1; k < 21; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            if (parent[i][k - 1] != -1)
                parent[i][k] = parent[parent[i][k - 1]][k - 1];
        }
    }
}

int kth_par(int u, int k)
{
    if (k == 0)
        return u;

    int v = log2(k);
    return kth_par(parent[u][v], k - (1 << v));
}

int LCA(int u, int v)
{
    if (level[u] > level[v])
        swap(u, v);

    int diff = level[v] - level[u];

    v = kth_par(v, diff);

    if (u == v)
        return u;

    for (int i = 20; i >= 0; i--)
    {
        if (parent[u][i] != parent[v][i])
        {
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    return parent[u][0];
}

void build_tree(int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void clear_tree(int n)
{
    for (int i = 0; i <= n; i++)
    {
        adj[i].clear();
        for (int j = 0; j <= 21; j++)
        {
            parent[i][j] = -1;
        }
    }
    level.clear();
}

int path_dist(int u, int v)
{
    return level[u] + level[v] - 2 * level[LCA(u, v)];
}
