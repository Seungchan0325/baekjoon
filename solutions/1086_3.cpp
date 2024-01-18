#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 16;

int n;
int k;
string input[MAXN];
int S[MAXN]; // 원소 % k의 값
int D[MAXN]; // (10 ^ (원소 자릿수)) % k
int mod10[51]; // (10 ^ i) % k
ll cache[101][1<<MAXN];

void calc_mod10() {
    mod10[0] = 1;
    for(int i = 1; i <= 50; i++) {
        mod10[i] = (mod10[i-1] * (10 % k)) % k;
    }
}

int mod(const string& num) {
    int ret = 0;

    //reverse(num.begin(), num.end());
    for(int i = 0; i < num.size(); i++) {
        int number = num[i] - '0';
        ret = (ret * 10 + number) % k;
        //ret = (ret + (number % k) * mod10[i]) % k;
    }
    return ret;
}

ll factorial(int x) {
    ll ret = 1;
    for(int i = 2; i <= x; i++) ret *= i;
    return ret;
}

ll solve(int cur, int taken) {
    if(taken == (1<<n)-1) return cur == 0 ? 1 : 0;

    ll& ret = cache[cur][taken];
    if(ret != -1) return ret;

    ret = 0;
    for(int i = 0; i < n; i++) {
        if(taken & (1<<i)) continue;

        int nxt = (cur * D[i] + S[i]) % k;
        ret += solve(nxt, taken | (1<<i));
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 0; i < n; i++) cin >> input[i];
    cin >> k;

    calc_mod10();
    for(int i = 0; i < n; i++) {
        S[i] = mod(input[i]);
        D[i] = mod10[input[i].length()];
    }

    memset(cache, -1, sizeof(cache));
    ll p = solve(0, 0);
    ll q = factorial(n);
    ll GCD = gcd(p, q);

    if(p == 0) cout << "0/1";
    else
        cout << p / GCD << "/" << q / GCD;
}