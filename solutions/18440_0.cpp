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

template<size_t sz = MAXN>
bitset<sz> LCS(const string& a, const string& b)
{
    bitset<sz> D, x, S[26];
    for(int i = 0; i < b.size(); i++) S[b[i]-'A'][i] = 1;
    for(int i = 0; i < a.size(); i++) {
        x = S[a[i]-'A'] | D; D <<= 1; D[0] = 1;
        D = x & (x ^ (x - D));
    }
    return D;
}

int lcs1[MAXN], lcs2[MAXN], prv[MAXN];
string a, b, ans;

void solve_small(int l, int r, int s, int e)
{
    if(r < l) return;
    if(l == r) {
        for(int i = s; i <= e; i++) {
            if(a[l-1] == b[i-1]) {
                ans.push_back(a[l-1]);
                return;
            }
        }
        return;
    }
    int m = (l + r) / 2;
    for(int i = s-1; i <= e+1; i++) {
        lcs1[i] = prv[i] = 0;
    }
    for(int i = l; i <= m; i++) {
        for(int j = s; j <= e; j++) {
            if(a[i-1] == b[j-1]) lcs1[j] = prv[j-1] + 1;
            else lcs1[j] = max(lcs1[j-1], prv[j]);
        }
        for(int j = s; j <= e; j++) prv[j] = lcs1[j];
    }
    for(int i = s-1; i <= e+1; i++) {
        lcs2[i] = prv[i] = 0;
    }
    for(int i = r; i >= m+1; i--) {
        for(int j = e; j >= s; j--) {
            if(a[i-1] == b[j-1]) lcs2[j] = prv[j+1] + 1;
            else lcs2[j] = max(lcs2[j+1], prv[j]);
        }
        for(int j = e; j >= s; j--) prv[j] = lcs2[j];
    }
    int mx = -1, opt = 0;
    for(int i = s-1; i <= e; i++) {
        if(lcs1[i] + lcs2[i+1] > mx) {
            mx = lcs1[i] + lcs2[i+1];
            opt = i;
        }
    }
    solve_small(l, m, s, opt);
    solve_small(m+1, r, opt+1, e);
}

void solve(int l, int r, int s, int e)
{
    if(r < l) return;
    if(l == r) {
        for(int i = s; i <= e; i++) {
            if(a[l-1] == b[i-1]) {
                ans.push_back(a[l-1]);
                return;
            }
        }
        return;
    }
    if(e - s < 500) return solve_small(l, r, s, e);
    int m = (l + r) / 2;
    string la(a.begin()+l-1, a.begin()+m);
    string ra(a.begin()+m, a.begin()+r);
    string bp(b.begin()+s-1, b.begin()+e);
    auto lcs1 = LCS(la, bp);
    reverse(ra.begin(), ra.end());
    reverse(bp.begin(), bp.end());
    auto lcs2 = LCS(ra, bp);
    int mx = -1, opt = 0;
    int sum = lcs2.count();
    for(int i = 0, j = ssize(bp); i <= bp.size(); i++, j--) {
        sum -= lcs2[j];
        if(mx < sum) {
            mx = sum;
            opt = i+s-1;
        }
        sum += lcs1[i];
    }
    solve(l, m, s, opt);
    solve(m+1, r, opt+1, e);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> a >> b;
    solve(1, ssize(a), 1, ssize(b));
    cout << ans.size() << "\n";
    cout << ans << "\n";
}