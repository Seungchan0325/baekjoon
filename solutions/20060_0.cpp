#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>

std::string guess_sequence(int N);

int press(std::string p);

// #include "combo.h"

namespace {

constexpr int MAX_N = 2000;
constexpr int MAX_NUM_MOVES = 8000;

int N;
std::string S;

int num_moves;

void wrong_answer(const char *MSG) {
  printf("Wrong Answer: %s\n", MSG);
  exit(0);
}

}  // namespace

int press(std::string p) {
  if (++num_moves > MAX_NUM_MOVES) {
    wrong_answer("too many moves");
  }
  int len = p.length();
  if (len > 4 * N) {
    wrong_answer("invalid press");
  }
  for (int i = 0; i < len; ++i) {
    if (p[i] != 'A' && p[i] != 'B' && p[i] != 'X' && p[i] != 'Y') {
      wrong_answer("invalid press");
    }
  }
  int coins = 0;
  for (int i = 0, j = 0; i < len; ++i) {
    if (j < N && S[j] == p[i]) {
      ++j;
    } else if (S[0] == p[i]) {
      j = 1;
    } else {
      j = 0;
    }
    coins = std::max(coins, j);
  }
  return coins;
}

int main() {
  char buffer[MAX_N + 1];
  if (scanf("%s", buffer) != 1) {
    fprintf(stderr, "Error while reading input\n");
    exit(1);
  }
  S = buffer;
  N = S.length();

  num_moves = 0;
  std::string answer = guess_sequence(N);
  if (answer != S) {
    wrong_answer("wrong guess");
    exit(0);
  }
  printf("Accepted: %d\n", num_moves);
  return 0;
}

// My Code

//#include "combo.h"
#include <string>
#include <assert.h>

std::string guess_sequence(int N) {
    char first = -1;
    if(press("AB") != 0) {
        if(press("A") == 1) first = 'A';
        else first = 'B';
    } else {
        if(press("X") == 1) first = 'X';
        else first = 'Y';
    }

    std::string s;
    s.push_back(first);
    std::string cand;
    for(auto c : std::string("ABXY")) {
        if(c != first) cand.push_back(c);
    }
    assert(cand.size() == 3);

    int prv = 1;
    for(int i = 1; i < N - 1; i++) {
        int now = press(s+cand[0] + s+cand[1]+cand[0] + s+cand[1]+cand[1] + s+cand[1]+cand[2]);
        int delta = now - i;

        if(delta == 0) {
            s.push_back(cand[2]);
        } else if(delta == 1) {
            s.push_back(cand[0]);
        } else if(delta == 2) {
            s.push_back(cand[1]);
        } else {
            assert(0);
        }
    }

    if(N == 1) return s;

    if(press(s+cand[0]) == N) s.push_back(cand[0]);
    else if(press(s+cand[1]) == N) s.push_back(cand[1]);
    else s.push_back(cand[2]);

    assert(s.size() == N);
    
    return s;
}
