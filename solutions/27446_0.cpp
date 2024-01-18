#include <iostream>
#include <algorithm>
#include <vector>
#include <memory.h>

using namespace std;

#define INF 987654321

int n, m, pages_mat[101], memoization[101];
vector<int> pages;

int min_ink(int idx) {
    if(memoization[idx] != -1) return memoization[idx];
    int ret = INF;
    
    if(idx >= pages.size()) return 0;
    for(auto i=idx; i < pages.size(); i++) {
        ret = min(5 + (pages[i] - pages[idx] + 1) * 2 + min_ink(i+1), ret);
    }

    memoization[idx] = ret;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int a;
    cin>>n>>m;
    for(int i=0; i<m; i++) {
        cin>>a;
        pages_mat[a] = 1;
    }
    
    memset(memoization, -1, sizeof(memoization));
    for(int i=1; i<=n; i++) {
        if(pages_mat[i] == 0) pages.push_back(i);
    }
    int result = min_ink(0);

    cout<<result<<endl;
}