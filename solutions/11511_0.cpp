#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1<<17;
const int mod = 10007;

struct Node {
    Node() : dp{1, 0, }, mul(1) {}
    Node(int x, int y) : dp{0, }, mul((x+y)%mod) {
        dp[0] = y % mod;
        dp[1] = x % mod;
    }
    int dp[20];
    int mul;
};

int N, S, Q, C, A[MAXN], B[MAXN];
Node tree[2*MAXN];

Node merge(const Node& a, const Node& b)
{
    Node res; res.dp[0] = 0;
    for(int i = 0; i < C; i++) {
        for(int j = 0; j <= i; j++) {
            res.dp[i] = (res.dp[i] + a.dp[j] * b.dp[i-j] % mod) % mod;
        }
    }
    res.mul = a.mul * b.mul % mod;
    return res;
}

void update(int x, Node v)
{
    tree[x+=S] = v;
    while(x>>=1) tree[x] = merge(tree[x<<1], tree[x<<1|1]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> C;
    for(int i = 0; i < N; i++) cin >> A[i];
    for(int i = 0; i < N; i++) cin >> B[i];
    S = bit_ceil((unsigned)N);
    for(int i = 0; i < N; i++) update(i, Node(A[i], B[i]));
    cin >> Q;
    while(Q--) {
        int p, a, b;
        cin >> p >> a >> b; p--;
        update(p, Node(a, b));
        int ans = tree[1].mul;
        for(int i = 0; i < C; i++) ans -= tree[1].dp[i];
        ans = (ans % mod + mod) % mod;
        cout << ans << "\n";
    }
}