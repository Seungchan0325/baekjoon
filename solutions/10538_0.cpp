#include <bits/stdc++.h>

using namespace std;

const int ALPHABET = 2;

int toNumber(char c) { return c == 'o' ? 0 : 1; }

struct TrieNode {
    TrieNode* children[ALPHABET];

    int terminal;
    TrieNode* fail;
    vector<int> output;

    TrieNode() : terminal(-1), fail(NULL), output()
    {
        memset(children, 0, sizeof(children));
    }

    ~TrieNode()
    {
        for(int i = 0; i < ALPHABET; i++)
            if(children[i])
                delete children[i];
    }

    void insert(const char* key, int id)
    {
        if(*key == '\0')
            terminal = id;
        else {
            int next = toNumber(*key);
            if(children[next] == NULL)
                children[next] = new TrieNode();
            children[next]->insert(key + 1, id);
        }
    }

    TrieNode* find(const char* key)
    {
        if(*key == '\0') return this;
        int next = toNumber(*key);
        if(children[next] == NULL) return NULL;
        return children[next]->find(key + 1);
    }
};

void computeFailFunc(TrieNode* root)
{
    queue<TrieNode*> q;
    root->fail = root;
    q.push(root);
    while(!q.empty()) {
        TrieNode* here = q.front();
        q.pop();

        for(int edge = 0; edge < ALPHABET; edge++) {
            TrieNode* child = here->children[edge];
            if(!child) continue;

            if(here == root)
                child->fail = root;
            else {
                TrieNode* t = here->fail;
                while(t != root && t->children[edge] == NULL)
                    t = t->fail;
                if(t->children[edge]) t = t->children[edge];
                child->fail = t;
            }
            child->output = child->fail->output;
            if(child->terminal != -1)
                child->output.push_back(child->terminal);
            q.push(child);
        }
    }
}

vector<pair<int, int>> ahoCorasick(const string& s, TrieNode* root)
{
    vector<pair<int, int>> ret;
    TrieNode* state = root;

    for(int i = 0; i < s.size(); i++) {
        int chr = toNumber(s[i]);
        while(state != root && state->children[chr] == NULL)
            state = state->fail;
        if(state->children[chr]) state = state->children[chr];
        for(int j = 0; j < state->output.size(); j++)
            ret.push_back(make_pair(i, state->output[j]));
    }
    return ret;
}

vector<int> getPartialMatch(const vector<int>& N)
{
    int m = N.size();
    vector<int> pi(m, 0);

    int matched = 0;
    for(int i = 1; i < m; i++) {
        while(matched > 0 && N[i] != N[matched])
            matched = pi[matched - 1];
        
        if(N[i] == N[matched])
            pi[i] = ++matched;
    }
    return pi;
}

vector<int> kmpSearch(const vector<int>& H, const vector<int>& N)
{
    int n = H.size(), m = N.size();
    vector<int> ret;
    vector<int> pi = getPartialMatch(N);

    ret.reserve(n);

    int matched = 0;
    for(int i = 0; i < n; i++) {
        while(matched > 0 && H[i] != N[matched])
            matched = pi[matched - 1];
        
        if(H[i] == N[matched]) {
            matched++;
            if(matched == m) {
                ret.push_back(i - m + 2);
                matched = pi[matched - 1];
            }
        }
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int hp, wp, hm, wm;
    cin >> hp >> wp >> hm >> wm;

    TrieNode* root = new TrieNode();
    int last_id = 0;
    vector<int> ids(hp);
    for(int i = 0; i < hp; i++) {
        string buf;
        cin >> buf;

        TrieNode* other = root->find(buf.c_str());
        if(other != NULL) ids[i] = other->terminal;
        else {
            ids[i] = ++last_id;
            root->insert(buf.c_str(), ids[i]);
        }
    }

    computeFailFunc(root);
    vector<vector<int>> m(wm, vector<int>(hm));
    for(int i = 0; i < hm; i++) {
        string buf;
        cin >> buf;

        auto found = ahoCorasick(buf, root);
        for(auto [where, id] : found) {
            m[where][i] = id;
        }
    }

    delete root;

    int ans = 0;
    for(int i = 0; i < wm; i++) {
        auto found = kmpSearch(m[i], ids);
        ans += found.size();
    }
    cout << ans;
}