#include<iostream>
#include<string.h>

using namespace std;

int main(void){
    int T;
    cin >> T;
    int R[T];
    char S[T][21];
    for(int i = 0; i < T; i++){
        cin >> R[i] >> S[i];
    }
    
    for(int i = 0; i < T; i++){
        for(int j = 0; j < strlen(S[i]); j++){
            for(int k = 0; k < R[i]; k++){
                cout << S[i][j];
            }
        }
        cout << endl;
    }
}