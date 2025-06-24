#include <bits/stdc++.h>

using namespace std;

const int ALPHABET = 26;
const int mod = 1e9 + 9;

const int MAX = 400;

int p;
int terminal[MAX], output[MAX], fail[MAX];
int dp[55][400][1<<7];
int ch[MAX][ALPHABET];

int get_idx(char c)
{
    return c - 'a';
}

int create()
{
    return p++;
}

void insert(int u, int id, const char *s)
{
    if(*s == '\0') {
        terminal[u] = id;
        return;
    }

    if(ch[u][get_idx(*s)] == 0) {
        ch[u][get_idx(*s)] = create();
    }

    insert(ch[u][get_idx(*s)], id, s+1);
}

void computeFailFunc(int root)
{
    queue<int> q; q.push(root);

    fail[root] = root;
    while(!q.empty()) {
        int here = q.front(); q.pop();

        for(int i = 0; i < ALPHABET; i++) {
            int next = ch[here][i];
            if(ch[here][i] == 0) {
                int state = fail[here];
                while(state != root && ch[state][i] == 0)
                    state = fail[state];
                if(ch[state][i]) state = ch[state][i];
                ch[here][i] = state;
            } else {
                if(here == root) fail[next] = root;
                else {
                    int state = fail[here];
                    while(state != root && ch[state][i] == 0)
                       state = fail[state];
                    if(ch[state][i]) {
                        state = ch[state][i];
                    }
                    fail[next] = state;
                }
                
                output[next] |= output[fail[next]];
                if(terminal[next]) output[next] |= terminal[next];

                q.push(next);
            }
        }
    }
}

int main()
{
    int n, c, l; cin >> n >> c >> l;
    create();
    int root = create();

    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        insert(root, 1<<i, s.c_str());
    }

    computeFailFunc(root);

    dp[0][root][0] = 1;
    for(int i = 0; i < l; i++) {
        for(int j = 1; j <= p; j++) {
            for(int bit = 0; bit < (1<<n); bit++) {
                for(int k = 0; k < ALPHABET; k++) {
                    int x = ch[j][k];
                    dp[i+1][x][bit|output[x]] += dp[i][j][bit];
                    dp[i+1][x][bit|output[x]] %= mod;
                }
            }
        }
    }

    int ans = 0;
    for(int j = 1; j <= p; j++) {
        for(int bit = 0; bit < (1<<n); bit++) {
            if(popcount((unsigned int)bit) == c) {
                ans += dp[l][j][bit];
                ans %= mod;
            }
        }
    }
    cout << ans;
}