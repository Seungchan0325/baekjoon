#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void normalize(ll& a, ll& b, ll& c, ll& d)
{
    ll GCD = gcd(gcd(b, a), c);
    a /= GCD;
    b /= GCD;
    c /= GCD;
}

tuple<ll, ll, ll, ll> add(ll a0, ll b0, ll c0, ll d0, ll a1, ll b1, ll c1, ll d1)
{
    assert(d0 == d1);
    ll a2 = a0 * a1;
    ll b2 = a1 * b0 + a0 * b1;
    ll c2 = a1 * c0 + a0 * c1;
    ll d2 = d0;
    normalize(a2, b2, c2, d2);
    return make_tuple(a2, b2, c2, d2);
}

tuple<ll, ll, ll, ll> sub(ll a0, ll b0, ll c0, ll d0, ll a1, ll b1, ll c1, ll d1)
{
    assert(d0 == d1);
    ll a2 = a0 * a1;
    ll b2 = a1 * b0 - a0 * b1;
    ll c2 = a1 * c0 - a0 * c1;
    ll d2 = d0;
    normalize(a2, b2, c2, d2);
    return make_tuple(a2, b2, c2, d2);
}

tuple<ll, ll, ll, ll> mul(ll a0, ll b0, ll c0, ll d0, ll a1, ll b1, ll c1, ll d1)
{
    assert(d0 == d1);
    ll a2 = a0 * a1;
    ll b2 = b0 * b1 + c0 * c1 * d0;
    ll c2 = b0 * c1 + b1 * c0;
    ll d2 = d0;
    normalize(a2, b2, c2, d2);
    return make_tuple(a2, b2, c2, d2);
}

tuple<ll, ll, ll> square(ll b, ll c, ll d)
{
    ll b0 = b * b + c * c * d;
    ll c0 = 2 * b * c;
    ll d0 = d;
    return make_tuple(b0, c0, d0);
}

tuple<ll, ll, ll, ll, ll, ll, ll, ll> inverse(ll a0, ll b0, ll c0, ll d0, ll a1, ll b1, ll c1, ll d1)
{
    assert(d0 == d1);
    ll xb = a1 * b0;
    ll xc = a1 * c0;
    ll xd = d0;
    ll yb = a0 * b1;
    ll yc = a0 * c1;
    ll yd = d1;
    auto [bb1, cc1, dd1] = square(xb, xc, xd);
    auto [bb2, cc2, dd2] = square(yb, yc, yd);
    auto [_aa, bb, cc, dd] = add(1, bb1, cc1, dd1, 1, bb2, cc2, dd2);

    ll z = a0 * a1;
    ll a2, a3;
    a2 = a3 = bb * bb - cc * cc * dd;
    auto [_a2, b2, c2, d2] = mul(1, xb, xc, xd, 1, bb, -cc, dd);
    b2 *= z;
    c2 *= z;

    auto [_a3, b3, c3, d3] = mul(1, yb, yc, yd, 1, bb, -cc, dd);
    b3 *= z;
    c3 *= z;
    b3 = -b3;
    c3 = -c3;

    normalize(a2, b2, c2, d2);
    normalize(a3, b3, c3, d3);
    return make_tuple(a2, b2, c2, d2, a3, b3, c3, d3);
}

tuple<ll, ll, ll, ll> div(ll a0, ll b0, ll c0, ll d0, ll a1, ll b1, ll c1, ll d1)
{
    auto [a2, b2, c2, d2] = mul(1, a1 * b0, a1 * c0, d0, 1, a0 * b1, -a0 * c1, d1);
    a2 = a0 * a0 * b1 * b1 - a0 * a0 * c1 * c1 * d1;
    normalize(a2, b2, c2, d2);
    return make_tuple(a2, b2, c2, d2);
}

int main()
{
    ll a0, b0, c0, d0;
    ll a1, b1, c1, d1;
    ll a2, b2, c2, d2;
    ll a3, b3, c3, d3;
    cin >> a0 >> b0 >> c0 >> d0 >> a1 >> b1 >> c1 >> d1;
    cin >> a2 >> b2 >> c2 >> d2 >> a3 >> b3 >> c3 >> d3;

    {
        auto [ar, br, cr, dr] = add(a0, b0, c0, d0, a2, b2, c2, d2);
        auto [ac, bc, cc, dc] = add(a1, b1, c1, d1, a3, b3, c3, d3);
        if(cr == 0) dr = 0;
        if(cc == 0) dc = 0;
        printf("%lld %lld %lld %lld %lld %lld %lld %lld\n", ar, br, cr, dr, ac, bc, cc, dc);
    }

    {
        auto [ar, br, cr, dr] = sub(a0, b0, c0, d0, a2, b2, c2, d2);
        auto [ac, bc, cc, dc] = sub(a1, b1, c1, d1, a3, b3, c3, d3);
        if(cr == 0) dr = 0;
        if(cc == 0) dc = 0;
        printf("%lld %lld %lld %lld %lld %lld %lld %lld\n", ar, br, cr, dr, ac, bc, cc, dc);
    }

    {
        auto [ar0, br0, cr0, dr0] = mul(a0, b0, c0, d0, a2, b2, c2, d2);
        auto [ar1, br1, cr1, dr1] = mul(a1, b1, c1, d1, a3, b3, c3, d3);
        auto [ar, br, cr, dr] = sub(ar0, br0, cr0, dr0, ar1, br1, cr1, dr1);

        auto [ac0, bc0, cc0, dc0] = mul(a0, b0, c0, d0, a3, b3, c3, d3);
        auto [ac1, bc1, cc1, dc1] = mul(a2, b2, c2, d2, a1, b1, c1, d1);
        auto [ac, bc, cc, dc] = add(ac0, bc0, cc0, dc0, ac1, bc1, cc1, dc1);
        if(cr == 0) dr = 0;
        if(cc == 0) dc = 0;
        printf("%lld %lld %lld %lld %lld %lld %lld %lld\n", ar, br, cr, dr, ac, bc, cc, dc);
    }

    {
        auto [a4, b4, c4, d4, a5, b5, c5, d5] = inverse(a2, b2, c2, d2, a3, b3, c3, d3);

        auto [ar0, br0, cr0, dr0] = mul(a0, b0, c0, d0, a4, b4, c4, d4);
        auto [ar1, br1, cr1, dr1] = mul(a1, b1, c1, d1, a5, b5, c5, d5);
        auto [ar, br, cr, dr] = sub(ar0, br0, cr0, dr0, ar1, br1, cr1, dr1);

        auto [ac0, bc0, cc0, dc0] = mul(a0, b0, c0, d0, a5, b5, c5, d5);
        auto [ac1, bc1, cc1, dc1] = mul(a4, b4, c4, d4, a1, b1, c1, d1);
        auto [ac, bc, cc, dc] = add(ac0, bc0, cc0, dc0, ac1, bc1, cc1, dc1);
        if(cr == 0) dr = 0;
        if(cc == 0) dc = 0;
        printf("%lld %lld %lld %lld %lld %lld %lld %lld\n", ar, br, cr, dr, ac, bc, cc, dc);
    }
}