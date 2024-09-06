#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 1000005;

ll N, A, B, C, X[MAXN], S[MAXN], DP[MAXN];

struct line
{
    ll a, b;
    ll get(ll x)
    {
        return a * x + b;
    }
};

double cross(line a, line b)
{
    return (double)(b.b - a.b) / (a.a - b.a);
}

int main()
{
    cin >> N;
    cin >> A >> B >> C;
    for(ll i = 1; i <= N; i++) {
        cin >> X[i];
        S[i] = S[i-1] + X[i];
    }

    vector<line> v;
    v.push_back(line{0, 0});
    ll lst = 0;
    for(ll n = 1; n <= N; n++) {
        while(lst + 1 < v.size() && cross(v[lst], v[lst+1]) < S[n]) lst++;

        DP[n] = v[lst].get(S[n]) + A*S[n]*S[n]+B*S[n]+C;

        line new_line;
        new_line.a = -2*A*S[n];
        new_line.b = DP[n] + A*S[n]*S[n] - B*S[n];

        while(v.size() >= 2 && cross(v.end()[-1], v.end()[-2]) > cross(v.end()[-1], new_line))
            v.pop_back();

        v.push_back(new_line);
    }

    cout << DP[N];
}