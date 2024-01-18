#include <bits/stdc++.h>

using namespace std;

int ans = 0;

struct node {
    node* childs[26];
    int cnt;
    bool is_end;

    node() {
        for(int i=0; i<26; i++) childs[i] = NULL;
        is_end = false;
        cnt = 0;
    }

    ~node() {
        for(int i=0; i<26; i++) delete childs[i];
    }

    void insert(const char* s) {
        if(*s == '\0') {
            is_end = true;
            return;
        }

        int next = *s - 'a';
        if(!childs[next]) {
            childs[next] = new node();
            cnt++;
        }
        childs[next]->insert(s + 1);
    }

    void find(const char* s, int k) {
        if(*s == '\0') {
            ans += k;
            return;
        }

        int next = *s - 'a';
        if(k == 0) childs[next]->find(s + 1, k + 1);
        else if(cnt == 1 && is_end == false) childs[next]->find(s + 1, k);
        else childs[next]->find(s + 1, k + 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n;
    while(cin>>n) {
        ans = 0;
        node* root = new node();
        vector<string> s(n);
        for(int i=0; i<n; i++) {
            cin>>s[i];
            root->insert(s[i].c_str());
        }
        for(int i=0; i<n; i++) {
            root->find(s[i].c_str(), 0);
        }
        cout<<fixed;
        cout.precision(2);
        cout<<(double)ans / n<<"\n";
        delete root;
    }
}