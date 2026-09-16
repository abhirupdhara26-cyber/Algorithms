#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class Quick_sort
{
public:
    int partition(vector<ll> &v, int start, int end)
    {
        int piv = end;
        int j = start - 1;
        for (int i = start; i < end; i++)
        {
            if (v[i] < v[piv])
                swap(v[i], v[++j]);
        }
        swap(v[piv], v[++j]);
        piv = j;
        return piv;
    }
    vector<ll> quicksort(vector<ll> &v, int start, int end)
    {
        if (start >= end)
            return v;
        int piv = partition(v, start, end);
        quicksort(v, start, piv - 1);
        quicksort(v, piv + 1, end);

        return v;
    }
};