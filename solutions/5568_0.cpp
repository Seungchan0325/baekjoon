#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int N, K;
string cards[10];
set<string> checked;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin>>N>>K;

    for(int i=0; i<N; i++) 
        cin>>cards[i];

    sort(cards, cards+N);
    do{
        string num;
        for(int i=0; i<K; i++){
            num += cards[i];
        }
        checked.insert(num);
        //cout<<num<<endl;
    }while(next_permutation(cards, cards+N));

    cout<<checked.size()<<endl;
}