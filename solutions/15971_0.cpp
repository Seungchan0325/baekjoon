    #include <iostream>
    #include <vector>

    using namespace std;

    struct edge {
        int target_node;
        int weight;
        edge(int _target_node, int _weight) : weight(_weight), target_node(_target_node) {};
    };

    int N, R1, R2;
    int costs[2][100001] = { 0 };
    vector<edge> graph[100001];
    vector<bool> visited;

    void make_cost(int idx, int node_id, int cost) {
        visited[idx] = true;
        costs[node_id][idx] = cost;

        for(auto& i : graph[idx]) {
            if(!visited[i.target_node])
                make_cost(i.target_node, node_id, cost + i.weight);
        }
    }

    int main() {
        cin>>N>>R1>>R2;
        R1--;R2--;
        for(int i=0; i<N-1; i++) {
            int a, b, len;
            cin>>a>>b>>len;
            a--;b--;
            graph[a].push_back(edge(b, len));
            graph[b].push_back(edge(a, len));
        }

        if(R1 == R2) {
            cout<<0<<endl;
            return 0;
        }

        visited = vector<bool>(N);
        make_cost(R1, 0, 0);
        visited = vector<bool>(N);
        make_cost(R2, 1, 0);

        int ans = 1e9;
        for(int i=0; i<N; i++) {
            for(auto& j : graph[i]) {
                ans = min(ans, costs[0][i] + costs[1][j.target_node]);
            }
        }

        cout<<ans<<endl;
    }