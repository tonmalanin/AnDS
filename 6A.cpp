#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int sz;
  std::cin >> sz;
  std::vector<int> vec(sz);
  for (int i = 0; i < sz; ++i) {
    std::cin >> vec[i];
  }
  const int kIntMin = -2147483647 - 1;
  std::vector<int> max_end(sz, kIntMin);
  std::vector<int> dp(sz);
  for (int i = 0; i < sz; ++i) {
    int lg = -1;
    int rg = sz - 1;
    while (rg - lg > 1) {
      int md = (lg + rg) / 2;
      if (max_end[md] < vec[i]) {
        rg = md;
      } else {
        lg = md;
      }
    }
    max_end[rg] = vec[i];
    dp[i] = rg + 1;
  }
  int ans = 0;
  for (auto item : dp) {
    ans = std::max(ans, item);
  }
  std::cout << ans << std::endl;
  int cnt = ans;
  std::vector<int> ids;
  for (int i = sz - 1; i > -1; --i) {
    if (dp[i] == cnt) {
      ids.push_back(i + 1);
      --cnt;
    }
  }
  std::reverse(ids.begin(), ids.end());
  for (auto item : ids) {
    std::cout << item << " ";
  }
}
