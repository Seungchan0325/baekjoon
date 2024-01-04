#include <bits/stdc++.h>

using namespace std;

const int MAXN = 51;
const int MAXV = 2000;

bool is_not_prime[MAXV+1];
int n, arr[MAXN], visited[MAXN], owner[MAXN], old_owner[MAXN];
vector<int> v, nv, ans;

void eratosthenes() {
    //is_not_prime[0] = is_not_prime[1] = 1;
    is_not_prime[2] = 0;
    for(int i=2; i*i<=MAXV; i++) {
        if(is_not_prime[i]) continue;
        for(int j=i*i; j<=MAXV; j+=i) {
            is_not_prime[j] = true;
        }
    }
}

bool dfs(int node) {
    visited[node] = true;
    for(int i=0; i<nv.size(); i++) {
        if(!is_not_prime[v[node] + nv[i]] && (owner[i] == -1 || (!visited[owner[i]] && dfs(owner[i])))) {
            owner[i] = node;
            return true;
        }
    }

    return false;
}

int main() {
    eratosthenes();
    cin>>n;
    for(int i=0; i<n; i++) cin>>arr[i];
    
    for(int i=0; i<n; i++) {
        owner[i] = -1;
        if((arr[0]&1) == (arr[i]&1)) {
            v.push_back(arr[i]);
        } else {
            nv.push_back(arr[i]);
        }
    }

    bool flag = false;
    for(int i=0; i<v.size(); i++) {
        memset(visited, 0, sizeof(visited));
        if(!dfs(i)) goto failed;
    }

    for(int i=0; i<nv.size(); i++) {
        if(owner[i] == -1) flag = true;
    }
    if(flag) goto failed;

    for(int i=0; i<nv.size(); i++) {
        memset(visited, 0, sizeof(visited));
        memcpy(old_owner, owner, sizeof(owner));

        if(owner[i] == 0) ans.push_back(nv[i]);

        *find(owner, owner + nv.size(), 0) = -1;
        if(!is_not_prime[arr[0] + nv[i]] && owner[i] >= 0 && dfs(owner[i])) {
            ans.push_back(nv[i]);
        }

        memcpy(owner, old_owner, sizeof(old_owner));
    }

    if(ans.empty()) goto failed;

    sort(ans.begin(), ans.end());
    for(int a : ans) cout<<a<<" ";
    return 0;
failed:
    cout<<-1;
}