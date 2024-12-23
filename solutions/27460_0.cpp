#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;

int n;
bool vst[MAXN];
vector<int> graph[MAXN];

bool chk(vector<int> a)
{
    static int cnt = 0;
    assert(++cnt <= 9);
    assert(!a.empty());
    cout << "? " << a.size() << " ";
    for(auto i : a) cout << i << " ";
    cout << "\n";
    cout.flush();
    string ans;
    cin >> ans;
    if(ans == "YES") return true;
    else return false;
}

int main()
{
    cin >> n;
    for(int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    sort(order.begin(), order.end(), [](int i, int j)
    {
        return graph[i].size() < graph[j].size();
    });

    int lo = -1;
    int hi = n-1;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        vector<int> a;
        if(mid == 0) {
            for(int i = 1; i < n; i++) {
                if(graph[order[i]].size() != 1) break;
                a.push_back(order[i]);
            }
            if(chk(a) == false) hi = mid;
            else lo = mid;
            continue;
        }
        for(int i = 0; i <= mid; i++) a.push_back(order[i]);
        if(chk(a)) hi = mid;
        else lo = mid;
    }

    cout << "! " << order[hi];
}