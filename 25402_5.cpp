#include <iostream>
#include <memory.h>
#include <vector>

using namespace std;

int n, q, k;
bool s[250000];
vector<int> adjlist[250000];

int factorial(int x) {
    int ret = 1;
    for(int i=2; i<=x; i++) ret *= i;
    return ret;
}

int C(int n, int r) {
    return factorial(n)/(factorial(r)*factorial(n-r));
}

int dfs(int node) {
    if(!s[node]) return 0;

    int ret = 1;
    s[node] = false;

    for(int i : adjlist[node]) {
        ret += dfs(i);
    }

    return ret;
}

int main() {
    scanf("%d", &n);

    int a, b;
    for(int i=0; i<n-1; i++) {
        scanf("%d %d", &a, &b); a--; b--;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }

    cin>>q;
    for(int i=0; i<q; i++) {
        memset(s, 0, sizeof(s));
        scanf("%d", &k);
        for(int j=0; j<k; j++) {
            int a; scanf("%d", &a);
            s[a-1] = true;
        }

        int ans=0;
        for(int node=0; node<n; node++) {
            ans += C(dfs(node), 2);
        }
        printf("%d\n", ans);
    }
}