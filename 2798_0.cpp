#include <iostream>
#include <vector>

using namespace std;

int brute_search(const vector<int> &input);

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> input(n);
    for (int i = 0; i < n; i++)
    {
        cin >> input[i];
    }

    int max = -2147483647 - 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                int sum = input[i] + input[j] + input[k];
                if (sum <= m)
                    max = std::max(max, sum);
            }
        }
    }
    cout << max << endl;
}