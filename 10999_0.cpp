#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int N, M, K;
vector<ll> arr, tree, lazy;

void tree_init(int start, int end, int index) {
  if (start == end) {
    tree[index] = arr[start];
    return;
  }
  int mid = (start + end) / 2;
  tree_init(start, mid, index * 2);
  tree_init(mid + 1, end, index * 2 + 1);
  tree[index] = tree[index * 2] + tree[index * 2 + 1];
}

void tree_lazy_update(int start, int end, int index) {
  if (lazy[index] != 0) {
    tree[index] += (end - start + 1) * lazy[index];
    if (start != end) {
      lazy[index * 2] += lazy[index];
      lazy[index * 2 + 1] += lazy[index];
    }
    lazy[index] = 0;
  }
}

void tree_update(int start, int end, int index, int left, int right, ll delta) {
  tree_lazy_update(start, end, index);
  if (right < start || end < left)
    return;

  if (left <= start && end <= right) {
    tree[index] += (end - start + 1) * delta;

    if (start != end) {
      lazy[index * 2] += delta;
      lazy[index * 2 + 1] += delta;
    }
    return;
  }

  int mid = (start + end) / 2;
  tree_update(start, mid, index * 2, left, right, delta);
  tree_update(mid + 1, end, index * 2 + 1, left, right, delta);
  tree[index] = tree[index * 2] + tree[index * 2 + 1];
}

ll tree_sum(int start, int end, int index, int left, int right) {
  tree_lazy_update(start, end, index);
  if (right < start || end < left)
    return 0;

  if (left <= start && end <= right) {
    return tree[index];
  }

  int mid = (start + end) / 2;
  return tree_sum(start, mid, index * 2, left, right) +
         tree_sum(mid + 1, end, index * 2 + 1, left, right);
}

int main(void) {
   std::ios_base::sync_with_stdio(false);
std::cin.tie(nullptr);
std::cout.tie(nullptr);

  cin >> N >> M >> K;
  arr.resize(N);
  tree.resize(4 * N);
  lazy.resize(4 * N);

  for (int i = 0; i < N; i++)
    cin >> arr[i];
  tree_init(0, N - 1, 1);
  // cout << "Debug" << tree[1] << endl;

  ll a, b, c, d;
  for (int i = 0; i < M + K; i++) {
    cin >> a >> b >> c;
    b--;
    c--;
    if (b > c)
      swap(b, c);
    if (a == 1) {
      cin >> d;
      tree_update(0, N - 1, 1, b, c, d);
      // cout << "Debug" << tree[1] << endl;
    } else if (a == 2) {
      ll result = tree_sum(0, N - 1, 1, b, c);
      cout << result << "\n";
    }
  }
}