// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;

using cpx = complex<double>;
using vec = vector<cpx>;

constexpr double pi = numbers::pi;

void fft(vec& f, cpx w)
{
    int n = ssize(f);
    if(n == 1) return;
    vec even(n >> 1), odd(n >> 1);
    for(int i=0; i<n; i++) {
        if(i&1) odd[i>>1] = f[i];
        else even[i>>1] = f[i];
    }
    fft(even, w*w); fft(odd, w*w);
    cpx wp(1, 0);
    for(int i=0; i<n/2; i++) {
        f[i] = even[i] + wp * odd[i];
        f[i+n/2] = even[i] - wp * odd[i];
        wp = wp * w;
    }
}

vec mul(vec a, vec b)
{
    int n = 2 * max(bit_ceil(a.size()), bit_ceil(b.size()));
    a.resize(n); b.resize(n);
    vec c(n);

    cpx w(cos(2*pi/n), sin(2*pi/n));
    
    fft(a, w); fft(b, w);

    for(int i=0; i<n; i++) c[i] = a[i] * b[i];

    fft(c, cpx(w.real(), -w.imag()));
    for(int i=0; i<n; i++) {
        c[i] /= cpx(n, 0);
        c[i] = cpx(round(c[i].real()), round(c[i].imag()));
    }
    return c;
}

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    string _a, _b;
    cin >> _a >> _b;
    if(_a == "0" || _b == "0") {
        cout << "0";
        return 0;
    }
    if(ssize(_a)&1) _a = "0" + _a;
    if(ssize(_b)&1) _b = "0" + _b;
    vec a, b;
    for(int i = 0, j = 0; i < _a.size(); i+=2, j++) {
        a.push_back(0);
        a[j] = 10*(_a[i] - '0') + (_a[i+1] - '0');
    }
    
    for(int i = 0, j = 0; i < _b.size(); i+=2, j++) {
        b.push_back(0);
        b[j] = 10*(_b[i] - '0') + (_b[i+1] - '0');
    }
    
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    auto c = mul(a, b);
    vector<long long> ans;
    long long carry = 0;
    for(int i = 0; i < c.size() || carry; i++) {
        ans.push_back(0);
        if(i < c.size()) ans[i] += c[i].real();
        ans[i] += carry;

        carry = ans[i] / 100;
        ans[i] %= 100;
    }
    int i = ssize(ans) - 1;
    while(ans[i] == 0) i--;
    cout << ans[i--];
    for(; i >= 0; i--) cout << setfill('0') << setw(2) << ans[i];
}