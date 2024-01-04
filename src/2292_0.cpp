#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;

    int a = 1;
    for(int i = 1; ; i++){
        if(n <= a){
            cout << i << endl;
            break;
        }
        a += i*6;
    }
}