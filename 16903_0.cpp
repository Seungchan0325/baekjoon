#include <bits/stdc++.h>

using namespace std;

const int ALPHABET = 2;

int toNumber(char c) { return c - '0'; }

struct TrieNode {
    TrieNode* children[ALPHABET];
    int terminal;

    TrieNode() : terminal(0)
    {
        memset(children, 0, sizeof(children));
    }

    ~TrieNode()
    {
        for(int i = 0; i < ALPHABET; i++)
            if(children[i])
                delete children[i];
    }

    void insert(const char* key)
    {
        if(*key == '\0')
            terminal += 1;
        else {
            int next = toNumber(*key);
            if(children[next] == NULL)
                children[next] = new TrieNode();
            children[next]->insert(key + 1);
        }
    }

    bool erase(const char* key)
    {
        if(*key == '\0')
            return --terminal == 0;
        else {
            int next = toNumber(*key);
            assert(children[next] != NULL);
            if(children[next]->erase(key + 1)) {
                delete children[next];
                children[next] = NULL;
                if(children[next^1] == NULL)
                    return true;
            }
        }
        return false;
    }

    TrieNode* find(const char* key)
    {
        if(*key == '\0') return this;
        int next = toNumber(*key);
        if(children[next] == NULL) return NULL;
        return children[next]->find(key + 1);
    }

    string getMaxXor(const char* key)
    {
        if(*key == '\0')
            return "";
        else {
            assert(children[0] != NULL || children[1] != NULL);
            char c = '0' + '1' - *key;
            char ret = '1';
            int next = toNumber(c);
            if(children[next] == NULL) {
                ret = '0';
                next ^= 1;
            }
            return ret + children[next]->getMaxXor(key + 1);
        }
    }
};

int M;

string btos(int x)
{

    string s;
    for(int i = 31; i >= 0; i--) {
        if(x & (1<<i)) s.push_back('1');
        else s.push_back('0');
    }
    return s;
}

int bstoi(string s)
{
    int ret = 0;
    reverse(s.begin(), s.end());
    for(int i = 0; i < s.size(); i++) {
        ret |= (toNumber(s[i])<<i);
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    TrieNode* root = new TrieNode;
    root->insert(btos(0).c_str());
    cin >> M;
    while(M--) {
        int t, x;
        cin >> t >> x;
        if(t == 1) {
            string s = btos(x);
            root->insert(s.c_str());
        } else if(t == 2) {
            string s = btos(x);
            root->erase(s.c_str());
        } else {
            string s = btos(x);
            string result = root->getMaxXor(s.c_str());
            cout << bstoi(result) << "\n";
        }
    }
    delete root;
}