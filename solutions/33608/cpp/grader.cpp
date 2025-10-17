#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cuchar>
#endif

// C++
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <codecvt>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#endif
#include "evolution2.h"
using namespace std;
void ensure(bool p, const char *err) {
	if (!p) {
		cout << err << endl;
		exit(0);
	}
}

vector<int> Y;
vector<int> REV;
vector<int> PAR;
int __N;
int C;

int compare(int a,int b) {
    ensure(0<=a&&a<__N&&0<=b&&b<__N,"Wrong Answer [1]");
    ensure(a!=b,"Wrong Answer [2]");
    C++;
    return REV[a]<REV[b];
}

int main() {
    int tc;
    assert(scanf("%d",&tc)==1);
    for(int t=0;t<tc;t++) {
    	assert(scanf("%d",&__N)==1);
    	PAR.resize(__N);
    	REV.resize(__N);
    	Y.resize(__N);
    	C=0;
    	for(int i=1;i<__N;i++) {
    	    assert(scanf("%d",&PAR[i])==1);
    	}
    	for(int i=0;i<__N;i++) {
    	    assert(scanf("%d",&Y[i])==1);
    	    REV[Y[i]]=i;
    	}
    	vector<int> U(__N-1);
    	vector<int> V(__N-1);
    	for(int i=1;i<__N;i++) {
    	    U[i-1] = Y[PAR[i]];
    	    V[i-1] = Y[i];
    	}
    	vector<int> X = recover(__N, U, V);
    	ensure(X.size() == __N,"Wrong Answer [3]");
    	printf("C : %d\n",C);
    	for(int i=0;i<__N;i++) {
    	    printf("%d ",X[i]);
    	}
    	printf("\n");
    }
}