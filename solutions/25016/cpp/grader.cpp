#include "evolution.h"
#include <cstdio>

int main(){
    init();
    int n;
    scanf("%d", &n);
    for(int i=1; i<=n; i++){
        int qtype, u;
        scanf("%d %d", &qtype, &u);
        if(qtype==1)observation(u);
        if(qtype==2)printf("%d\n", analyze(u));
    }
    return 0;
}
