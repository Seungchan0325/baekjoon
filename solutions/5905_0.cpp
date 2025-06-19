#include <bits/stdc++.h>

using namespace std;

struct Trie {
    Trie* ch[3];
    Trie* fail;
    int terminal, dp[1010], vst[1010];
    Trie() : terminal(0), ch{0, } {
        for(int i = 0; i < 1010; i++) dp[i] = -1e9;
    }
    ~Trie()
    {
        for(int e = 0; e < 3; e++) {
            if(ch[e]) delete ch[e];
        }
    }

    void insert(const char* c)
    {
        if(*c == '\0') {
            terminal++;
            return;
        }
        if(ch[*c-'A'] == NULL) ch[*c-'A'] = new Trie;
        ch[*c-'A']->insert(c+1);
    }
};

void computeFail(Trie* root)
{
    queue<Trie*> q;
    root->fail = root;
    q.push(root);
    while(!q.empty()) {
        Trie* here = q.front(); q.pop();

        for(int e = 0; e < 3; e++) {
            Trie* child = here->ch[e];
            if(!child) {
                Trie* t = here->fail;
                while(t != root && t->ch[e] == NULL)
                    t = t->fail;
                if(t->ch[e]) t = t->ch[e];
                here->ch[e] = t;
                continue;
            }

            if(here == root) {
                child->fail = root;
            } else {
                Trie* t = here->fail;
                while(t != root && t->ch[e] == NULL)
                    t = t->fail;
                if(t->ch[e]) t = t->ch[e];
                child->fail = t;
                child->terminal += child->fail->terminal;
            }
            q.push(child);
        }
    }
}

void run(int k, Trie* root)
{
    queue<Trie*> q;
    q.push(root);
    root->vst[k] = true;
    while(!q.empty()) {
        Trie* here = q.front(); q.pop();

        for(int e = 0; e < 3; e++) {
            Trie* child = here->ch[e];
            child->dp[k+1] = max(child->dp[k+1], here->dp[k] + child->terminal);
            if(!child->vst[k]) {
                q.push(child);
                child->vst[k] = true;
            }
        }
        // here->fail->dp[k+1] = max(here->fail->dp[k+1], here->dp[k] + here->fail->terminal);
    }
}

int main()
{
    int n, k;
    cin >> n >> k;
    Trie* root = new Trie;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        root->insert(s.c_str());
    }
    computeFail(root);

    for(int i = 0; i < k; i++) {
        root->dp[i] = max(root->dp[i], 0);
        run(i, root);
    }

    int ans = 0;
    queue<Trie*> q; q.push(root);
    while(!q.empty()) {
        Trie* here = q.front(); q.pop();
        ans = max(ans, here->dp[k]);
        for(int e = 0; e < 3; e++) {
            Trie* child = here->ch[e];
            if(!child->vst[k]) {
                q.push(child);
                child->vst[k] = true;
            }
        }
    }
    cout << ans;
}