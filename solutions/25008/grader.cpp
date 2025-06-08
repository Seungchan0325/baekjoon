#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>

extern int findP(char T[], char P[], int N, int M);

static const int MAX_T = int(1e6);
static const int MAX_P = int(1e6);

static char text[MAX_T + 10];
static char patt[MAX_P + 10];
static int n, m;

int main()
{
	assert(scanf("%s", text) == 1);
	assert(scanf("%s", patt) == 1);

	n = strlen(text);
	m = strlen(patt);

	assert(1 <= n && n <= MAX_T);
	assert(1 <= m && m <= MAX_P);
	assert(m <= n);

	int res = findP(text, patt, n, m);

	printf("%d\n", res);

	return 0;
}
