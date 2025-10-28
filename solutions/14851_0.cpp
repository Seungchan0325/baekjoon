#pragma GCC optimize("O3", "Ofast", "unroll-loops")
#pragma GCC target("avx,avx2")

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200000;

bitset<MAXN> a, b;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    string sa, sb;
    cin >> sa >> sb;
    reverse(sa.begin(), sa.end());
    reverse(sb.begin(), sb.end());
    a = bitset<MAXN>(sa);
    b = bitset<MAXN>(sb);

    int q; cin >> q;
    while(q--) {
        int p1, p2, len;
        cin >> p1 >> p2 >> len;
        bitset<MAXN> mask; mask.set(); mask>>=MAXN-len;
        auto t = ((a>>p1)^(b>>p2))&mask;
        cout << t.count() << "\n";
    }
}