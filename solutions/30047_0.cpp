#include <bits/stdc++.h>

using namespace std;

int f(string::iterator& expr, string::iterator end)
{
    if(expr == end) return -1e9;
    auto c = *(expr++);
    if(c == 'x') return 0;
    if(c == 'g') return f(expr, end) + 1;
    if(c == 'f') return min(f(expr, end), f(expr, end));
}

int main()
{
    string expr;
    cin >> expr;
    auto it = expr.begin();
    int ans = f(it, expr.end());
    if(it != expr.end() || ans < 0) cout << "-1\n";
    else cout << ans;
}