
class Disjoint_Set_Union
{
public:
    vector<int> size, rank, parent, edges;

    Disjoint_Set_Union(int n)
    {
        size.resize(n + 1), rank.resize(n + 1), parent.resize(n + 1), edges.resize(n + 1);
        for (int i = 0; i <= n; i++)
            size[i] = 1, rank[i] = 0, parent[i] = i, edges[i] = 0;
    }

    int find_parent(int u)
    {

        if (parent[u] == u)
            return u;

        return parent[u] = find_parent(parent[u]); // path compression;
    }

    void unioin_by_rank(int u, int v)
    {
        int pu = find_parent(u);
        int pv = find_parent(v);

        if (pu == pv)
            return;

        if (rank[pu] < rank[pv])
            parent[pu] = pv;
        else if (rank[pu] > rank[pv])
            parent[pv] = pu;
        else
            ++rank[pu], parent[pv] = pu;
    }

    void unioin_by_size(int u, int v)
    {
        int pu = find_parent(u);
        int pv = find_parent(v);

        ++edges[pu];

        if (pu == pv)
            return;

        if (size[pu] < size[pv])
            size[pv] += size[pu], edges[pv] += edges[pu], parent[pu] = pv;
        else
            size[pu] += size[pv], edges[pu] += edges[pv], parent[pv] = pu;
    }
};
