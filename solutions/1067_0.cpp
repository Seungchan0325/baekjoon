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
    int n = max(bit_ceil(a.size()), bit_ceil(b.size()));
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
    int n;
    cin >> n;
    vec a(n), b(n);
    for(int i = 0; i < n; i++) {
        int v; cin >> v;
        a[i] = cpx(v, 0);
    }
    for(int i = 0; i < n; i++) {
        int v; cin >> v;
        b[i] = cpx(v, 0);
    }
    a.insert(a.end(), a.begin(), a.end());
    reverse(b.begin(), b.end());
    auto c = mul(a, b);
    ll ans = 0;
    for(auto i : c) {
        // cout << i.real() << " " << i.imag() << "\n";
        ans = max<ll>(ans, i.real());
    }
    cout << ans;
}