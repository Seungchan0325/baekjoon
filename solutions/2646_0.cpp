#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;

int n, lengths[50];

bool isPossible(int sum, int purpose, ull& used) {
    if(sum == purpose) return true;
    if(sum > purpose) return false;

    for(int i=0; i<n; i++) {
        ull idx = (1ll << i);
        if(used & idx) continue;
        
        used += idx;
        if(isPossible(sum + lengths[i], purpose, used)) return true;
        used -= idx;
    }
    return false;
}

bool print(int sum, int purpose, ull& used) {
    if(sum == purpose) {
        return true;
    }
    if(sum > purpose) return false;

    for(int i=0; i<n; i++) {
        ull idx = (1ll << i);
        if(used & idx) continue;
        
        used += idx;
        if(print(sum + lengths[i], purpose, used)) {
            cout<<lengths[i]<<" ";
            return true;
        }
        used -= idx;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int sum = 0;
    cin>>n;
    for(int i=0; i<n; i++) { cin>>lengths[i]; sum += lengths[i]; }

    sort(lengths, lengths + n, greater<>());

    ull full = (1ll << n) - 1;
    int length = 1;
    for(; length <= sum; length++) {
        if(sum % length != 0) continue;

        ull used = 0;
        while(isPossible(0, length, used) && used < full);

        if(used == full) break;
    }

    cout<<length<<"\n";
    ull used = 0;
    while(used < full) {
        print(0, length, used);
        cout<<"\n";
    }
}