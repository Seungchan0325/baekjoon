#include <bits/stdc++.h>

using namespace std;


struct TreeNode {
    struct cmp {
        bool operator()(TreeNode* t1, TreeNode* t2) const {
            return t1->data < t2->data;
        }
    };

    string data;
    set<TreeNode*, cmp> childs;

    TreeNode(string str) : data(str) {};
    ~TreeNode() {
        for(TreeNode* child : childs) delete child;
    }

    void insert(vector<string>::iterator first, vector<string>::iterator last) {
        if(distance(first, last) == 1) {
            childs.insert(new TreeNode(*first));
            return;
        }

        for(TreeNode* child : childs)
            if(child->data == *first) {
                child->insert(first + 1, last);
                return;
            }
        
        TreeNode* child = new TreeNode(*first);
        child->insert(first + 1, last);
        childs.insert(child);
    }

    void print(int depth) {
        for(int i=1; i<depth; i++) cout<<"--";
        if(0 < depth)
            cout<<data<<"\n";

        for(TreeNode* child : childs)
            child->print(depth + 1);
    }
};

int n;
vector<vector<string>> ants;
TreeNode* root;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin>>n;
    ants.resize(n);
    for(auto& i : ants) {
        int k; cin>>k;
        i.resize(k);
        for(auto& j : i) cin>>j;
    }

    sort(ants.begin(), ants.end(), [](vector<string>& a, vector<string>& b) { return a.size() > b.size(); }); 
    
    root = new TreeNode("");
    for(auto& v : ants)
        root->insert(v.begin(), v.end());
    
    root->print(0);

    delete root;
}