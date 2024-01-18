#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> primes;

void make_primes() {
    vector<bool> table(N+1);
    for(int i=2; i*i<=N; i++) {
        if(table[i]) continue;

        for(int j=i+i; j<=N; j+=i) {
            table[j] = true;
        }
    }
    
    for(int i=2; i<=N; i++)
        if(!table[i])
            primes.push_back(i);
}

int solve() {
    int cnt=0, sum=0;
    int r, l;
    r = l = 0;

    while(l <= r) {
        if(sum >= N) {
            sum -= primes[l];
            l++;
        } else {
            if (r == primes.size()) break;
            sum += primes[r];
            r++;
        }
        if (sum == N) cnt++;
    }

    return cnt;
}

int main() {
    cin>>N;
    make_primes();
    cout<<solve()<<endl;
}