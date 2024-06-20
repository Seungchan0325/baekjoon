#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

using ll = long long;

ll N, M, K, L[MAXN], x, B[2], day;
multiset<ll> A, C;

bool f(ll d)
{
    ll delta = d * (K - A.size()) + B[1];
    ll b = x + delta / (B[0] + B[1]);

    if(A.size()) {
        ll a = *(--A.end()) + day + d;
        if(a >= b) return false;
    }

    if(C.size()) {
        ll c = *C.begin();
        b++;
        if(c <= b) return false;
    }

    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(ll i = 0; i < N; i++) cin >> L[i];
    cin >> M >> K;

    sort(L, L + N);

    for(ll i = 0; i < K - 1; i++) A.insert(L[i]);
    for(ll i = K; i < N; i++) C.insert(L[i]);

    x = L[K-1];
    B[0] = 1;
    while(A.size() && *(--A.end()) == x) {
        A.erase(--A.end());
        B[0]++;
    }

    while(C.size() && *C.begin() <= x + 1) {
        B[*C.begin() - x]++;
        C.erase(C.begin());
    }

    while(day < M) {
        ll lo = -1;
        ll hi = 1e9;
        while(lo + 1 < hi) {
            ll mid = (lo + hi) / 2;
            if(f(mid)) lo = mid;
            else hi = mid;
        }

        if(day + hi >= M) {
            hi = M - day;
        }

        day += hi;

        ll delta = hi * (K - A.size()) + B[1];
        x += delta / (B[0] + B[1]);

        ll tmp = B[0] + B[1] - delta % (B[0] + B[1]);
        B[1] = delta % (B[0] + B[1]);
        B[0] = tmp;

        if(A.size()) {
            ll a = *(--A.end()) + day;
            while(A.size() && a == x) {
                A.erase(--A.end());
                B[0]++;
                if(A.size()) a = *(--A.end()) + day;
            }
        }

        if(C.size()) {
            ll c = *C.begin();
            while(C.size() && x + 1 == c) {
                C.erase(C.begin());
                B[1]++;
                if(C.size()) c = *C.begin();
            }
        }
    }

    for(auto i : A) cout << i + day << " ";
    for(ll i = 0; i < B[0]; i++) cout << x << " ";
    for(ll i = 0; i < B[1]; i++) cout << x + 1 << " ";
    for(auto i : C) cout << i << " ";
}