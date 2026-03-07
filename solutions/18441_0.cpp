#define private public
#include <bitset>
#undef private

#include <bits/stdc++.h>
#include <x86intrin.h>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Author : jinhan814
 * Date : 2021-05-06
 * Source : https://blog.naver.com/jinhan814/222266396476
 * Description : FastIO implementation for cin, cout.
 */
constexpr int SZ = 1 << 20;

class INPUT {
private:
    char read_buf[SZ];
    int read_idx, next_idx;
    bool __END_FLAG__, __GETLINE_FLAG__;
public:
    explicit operator bool() { return !__END_FLAG__; }
    bool IsBlank(char c) { return c == ' ' || c == '\n'; }
    bool IsEnd(char c) { return c == '\0'; }
    char _ReadChar() {
        if (read_idx == next_idx) {
            next_idx = fread(read_buf, sizeof(char), SZ, stdin);
            if (next_idx == 0) return 0;
            read_idx = 0;
        }
        return read_buf[read_idx++];
    }
    char ReadChar() {
        char ret = _ReadChar();
        for (; IsBlank(ret); ret = _ReadChar());
        return ret;
    }
    template<typename T> T ReadInt() {
        T ret = 0; char cur = _ReadChar(); bool flag = 0;
        for (; IsBlank(cur); cur = _ReadChar());
        if (cur == '-') flag = 1, cur = _ReadChar();
        for (; !IsBlank(cur) && !IsEnd(cur); cur = _ReadChar()) ret = 10 * ret + (cur & 15);
        if (IsEnd(cur)) __END_FLAG__ = 1;
        return flag ? -ret : ret;
    }
    string ReadString() {
        string ret; char cur = _ReadChar();
        for (; IsBlank(cur); cur = _ReadChar());
        for (; !IsBlank(cur) && !IsEnd(cur); cur = _ReadChar()) ret.push_back(cur);
        if (IsEnd(cur)) __END_FLAG__ = 1;
        return ret;
    }
    double ReadDouble() {
        string ret = ReadString();
        return stod(ret);
    }
    string getline() {
        string ret; char cur = _ReadChar();
        for (; cur != '\n' && !IsEnd(cur); cur = _ReadChar()) ret.push_back(cur);
        if (__GETLINE_FLAG__) __END_FLAG__ = 1;
        if (IsEnd(cur)) __GETLINE_FLAG__ = 1;
        return ret;
    }
    friend INPUT& getline(INPUT& in, string& s) { s = in.getline(); return in; }
} _in;

class OUTPUT {
private:
    char write_buf[SZ];
    int write_idx;
public:
    ~OUTPUT() { Flush(); }
    explicit operator bool() { return 1; }
    void Flush() {
        fwrite(write_buf, sizeof(char), write_idx, stdout);
        write_idx = 0;
    }
    void WriteChar(char c) {
        if (write_idx == SZ) Flush();
        write_buf[write_idx++] = c;
    }
    template<typename T> int GetSize(T n) {
        int ret = 1;
        for (n = n >= 0 ? n : -n; n >= 10; n /= 10) ret++;
        return ret;
    }
    template<typename T> void WriteInt(T n) {
        int sz = GetSize(n);
        if (write_idx + sz >= SZ) Flush();
        if (n < 0) write_buf[write_idx++] = '-', n = -n;
        for (int i = sz; i-- > 0; n /= 10) write_buf[write_idx + i] = n % 10 | 48;
        write_idx += sz;
    }
    void WriteString(string s) { for (auto& c : s) WriteChar(c); }
    void WriteDouble(double d) { WriteString(to_string(d)); }
} _out;

/* operators */
INPUT& operator>> (INPUT& in, char& i) { i = in.ReadChar(); return in; }
INPUT& operator>> (INPUT& in, string& i) { i = in.ReadString(); return in; }
template<typename T, typename std::enable_if_t<is_arithmetic_v<T>>* = nullptr>
INPUT& operator>> (INPUT& in, T& i) {
    if constexpr (is_floating_point_v<T>) i = in.ReadDouble();
    else if constexpr (is_integral_v<T>) i = in.ReadInt<T>(); return in; }

OUTPUT& operator<< (OUTPUT& out, char i) { out.WriteChar(i); return out; }
OUTPUT& operator<< (OUTPUT& out, string i) { out.WriteString(i); return out; }
template<typename T, typename std::enable_if_t<is_arithmetic_v<T>>* = nullptr>
OUTPUT& operator<< (OUTPUT& out, T i) {
    if constexpr (is_floating_point_v<T>) out.WriteDouble(i);
    else if constexpr (is_integral_v<T>) out.WriteInt<T>(i); return out; }

/* macros */
#define fastio 1
#define cin _in
#define cout _out
#define istream INPUT
#define ostream OUTPUT
/////////////////////////////////////////////////////////////////////////////////////////////

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
    for(int i = 0; i < b.size(); i++) S[b[i]-'a'][i] = 1;
    for(int i = 0; i < a.size(); i++) {
        x = S[a[i]-'a'] | D; D <<= 1; D[0] = 1;
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
    if(b.size() <= 50) return _LCS<50>(a, b);
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
    // ios_base::sync_with_stdio(false); cin.tie(NULL);
    int tc; cin >> tc;
    for(int t = 1; t <= tc; t++) {
        string S;
        cin >> S;
        int opt = 0;
        int opti = 0;
        for(int i = 1; i < S.size(); i++) {
            string a = S.substr(0, i);
            string b = S.substr(i);
            int lcs = LCS(a, b)[b.size()];
            if(opt < lcs) {
                opt = lcs;
                opti = i;
            }
        }
        U = "";
        string a = S.substr(0, opti);
        string b = S.substr(opti);
        solve(a, b, 0, ssize(a)-1, 0, ssize(b)-1);

        cout << "Case #" << t << ": " << 2*U.size() << "\n";
        if(U.size()) cout << U << U << "\n";
    }
}