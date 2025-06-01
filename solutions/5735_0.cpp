#include <bits/stdc++.h>

using namespace std;

const int ALPHABET = 128;

struct Trie {
    int terminal;
    Trie* ch[ALPHABET];
    Trie* fail;
    vector<int> output;
    Trie() : ch{nullptr,}, terminal(-1) {}
    ~Trie() {
        for(int i = 0; i < ALPHABET; i++) {
            if(ch[i]) delete ch[i];
        }
    }

    void insert(const char *s, int id) {
        if(*s == '\0') {
            terminal = id;
            return;
        }
        if(ch[*s] == nullptr) ch[*s] = new Trie;
        ch[*s]->insert(s+1, id);
    }
};

void computeFailFunc(Trie* root)
{
    queue<Trie*> q;
    root->fail = root;
    q.push(root);
    while(!q.empty()) {
        auto here = q.front();
        q.pop();
        for(int i = 0; i < ALPHABET; i++) {
            auto ch = here->ch[i];
            if(ch == nullptr) continue;

            if(here == root)
                ch->fail = root;
            else {
                Trie* t = here->fail;
                while(t != root && t->ch[i] == nullptr)
                    t = t->fail;
                if(t->ch[i]) t = t->ch[i];
                ch->fail = t;
            }
            q.push(ch);

            ch->output = ch->fail->output;
            if(ch->terminal != -1)
                ch->output.push_back(ch->terminal);
        }
    }
}

vector<pair<int, int>>  ahoCorasick(const string& s, Trie* root)
{
    vector<pair<int, int>> ret;
    Trie* state = root;

    for(int i = 0; i < s.size(); i++) {
        int ch = s[i];
        while(state != root && state->ch[ch] == nullptr)
            state = state->fail;
        if(state->ch[ch] != nullptr) state = state->ch[ch];
        for(auto j : state->output)
            ret.emplace_back(i - j + 1, i);
    }
    return ret;
}

int main()
{
    while(true) {
        int n, m;
        cin >> n >> m;
        if(n == 0 && m == 0) break;

        Trie* root = new Trie();
        for(int i = 0; i < n; i++) {
            string s; cin >> s;
            root->insert(s.c_str(), s.length());
        }
        computeFailFunc(root);

        int ans = 0;
        cin.ignore();
        for(int i = 0; i < m; i++) {
            string s;
            getline(cin, s);
            auto where = ahoCorasick(s, root);
            sort(where.begin(), where.end(), [](pair<int, int> a, pair<int, int> b){
                if(a.second != b.second) return a.second < b.second;
                return a.first > b.first;
            });
            int lst = -1;
            for(auto [l, r] : where) {
                if(lst < l) {
                    lst = r;
                    ans++;
                }
            }
        }
        cout << ans << "\n";
        delete root;
    }
}