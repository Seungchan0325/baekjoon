#include <bits/stdc++.h>

using namespace std;

int n, m;

int main()
{
    cin >> n >> m;
    vector<pair<int, int>> bottles(n);

    int sum_solute = 0, sum_amount = 0;
    for(auto& [solution, amount] : bottles)
    {
        cin >> solution >> amount;
        sum_solute += solution * amount;
        sum_amount += amount;
    }
    sum_amount *= 100;
    sort(bottles.begin(), bottles.end());

    int ans = 0;
    if(sum_amount * m < 100 * sum_solute)
    {
        int i = n - 1;
        while((sum_amount - 100 * bottles[i].second) * m < 100 * (sum_solute - bottles[i].first * bottles[i].second))
        {
            sum_amount -= 100 * bottles[i].second;
            sum_solute -= bottles[i].first * bottles[i].second;
            i--;
        }
        sum_amount -= 100 * bottles[i].second;
        sum_solute -= bottles[i].first * bottles[i].second;

        int lo = -1, hi = 100 * bottles[i].second;
        while(lo + 1 < hi)
        {
            int mid = (lo + hi) / 2;
            if((sum_amount + mid) * m > 100 * (sum_solute + bottles[i].first * mid / 100.0f))
                lo = mid;
            else
                hi = mid;
        }
        sum_amount += hi;
    }
    else if(sum_amount * m > 100 * sum_solute)
    {

        int i = 0;
        while((sum_amount - 100 * bottles[i].second) * m > 100 * (sum_solute - bottles[i].first * bottles[i].second))
        {
            sum_amount -= 100 * bottles[i].second;
            sum_solute -= bottles[i].first * bottles[i].second;
            i++;
        }
        sum_amount -= 100 * bottles[i].second;
        sum_solute -= bottles[i].first * bottles[i].second;

        int lo = -1, hi = 100 * bottles[i].second;
        while(lo + 1 < hi)
        {
            int mid = (lo + hi) / 2;
            if((sum_amount + mid) * m < 100 * (sum_solute + bottles[i].first * mid / 100.0f))
                lo = mid;
            else
                hi = mid;
        }
        sum_amount += hi;
    }

    cout << (double)sum_amount / 100;
}