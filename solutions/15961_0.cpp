#include <iostream>

using namespace std;

int N, d, k, c;
int sushi[3000000] = { 0, };
int list[3001] = { 0, };

int GetCnt() {
    int ret=0;
    for(int i=0; i<=d; i++) {
        if(list[i] > 0) ret++;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>N>>d>>k>>c;
    for(int i=0; i<N; i++)
        cin>>sushi[i];

    int result=0;
    int cnt=0;
    list[c]++;
    for(int i=0; i<k; i++) {
        list[sushi[i]]++;
        //cout<<"push: "<<sushi[i]<<" ";
    }
    //cout<<endl;
    cnt = GetCnt();
    result = cnt;
    for(int i=1; i<N; i++) {
        list[sushi[(i-1)%N]]--;
        if(list[sushi[(i-1)%N]] == 0) cnt--;
        list[sushi[(i+k-1)%N]]++;
        if(list[sushi[(i+k-1)%N]] == 1) cnt++;
        //cout<<"pop: "<<sushi[(i-1)%N]<<" ";
        //cout<<"push: "<<sushi[(i+k-1)%N]<<" ";
        //cout<<"cnt: "<<cnt<<"\n";
        result = max(cnt, result);
    }
    
    cout<<result<<endl;
}