#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int N;
    bool ispossible = true;
    cin >> N;
    for(int i = 1; i <= N; i++) {
        int x;
        cin >> x;
        if((i&1) != (x&1)) ispossible = false;
    }
    cout << (const char*)(ispossible ? "YES" : "NO");
}