#include <bits/stdc++.h>

using namespace std;

long long nodes[55] = {1, 1};

void build()
{
    for(int i = 2; i < 55; i++) {
        nodes[i] = nodes[i - 1] + nodes[i - 2] + 1;
    }
}

string f(int n, long long dst)
{
    if(dst == 1) return "";
    if(dst - 1 <= nodes[n - 2]) return "L" + f(n - 2, dst - 1);
    else return "R" + f(n - 1, dst - nodes[n - 2] - 1);
}

int main()
{
    build();
    int n, s, e;
    cin >> n >> s >> e;
    auto ss = f(n, s);
    auto ee = f(n, e);
    while(ss.size() && ee.size() && ss.front() == ee.front()) {
        ss.erase(ss.begin());
        ee.erase(ee.begin());
    }
    for(int i = 0; i < ss.size(); i++) cout << "U";
    cout << ee;
}