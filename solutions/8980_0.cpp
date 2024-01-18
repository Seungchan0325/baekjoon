#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, c, m;
    cin>>n>>c>>m;
    vector<pair<int, int>> packages[2001];
    for(int i=0; i<m; i++) {
        int from, to, package; cin>>from>>to>>package;
        packages[from].push_back({to, package});
    }

    // for(int i=1; i<=n; i++) {
    //     for(auto [to, package] : packages[i]) {
    //         printf("from: %d\tto: %d\tpackage: %d\n", i, to, package);
    //     }
    // }

    int sum = 0;
    int delivering = 0;
    int delivering_package[2001];
    memset(delivering_package, 0, sizeof(delivering_package));
    for(int i=1; i<=n; i++) {
        sum += delivering_package[i];
        delivering -= delivering_package[i];
        delivering_package[i] = 0;
        
        // printf("%d 1\n", delivering);
        // for(int j=1; j<=n; j++) {
        //     printf("%d ", delivering_package[j]);
        // }
        // printf("\n");

        for(auto [to, package] : packages[i]) {
            delivering += package;
            delivering_package[to] += package;
        }

        // printf("%d 2\n", delivering);
        // for(int j=1; j<=n; j++) {
        //     printf("%d ", delivering_package[j]);
        // }
        // printf("\n");

        int last = n;
        while(c < delivering) {
            int over = delivering - c;
            delivering -= min(over, delivering_package[last]);
            delivering_package[last] -= min(over, delivering_package[last]);
            last--;
        }

        // printf("%d 3\n", delivering);
        // for(int j=1; j<=n; j++) {
        //     printf("%d ", delivering_package[j]);
        // }
        // printf("\n");
    }

    cout<<sum;
}