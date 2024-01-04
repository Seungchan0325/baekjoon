#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll=long long;

constexpr int MAX_SIZE = 1000;

ll T, N, M, A[MAX_SIZE], B[MAX_SIZE];
vector<ll> AA, BB;

int main() {
    cin>>T;

    cin>>N;
    for(int i=0; i<N; i++) {
        cin>>A[i];
    }

    cin>>M;
    for(int i=0; i<M; i++) {
        cin>>B[i];
    }

    for(int i=0; i<N; i++) {
        int tmp=0;
        for(int j=i; j<N; j++) {
            AA.push_back(tmp+=A[j]);
        }
    }

    for(int i=0; i<M; i++) {
        int tmp=0;
        for(int j=i; j<M; j++) {
            BB.push_back(tmp+=B[j]);
        }
    }

    sort(AA.begin(), AA.end());
    sort(BB.begin(), BB.end());

    ll cnt=0;
    for(int i=0; i<BB.size(); i++) {
        cnt += upper_bound(AA.begin(), AA.end(), T-BB[i]) - lower_bound(AA.begin(), AA.end(), T-BB[i]);
    }
    
    cout<<cnt<<endl;
}