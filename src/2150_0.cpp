#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int MAX = 10001;

int v, e, id, p[MAX], sccNum;
bool finished[MAX];
stack<int> s;
vector<int> adjlist[MAX];
vector<vector<int>> scc;

int findSCC(int x) {
    p[x] = ++id;
    s.push(x);

    int result = p[x];
    for(int next : adjlist[x]) {
        if(p[next] == 0) result = min(result, findSCC(next));
        else if(!finished[next]) result = min(result, p[next]);
    }

    if(result == p[x]) {
        vector<int> _scc;
        while(true) {
            int t = s.top(); s.pop();
            _scc.push_back(t);
            finished[t] = true;
            if(t == x) break;
        }
        sort(_scc.begin(), _scc.end());
        scc.push_back(_scc);
        sccNum++;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>v>>e;
    for(int i=0; i<e; i++) {
        int a, b; cin>>a>>b;
        adjlist[a].push_back(b);
    }

    for(int i=1; i<=v; i++) {
        if(p[i] == 0) findSCC(i);
    }

    sort(scc.begin(), scc.end(), [](vector<int>& a, vector<int>& b) {
        return a.front() < b.front();
    });

    cout<<sccNum<<"\n";
    for(auto& _scc:scc) {
        for(int i:_scc) cout<<i<<" ";
        cout<<"-1\n";
    }
}