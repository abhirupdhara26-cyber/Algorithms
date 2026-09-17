#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class ClosestPair
{
public:

    struct Point
    {
        ll x, y;
    };

    double dist(Point a, Point b)
    {
        ll dx = a.x - b.x;
        ll dy = a.y - b.y;

        return sqrt((double)dx * dx + (double)dy * dy);
    }

    double bruteForce(vector<Point>& p, int left, int right)
    {
        double ans = DBL_MAX;

        for(int i = left; i <= right; i++)
        {
            for(int j = i + 1; j <= right; j++)
            {
                ans = min(ans, dist(p[i], p[j]));
            }
        }

        return ans;
    }

    double stripClosest(vector<Point>& strip, double delta)
    {
        sort(strip.begin(), strip.end(),
            [](Point a, Point b)
            {
                return a.y < b.y;
            });

        double ans = delta;
        int n = strip.size();

        for(int i = 0; i < n; i++)
        {
            for(int j = i + 1; j < n; j++)
            {
                if(strip[j].y - strip[i].y >= ans)
                    break;

                ans = min(ans, dist(strip[i], strip[j]));
            }
        }

        return ans;
    }

    double closestPair(vector<Point>& p, int left, int right)
    {
        if(right - left <= 2)
            return bruteForce(p, left, right);

        int mid = left + (right - left) / 2;

        ll midX = p[mid].x;

        double leftMin = closestPair(p, left, mid);
        double rightMin = closestPair(p, mid + 1, right);

        double delta = min(leftMin, rightMin);

        vector<Point> strip;

        for(int i = left; i <= right; i++)
        {
            if(abs(p[i].x - midX) < delta)
                strip.push_back(p[i]);
        }

        double stripMin = stripClosest(strip, delta);

        return min(delta, stripMin);
    }

    double solve(vector<Point>& p)
    {
        sort(p.begin(), p.end(),
            [](Point a, Point b)
            {
                if(a.x == b.x)
                    return a.y < b.y;

                return a.x < b.x;
            });

        return closestPair(p, 0, p.size() - 1);
    }
};

int main()
{
    int n;
    cin >> n;

    ClosestPair cp;

    vector<ClosestPair::Point> p(n);

    for(int i = 0; i < n; i++)
        cin >> p[i].x >> p[i].y;

    double ans = cp.solve(p);

    cout << fixed << setprecision(6) << ans << endl;

    return 0;
}