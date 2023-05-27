class FNWKTree
{
public:
    vector<int> fen;
    int n;
    FNWKTree(int n)
    {
        this->n = n;
        fen.resize(n + 1);
    }

    void update(int ind, int val)
    {
        if(ind==0)return;
        while (ind <= n)
        {
            fen[ind] += val;
            ind += (ind & (-ind));
        }
    }

    int sum(int ind)
    {
        int res = 0;
        while (ind > 0)
        {
            res += fen[ind];
            ind -= (ind & (-ind));
        }
        return res;
    }

    int range_sum(int l, int r)
    {
        return this->sum(r) - this->sum(l - 1);
    }

    int lb_binarylifting(int val)
    {
        int ind = 0, sum = 0;
        for (int i = 20; i >= 0; i--)
        {
            if ( ind+(1<<i)<=n && fen[ind + (1 << i)] + sum < val)
            {
                ind += (1 << i);
                sum += fen[ind];
            }
        }
        return ind + 1;
    }
};
