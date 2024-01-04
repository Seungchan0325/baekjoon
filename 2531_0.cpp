#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, d, k, c;
int sushi_list[30000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>N>>d>>k>>c;

    for(int i=0; i<N; i++)
        cin>>sushi_list[i];
    
    int ret = 0;
    for(int i=0; i<N; i++) {
        int tmp=0;
        vector<int> a(3002);
        for(int j=0; j<k; j++) {
            if(a[sushi_list[(j+i)%N]] == 0) {
                a[sushi_list[(j+i)%N]] = 1;
                tmp++;
            }
        }
        if(a[c] == 0) tmp++;
        ret = max(tmp, ret);
    }

    cout<<ret<<"\n";
}