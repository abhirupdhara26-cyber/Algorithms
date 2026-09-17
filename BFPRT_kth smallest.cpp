#include <bits/stdc++.h>
using namespace std;

class BFPRT
{
public:

    int findMedian(vector<int>& a, int l, int r)
    {
        sort(a.begin() + l, a.begin() + r + 1);

        return a[l + (r - l) / 2];
    }

    int medianOfMedians(vector<int>& a, int l, int r)
    {
        int n = r - l + 1;

        if(n <= 5)
            return findMedian(a, l, r);

        vector<int> medians;

        for(int i = l; i <= r; i += 5)
        {
            int j = min(i + 4, r);

            int median = findMedian(a, i, j);

            medians.push_back(median);
        }

        return medianOfMedians(medians, 0, medians.size() - 1);
    }

    int partition(vector<int>& a, int l, int r, int pivot)
    {
        int pivotIndex = l;

        for(int i = l; i <= r; i++)
        {
            if(a[i] == pivot)
            {
                pivotIndex = i;
                break;
            }
        }

        swap(a[pivotIndex], a[r]);

        int pos = l;

        for(int i = l; i < r; i++)
        {
            if(a[i] < pivot)
            {
                swap(a[i], a[pos]);
                pos++;
            }
        }

        swap(a[pos], a[r]);

        return pos;
    }

    int select(vector<int>& a, int l, int r, int k)
    {
        if(l == r)
            return a[l];

        int pivot = medianOfMedians(a, l, r);

        int pos = partition(a, l, r, pivot);

        int rank = pos - l + 1;

        if(k == rank)
            return a[pos];

        if(k < rank)
            return select(a, l, pos - 1, k);

        return select(a, pos + 1, r, k - rank);
    }

    int kthSmallest(vector<int>& a, int k)
    {
        return select(a, 0, a.size() - 1, k);
    }
};

int main()
{
    int n;
    cin >> n;

    vector<int> a(n);

    for(int i = 0; i < n; i++)
        cin >> a[i];

    int k;
    cin >> k;

    BFPRT obj;

    cout << obj.kthSmallest(a, k) << endl;

    return 0;
}