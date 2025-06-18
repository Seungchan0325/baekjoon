#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int n, sieve[MAXN];

vector<vector<int>> solve_even(int n)
{
    vector<vector<int>> ans;
    for(int i = 1, j = 2*n-1; i < j; i+=2, j-=2) {
        ans.push_back({i, j});
    }
    return ans;
}
vector<vector<int>> solve_square(int n)
{
    int m = sqrt(n);
    vector<vector<int>> ans;
    for(int i = 1; i <= m; i++) {
        vector<int> group;
        int j = 2*i-1;
        for(int iter = 0; iter < m; iter++) {
            group.push_back(j);
            if((j+1)/2 % m == 0) j+=2;
            else j += 2*(m+1);
        }
        ans.push_back(group);
    }
    return ans;
}

void print(vector<vector<int>>& ans) {
    cout << ans.size() << "\n";
    for(auto i : ans) {
        cout << i.size() << " ";
        for(auto j : i) cout << j << " ";
        cout << "\n";
    }
}

int main()
{
    for(int i = 2; i < MAXN; i++) {
        for(int j = i+i; j < MAXN; j+=i) {
            sieve[j] = true;
        }
    }
    cin >> n;
    if(!sieve[n]) {
        cout << "-1\n";
        return 0;
    }

    if(n%2 == 0) {
        auto ans = solve_even(n);
        print(ans);
        return 0;
    }

    int m = sqrt(n);
    if(n == m * m) {
        auto ans = solve_square(n);
        print(ans);
        return 0;
    }

    int a = 3;
    while(n%a) a++;
    int b = n / a;

    auto ans = solve_square(a*a);
    int k = 0;
    for(int i = 2*a*a+1, j = 2*n-1; i < j; i+=2, j-=2) {
        ans[k].push_back(i);
        ans[k].push_back(j);
        k = (k+1)%a;
    }
    print(ans);
}