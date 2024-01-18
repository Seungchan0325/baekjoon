#include <iostream>
using namespace std;
int main(){
    int n;
    cin >> n;

    int box= 0;
    while(true){
        if(n%5 == 0){
            box += n/5;
            break;
        }
        n -= 3;
        box++;
        if(n < 0){
            box = -1;
            break;
        }
    }
    cout << box << endl;
}