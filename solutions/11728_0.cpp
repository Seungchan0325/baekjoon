#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 1000000;

int N, M, C[MAX_SIZE*2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>N>>M;
    for(int i=0; i<N; i++)
        cin>>C[i];
    for(int i=0; i<M; i++)
        cin>>C[i+N];
    
    sort(C, C+N+M);

    for(int i=0; i<N+M; i++)
        cout<<C[i]<<" ";
    cout<<"\n";
}