#include <iostream>

using namespace std;

int main(){
    int t;
    cin >> t;

    while(t--){
        int h, w, n;
        cin >> h >> w >> n;
		int start = n % h;
		int end = n / h + 1;
			
        if (start == 0){
				start = h;  
				end = end - 1; 
				
		}
        cout << start;
        cout.width(2);
        cout.fill('0');
        cout << end << endl;
    }
}