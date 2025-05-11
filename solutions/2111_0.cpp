#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20202;

// typedef int64_t ll;
typedef long long ll;

#define EL printf("\n")
#define pb push_back
#define FOR(i,l,r) for (int i=l;i<=r;i++)
#define FORD(i,r,l) for (int i=r;i>=l;i--)

const int base = 1e9;
typedef vector<int> BigInt;

void Set(BigInt &a) {
    while (a.size() > 1 && a.back() == 0) a.pop_back();
}

void Print(BigInt a) {
    Set(a);
    printf("%d", (a.size() == 0) ? 0 : a.back());
    FORD(i,a.size()-2,0) printf("%09d", a[i]); EL;
}

BigInt Integer(string s) {
    BigInt ans;
    if (s[0] == '-') return ans;
    if (s.size() == 0) {ans.pb(0); return ans;}
    while (s.size()%9 != 0) s = '0'+s;
    for (int i=0;i<s.size();i+=9) {
        int v = 0;
        for (int j=i;j<i+9;j++) v = v*10+(s[j]-'0');
        ans.insert(ans.begin(),v);
    }
    Set(ans);
    return ans;
}

BigInt Integer(char c[]) {
    string s = "";
    FOR(i,0,strlen(c)-1) s = s + c[i];
    return Integer(s);
}

BigInt Integer(ll x) {
    string s = "";
    while (x > 0) s = char(x%10+'0') + s, x /= 10;
    return Integer(s);
}

BigInt Integer(int x) {
    return Integer((ll) x);
}

void operator >> (istream &in, BigInt &a) {
    string s;
    getline(cin, s);
    a = Integer(s);
}

void operator << (ostream &out, BigInt a) {
    Print(a);
}

bool operator < (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    if (a.size() != b.size()) return (a.size() < b.size());
    FORD(i,a.size()-1,0)
        if (a[i] != b[i]) return (a[i] < b[i]);
    return false;
}

bool operator > (BigInt a, BigInt b) {
    return (b < a);
}

bool operator == (BigInt a, BigInt b) {
    return (!(a < b) && !(b < a));
}

bool operator <= (BigInt a, BigInt b) {
    return (a < b || a == b);
}

bool operator >= (BigInt a, BigInt b) {
    return (b < a || b == a);
}

bool operator < (BigInt a, int b) {
    return (a < Integer(b));
}

bool operator > (BigInt a, int b) {
    return (a > Integer(b));
}

bool operator == (BigInt a, int b) {
    return (a == Integer(b));
}

bool operator >= (BigInt a, int b) {
    return (a >= Integer(b));
}

bool operator <= (BigInt a, int b) {
    return (a <= Integer(b));
}

BigInt max(BigInt a, BigInt b) {
    if (a > b) return a;
    return b;
}

BigInt min(BigInt a, BigInt b) {
    if (a < b) return a;
    return b;
}

BigInt operator + (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    BigInt ans;
    int carry = 0;
    FOR(i,0,max(a.size(), b.size())-1) {
        if (i < a.size()) carry += a[i];
        if (i < b.size()) carry += b[i];
        ans.pb(carry%base);
        carry /= base;
    }
    if (carry) ans.pb(carry);
    Set(ans);
    return ans;
}

BigInt operator + (BigInt a, int b) {
    return a + Integer(b);
}

BigInt operator * (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    BigInt ans;
    ans.assign(a.size()+b.size(), 0);
    FOR(i,0,a.size()-1) {
        ll carry = 0ll;
        for (int j=0;j<b.size() || carry > 0;j++) {
            ll s = ans[i+j] + carry + (ll)a[i]*(j<b.size()?(ll)b[j]:0ll);
            ans[i+j] = s%base;
            carry = s/base;
        }
    }
    Set(ans);
    return ans;
}

BigInt operator * (BigInt a, int b) {
    return a * Integer(b);
}

void operator *= (BigInt &a, BigInt b) {
    a = a * b;
}

void operator *= (BigInt &a, int b) {
    a = a * b;
}

BigInt ans;
bool iscactus = true;
int n, m, low[MAXN], num[MAXN], dfsn;
vector<int> g[MAXN];
stack<pair<int, int>> s;

void dfs(int u, int p)
{
    num[u] = low[u] = ++dfsn;
    for(auto v : g[u]) {
        if(v == p) continue;
        if(num[v] < num[u]) s.emplace(u, v);
        if(!num[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(num[u] <= low[v]) {
                set<int> vertex;
                int edge = 0;
                while(true) {
                    vertex.insert(s.top().first);
                    vertex.insert(s.top().second);
                    edge++;
                    if(s.top() == pair(u, v)) { s.pop(); break; }
                    s.pop();
                }
                if(vertex.size() >= 3 && edge > vertex.size()) iscactus = false;
                if(vertex.size() >= 3) {
                    ans *= (vertex.size() + 1);
                }
            }
        }
        else low[u] = min(low[u], num[v]);
    }
}

int main()
{
    ans = Integer(1);
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int k;
        cin >> k;
        vector<int> vtx(k);
        for(auto& i : vtx) cin >> i;
        for(int i = 0; i < k-1; i++) {
            int u = vtx[i];
            int v = vtx[i+1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
    }
    dfs(1, -1);
    for(int i = 1; i <= n; i++) if(!num[i]) {
        cout << "0\n";
        return 0;
    }
    if(!iscactus) {
        cout << "0\n";
        return 0;
    }
    Print(ans);
}