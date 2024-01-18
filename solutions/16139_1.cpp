#include <iostream>
#include <cstring>
#include <memory.h>

using namespace std;

char c, str[200000];
int arr[26][200001];
int q, l, r, len;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>str;
    cin>>q;
    len = strlen(str);
    for(int i=0; i<len; i++) {
        arr[str[i]-'a'][i+1] = 1;
    }
    for(int i=0; i<len; i++) {
        for(int j=0; j<26; j++) {
            arr[j][i+1] += arr[j][i];
        }
    }
    for(int i=0; i<q; i++) {
        cin>>c>>l>>r;
        
        int result = arr[c-'a'][r+1] - arr[c-'a'][l];

        cout<<result<<"\n";
    }
}