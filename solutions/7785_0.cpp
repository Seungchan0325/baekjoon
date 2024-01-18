#include <iostream>
#include <string>
#include <set>

#define endl '\n'

using namespace std;

int N;
set<string, greater<string>> leave_person;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>N;
    for(int i=0; i<N; i++) {
        string name, inout;
        cin>>name>>inout;
        if(inout == "enter")
            leave_person.insert(name);
        else if(inout == "leave")
            leave_person.erase(name);
    }

    for(auto& item:leave_person) {
        cout<<item<<endl;
    }
}