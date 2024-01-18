#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

int main()
{
    int input;
    cin >> input;

    int min_gen = INT_MAX;
    for (int i = 0; i < input; i++){
        int sum = 0;
        string generator = to_string(i);
        for (const auto &item : generator){
            sum += item - '0';
        }
        sum += stoi(generator);
        //if (sum > stoi(input)) break;

        if (sum == input)
            min_gen = std::min(i, min_gen);
    }
    if(INT_MAX == min_gen){
        min_gen = 0;
    }
    cout << min_gen << endl;
}