#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

const int NMAX = 250005;

bool visit[NMAX], schk[NMAX];
int n, q, k, s[NMAX], parents[NMAX], roots[NMAX], sizes[NMAX];
vector<int> graph[NMAX];

void make_tree(int node) {
    visit[node] = true;
    for(int child : graph[node]) {
        if(visit[child]) continue;

        make_tree(child);
        parents[child] = node;
    }
}

int find(int x) {
    if(roots[x] == x) return x;
    else return roots[x] = find(roots[x]);
}

void Union(int x, int y) {
    x = find(x);
    y = find(y);

    if(x == y) return;

    sizes[x] += sizes[y];
    roots[y] = x;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    int a, b;
    for(int i=0; i<n-1; i++) {
        cin>>a>>b; a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    make_tree(0);

    cin>>q;
    for(int i=0; i<q; i++) {
        cin>>k;
        
        for(int j=0; j<k; j++) {
            cin>>s[j]; s[j]--;
            roots[s[j]] = s[j];
            sizes[s[j]] = 1;
            schk[s[j]] = true;
        }

        for(int j=0; j<k; j++) {
            if(schk[parents[s[j]]])
                Union(s[j], parents[s[j]]);
        }

        ll ans=0;
        for(int j=0; j<k; j++) {
            if(roots[s[j]] == s[j]) {
                ans += (ll)sizes[s[j]] * ((ll)sizes[s[j]] - 1) / 2;
            }
        }

        for(int j=0; j<k; j++) {
            schk[s[j]] = false;
        }
        cout<<ans<<"\n";
    }
}