#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class merge_sort
{
public:
    vector<ll> mergesort(vector<ll> &v)
    {
        int n = v.size();
        if (n <= 1)
            return v;
        int middle = n / 2;
        vector<ll> left, right;
        for (int i = 0; i < middle; i++)
            left.push_back(v[i]);
        for (int i = middle; i < n; i++)
            right.push_back(v[i]);
        left = mergesort(left);
        right = mergesort(right);
        return merge(left, right);
    }

    vector<ll> merge(vector<ll> &l, vector<ll> &r)
    {
        vector<ll> merged;
        int li = 0, ri = 0, ls = l.size(), rs = r.size();
        while (li < ls && ri < rs)
        {
            if (l[li] < r[ri])
            {
                merged.push_back(l[li]);
                li++;
            }
            else
            {
                merged.push_back(r[ri]);
                ri++;
            }
        }
        if (ri < rs )
        {
            for (int i = ri; i < rs; i++)
                merged.push_back(r[i]);
        }
        else if (li < ls )
        {
            for (int i = li; i < ls; i++)
                merged.push_back(l[i]);
        }
        return merged;
    }
};


int main()
{
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<ll> v(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++)
        cin >> v[i];

    merge_sort ms;
    vector<ll> result = ms.mergesort(v);

    cout << "Sorted: ";
    for (ll x : result)
        cout << x << " ";
    cout << "\n";

    return 0;
}