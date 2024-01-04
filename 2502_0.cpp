#include <iostream>
#include <vector>

using namespace std;

int D, K;
vector<int> fibo;

int main() {
    cin >> D >> K;

    fibo.resize(D);
    for(int i = 1; i < K; i++) {
        for(int j = i; j < K; j++) {
            fibo.clear();
            fibo[0] = i; fibo[1] = j;

            for(int i = 2; i < D; i++) {
                fibo[i] = fibo[i-1] + fibo[i-2];
                if(fibo[i] > K)
                    break;
            }

            if(fibo[D-1] == K) {
                cout << i << "\n" << j << "\n";
                exit(0);
            }
        }
    }
}