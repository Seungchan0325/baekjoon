#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

using ordered_set = tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>;

int N;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;

    ordered_set s;
    while(N--) {
        int t, x;
        cin >> t >> x;
        if(t == 1) {
            s.insert(x);
        } else {
            auto it = s.find_by_order(x-1);
            cout << *it << "\n";
            s.erase(it);
        }
    }
}