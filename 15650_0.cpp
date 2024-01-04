#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n, m;
vector<bool> flags;

void f(int cnt, string s, int prev) {
    if(cnt == m) {
        cout << s << "\n";
        return;
    }

    for(int i=prev+1; i<=n; i++) {
        if(flags[i] == true) continue;

        flags[i] = true;
        f(cnt+1, s+to_string(i)+' ', i);
        flags[i]  = false;
    }
}

int main() {
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    cin >> n >> m;
    flags.resize(n);
    f(0, string(), 0);
}