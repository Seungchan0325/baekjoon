#include <bits/stdc++.h>

using namespace std;

int A[1000005];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;
    for(int i = n; i > 0; i--) {
        cin >> A[i];
    }
    list<int> deck;
    for(int i = 1; i <= n; i++) {
        if(A[i] == 1) {
            deck.push_front(i);
        } else if(A[i] == 2) {
            deck.insert(++deck.begin(), i);
        } else {
            deck.push_back(i);
        }
    }

    for(auto it = deck.begin(); it != deck.end(); it++) {
        cout << *it << " ";
    }
}