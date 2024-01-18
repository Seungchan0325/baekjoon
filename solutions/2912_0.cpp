#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;
const int MAXM = 10005;
const int MAXC = 10005;

int sqrtN;

struct Query {
    int s, e;
    int idx;
    bool operator < (const Query& other) const
    {
        if(s / sqrtN != other.s / sqrtN) return s / sqrtN < other.s / sqrtN;
        return e < other.e;
    }
};

int N, C, M, hats[MAXN];
pair<int, int> tree[4*MAXC];
string ans[MAXM];
Query queries[MAXM];

void build(int start = 1, int end = C, int index = 1)
{
    if(start == end) {
        tree[index].first = 0;
        tree[index].second = start;
        return;
    }

    int mid = (start + end) / 2;
    build(start, mid, 2*index);
    build(mid+1, end, 2*index+1);
    tree[index] = max(tree[2*index], tree[2*index+1]);
}

void update(int pos, int delta, int start = 1, int end = C, int index = 1)
{
    if(end < pos || pos < start) return;

    if(start == end) {
        tree[index].first += delta;
        return;
    }

    int mid = (start + end) / 2;
    update(pos, delta, start, mid, 2*index);
    update(pos, delta, mid+1, end, 2*index+1);
    tree[index] = max(tree[2*index], tree[2*index+1]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> C;
    sqrtN = sqrt(N);
    for(int i = 1; i <= N; i++) {
        cin >> hats[i];
    }
    cin >> M;
    for(int i = 0; i < M; i++) {
        cin >> queries[i].s >> queries[i].e;
        queries[i].idx = i;
    }
    sort(queries, queries + M);

    build();

    int s = queries[0].s;
    int e = s - 1;
    int max_v = 0;
    int updates[C + 1] = {0, };

    for(int i = 0; i < M; i++) {
        while(s < queries[i].s) { max_v = max(--updates[hats[s++]], max_v);}
        while(queries[i].s < s) { max_v = max(++updates[hats[--s]], max_v);}
        while(e < queries[i].e) { max_v = max(++updates[hats[++e]], max_v);}
        while(queries[i].e < e) { max_v = max(--updates[hats[e--]], max_v);}

        int half = (e - s + 1) / 2;

        if(tree[1].first + max_v > half) {
            for(int j = 1; j <= C; j++) {
                if(updates[j]) {
                    update(j, updates[j]);
                }
            }
            memset(updates, 0, sizeof(int) * (C + 1));
            max_v = 0;
        }
        string output;
        if(half < tree[1].first) {
            output = "yes " + to_string(tree[1].second);
        }
        else {
            output = "no";
        }
        ans[queries[i].idx] = output;
    }
    
    for(int i = 0; i < M; i++) {
        cout << ans[i] << "\n";
    }
}