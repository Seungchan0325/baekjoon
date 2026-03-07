#define private public
#include <bitset>
#undef private

#include <bits/stdc++.h>
#include <x86intrin.h>
using namespace std;

template<size_t _Nw> void _M_do_sub(_Base_bitset<_Nw> &A, const _Base_bitset<_Nw> &B) {
	for(int i=0, c=0; i<_Nw; i++)
		c=_subborrow_u64(c, A._M_w[i], B._M_w[i], (unsigned long long*)&A._M_w[i]);
}
template<> void _M_do_sub(_Base_bitset<1> &A, const _Base_bitset<1> &B) {
	A._M_w-=B._M_w;
}
template<size_t _Nb> bitset<_Nb>& operator-=(bitset<_Nb> &A, const bitset<_Nb> &B) {
	_M_do_sub(A, B);
	return A;
}
template<size_t _Nb> inline bitset<_Nb> operator-(const bitset<_Nb> &A, const bitset<_Nb> &B) {
	bitset<_Nb> C(A);
	return C-=B;
}

template<size_t sz>
vector<int> _LCS(const string& a, const string& b)
{
    bitset<sz> D, x, S[26];
    for(int i = 0; i < b.size(); i++) S[b[i]-'A'][i] = 1;
    for(int i = 0; i < a.size(); i++) {
        x = S[a[i]-'A'] | D; D <<= 1; D[0] = 1;
        D = x & (x ^ (x - D));
    }

    vector<int> dp(b.size()+1);
    for(int i = 0; i < b.size(); i++) {
        dp[i+1] = dp[i] + D[i];
    }
    return dp;
}

vector<int> LCS(const string& a, const string& b)
{
    if(b.size() <= 100) return _LCS<100>(a, b);
    if(b.size() <= 500) return _LCS<500>(a, b);
    if(b.size() <= 1000) return _LCS<1000>(a, b);
    if(b.size() <= 2000) return _LCS<2000>(a, b);
    if(b.size() <= 3000) return _LCS<3000>(a, b);
    if(b.size() <= 4000) return _LCS<4000>(a, b);
    if(b.size() <= 5000) return _LCS<5000>(a, b);
    if(b.size() <= 6000) return _LCS<6000>(a, b);
    if(b.size() <= 7000) return _LCS<7000>(a, b);
    if(b.size() <= 8000) return _LCS<8000>(a, b);
    if(b.size() <= 9000) return _LCS<9000>(a, b);
    if(b.size() <= 10000) return _LCS<10000>(a, b);
    if(b.size() <= 20000) return _LCS<20000>(a, b);
    if(b.size() <= 30000) return _LCS<30000>(a, b);
    if(b.size() <= 40000) return _LCS<40000>(a, b);
    if(b.size() <= 50000) return _LCS<50000>(a, b);
    assert(0);
}

string U;

void solve(const string& S, const string& T, int l, int r, int s, int e)
{
    if(r < l) return;
    if(l == r) {
        for(int i = s; i <= e; i++) {
            if(S[l] == T[i]) {
                U += T[i];
                break;
            }
        }
        return;
    }

    int m = (l + r) / 2;
    string lef = S.substr(l, m-l+1); // [l, m]
    string rig = S.substr(m+1, r-m); // [m+1, r]
    string part = T.substr(s, e-s+1); // [s, e]
    auto llcs = LCS(lef, part); llcs.push_back(llcs.back());
    reverse(rig.begin(), rig.end());
    reverse(part.begin(), part.end());
    auto rlcs = LCS(rig, part); rlcs.push_back(rlcs.back());
    reverse(rlcs.begin(), rlcs.end());

    int opt = -1, opti = -1;
    for(int i = 0; i < e-s+2; i++) {
        if(opt < llcs[i] + rlcs[i+1]) {
            opt = llcs[i] + rlcs[i+1];
            opti = i+s-1;
        }
    }

    solve(S, T, l, m, s, opti);
    solve(S, T, m+1, r, opti+1, e);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string S;
    string T;
    cin >> S >> T;
    solve(S, T, 0, ssize(S)-1, 0, ssize(T)-1);
    cout << U.size() << "\n";
    cout << U << "\n";
}