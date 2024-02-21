#include <bits/stdc++.h>

using namespace std;

const int ALPHABET = 26;

int toNumber(char c) { return c - 'a'; }

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

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;
    TrieNode* root = new TrieNode;
    for(int i = 0; i < n; i++) {
        char buf[128];
        cin >> buf;
        root->insert(buf, i);
    }

    computeFailFunc(root);

    int q;
    cin >> q;
    while(q--) {
        string buf;
        cin >> buf;
        auto found = ahoCorasick(buf, root);
        if(found.empty()) cout << "NO\n";
        else cout << "YES\n";
    }
    delete root;
}