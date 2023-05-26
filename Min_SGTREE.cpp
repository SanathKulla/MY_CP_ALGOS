
vector<int> arr(2e5 + 10);
class SGTree
{
    vector<int> seg;

public:
    SGTree(int n)
    {
        seg.resize(4 * n + 10);
    }

    void build(int ind, int low, int high)
    {
        if (low == high)
        {
            seg[ind] = arr[low];
            return;
        }

        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid);
        build(2 * ind + 2, mid + 1, high);
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    void point_update(int ind, int low, int high, int i, int val)
    {
        if (low == high)
        {
            seg[ind] = val;
            return;
        }
        int mid = (low + high) / 2;
        if (i <= mid)
        {
            point_update(2 * ind + 1, low, mid, i, val);
        }
        else
        {
            point_update(2 * ind + 2, mid + 1, high, i, val);
        }
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    int query(int ind, int low, int high, int l, int r)
    {

        if (l > high || r < low || low > high)
            return INT_MAX;

        if (low >= l && high <= r)
        {
            return seg[ind];
        }

        int mid = (low + high) / 2;
        return min(query(2 * ind + 1, low, mid, l, r), query(2 * ind + 2, mid + 1, high, l, r));
    }
};
