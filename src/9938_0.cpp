#include <iostream>

using namespace std;

int a, b, n, l, root[300000], sz[300000], con[300000];

int find(int x) {
    if(root[x] == x) return x;
    else return root[x] = find(root[x]);
}

void Union(int x, int y) {
    x = find(x);
    y = find(y);

    if(x == y) return;

    con[x] += con[y];
    sz[x] += sz[y];
    root[y] = x;
}

int main() {
    scanf("%d %d", &n, &l);
    for(int i=0; i<l; i++) {
        root[i] = i;
        sz[i] = 1;
    }
    for(int i=0; i<n; i++) {
        scanf("%d %d", &a, &b); a--; b--;

        Union(a, b);

        int pa = find(a);
        if(con[pa] < sz[pa]) {
            con[pa]++;
            printf("LADICA\n");
        } else {
            printf("SMECE\n");
        }
    }
}