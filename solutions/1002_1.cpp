#include <iostream>

using namespace std;

int t, x1, y1, r1, x2, y2, r2;

int main() {
    cin>>t;
    while(t--) {
        cin>>x1>>y1>>r1>>x2>>y2>>r2;

        int dist = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
        int sum = (r1 + r2) * (r1 + r2);
        int diff = (r1 - r2) * (r1 - r2);

        int output;
        if(dist == 0 && diff == 0)
            output = -1;
        else if(diff < dist && dist < sum)
            output = 2;
        else if(diff == dist || sum == dist)
            output = 1;
        else
            output = 0;

        cout<<output<<"\n";
    }
}