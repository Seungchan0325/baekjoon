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

const int MAXN = 50000;

int LCS(const string& a, const string& b)
{
    bitset<MAXN> D, x, S[26];
    for(int i = 0; i < b.size(); i++) S[b[i]-'a'][i] = 1;
    for(int i = 0; i < a.size(); i++) {
        x = S[a[i]-'a'] | D; D <<= 1; D[0] = 1;
        D = x & (x ^ (x - D));
    }
    return D.count();
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string S, T;
    cin >> S;
    cin >> T;
    char X, Y;
    cin >> X;
    cin >> Y;

    S.erase(remove(S.begin(), S.end(), Y), S.end());
    T.erase(remove(T.begin(), T.end(), Y), T.end());

    int i = S.find(X);
    int j = T.find(X);

    auto S1 = S.substr(0, i);
    auto S2 = S.substr(i+1);
    auto T1 = T.substr(0, j);
    auto T2 = T.substr(j+1);

    int ans = LCS(S1, T1) + LCS(S2, T2) + 1;
    while(ans > 0) {
        bool isprime = true;
        if(ans == 1) isprime = false;
        for(int i = 2; i*i <= ans; i++) {
            if(ans % i == 0) {
                isprime = false;
            }
        }
        if(isprime) break;
        ans--;
    }

    if(ans <= 0) cout << "-1\n";
    else cout << ans << "\n";
}