#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 50505;

bool use[MAXN], coupon[MAXN];
int N, K;
ll M, P[MAXN], C[MAXN];

int main()
{
    cin >> N >> K >> M;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> p, c, onlyc, cp;
    for(int i = 1; i <= N; i++) {
        cin >> P[i] >> C[i];
        p.emplace(P[i], i);
        c.emplace(C[i], i);
    }

    ll cost = 0;
    for(int i = 1; i <= N; i++) {
        while(p.size() && use[p.top().second]) p.pop();
        while(c.size() && use[c.top().second]) c.pop();
        while(onlyc.size() && !coupon[onlyc.top().second]) onlyc.pop();
        while(cp.size() && !coupon[cp.top().second]) cp.pop();
        if(K) {
            K--;
            auto [_, id] = c.top(); c.pop();
            cost += C[id];
            use[id] = true;
            coupon[id] = true;
            onlyc.emplace(-C[id], id);
            cp.emplace(-C[id]+P[id], id);
        } else {
            ll op1 = c.top().first + onlyc.top().first + p.top().first;
            ll op2 = c.top().first + cp.top().first;
            ll op3 = p.top().first;
            if(op1 == min({op1, op2, op3})) {
                cost += op1;
                auto [_, id] = onlyc.top(); onlyc.pop();
                use[id] = false;
                coupon[id] = false;
                p.emplace(P[id], id);
                c.emplace(C[id], id);

                tie(_, id) = c.top(); c.pop();
                use[id] = true;
                coupon[id] = true;
                onlyc.emplace(-C[id], id);
                cp.emplace(-C[id]+P[id], id);

                tie(_, id) = p.top(); p.pop();
                use[id] = true;
            } else if(op2 == min({op1, op2, op3})) {
                cost += op2;
                auto [_, id] = cp.top();
                coupon[id] = false;

                tie(_, id) = c.top();
                use[id] = true;
                coupon[id] = true;
                onlyc.emplace(-C[id], id);
                cp.emplace(-C[id]+P[id], id);
            } else {
                cost += op3;
                auto [_, id] = p.top();
                use[id] = true;
            }
        }
        if(cost > M) {
            cout << i-1 << "\n";
            return 0;
        }
    }
    cout << N << "\n";
}