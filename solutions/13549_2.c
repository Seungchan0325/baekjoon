#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAXN (140005)
#define BUF_SZ (20)

int head = 1, tail = 0, deque[MAXN], dist[MAXN];

void push_front(int v)
{
    head = (head - 1 + MAXN) % MAXN;
    deque[head] = v;
}

void push_back(int v)
{
    tail = (tail + 1 + MAXN) % MAXN;
    deque[tail] = v;
}

int front()
{
    int ret = deque[head];
    head = (head + 1 + MAXN) % MAXN;
    return ret;
}

int main(void)
{
    int n = 0, k = 0;
    char buf[BUF_SZ] = { 0, };
    read(0, buf, BUF_SZ - 1);
    char* p = buf;
    for(; !isspace(*p); p++) n = 10 * n + (*p - '0');
    p++;
    for(; !isspace(*p); p++) k = 10 * k + (*p - '0');

    memset(deque, 0, sizeof(deque));
    memset(dist, 0x7F, sizeof(dist));

    push_front(n);
    dist[n] = 0;
    while(head <= tail) {
        int cur = front();

        if(2 * cur < MAXN && dist[cur] < dist[2 * cur]) {
            dist[2 * cur] = dist[cur];
            push_front(2 * cur);
        }
        if(0 <= cur - 1 && dist[cur] + 1 < dist[cur - 1]) {
            dist[cur - 1] = dist[cur] + 1;
            push_back(cur - 1);
        }
        if(cur + 1 < MAXN && dist[cur] + 1 < dist[cur + 1]) {
            dist[cur + 1] = dist[cur] + 1;
            push_back(cur + 1);
        }
    }

    printf("%d", dist[k]);

    return 0;
}